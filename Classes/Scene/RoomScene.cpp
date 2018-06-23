#include "Scene/RoomScene.h"
#include"Scene/GameScene.h"
#include"Network/Msg.h"
#include"Network/Client.h"
#include"Global/Player.h"
#include"Global/Global.h"
#include"Scene/ChatBox.h"
#include "ui/UIText.h"
#include"ProgressScene.h"

USING_NS_CC;

RoomScene::RoomScene()
{
	isEnter = false;
}

RoomScene::~RoomScene()
{
}

bool RoomScene::init()
{
	createBackground();
	createTitle();
	initUIBox();
	createBackButton();	
	creatCharacter();
	createSettingButton();
	auto ChatBox = ChatBox::create();
	addChild(ChatBox,20);
	Music::PlayMusic(Music::music::room);
	scheduleUpdate();
	return true;
}

void RoomScene::update(float det)
{
	checkConnect();
	checkCharacter();
}

void RoomScene::createBackground()
{
	auto visiblesize = Director::getInstance()->getVisibleSize();
	auto bg = Sprite::create("Scene/Room/bg.png");
	assert(bg != nullptr);
	bg->setScale(1.6f);
	bg->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	addChild(bg, -1);
}


void RoomScene::createBackButton()
{
	auto back = MenuItemLabel::create(
		Label::createWithTTF("Back", "fonts/Quicksand-Bold.ttf", 50),
		CC_CALLBACK_1(RoomScene::menuBackCallback, this));
	back->setPosition(90, 680);
	back->setColor(ccc3(3, 38, 58));
	auto menu = Menu::create();
	menu->addChild(back, 0);
	menu->setPosition(0, 0);
	addChild(menu, 3);
}

void RoomScene::createSettingButton()
{
	settingLayer = RoomSetting::create();
	settingLayer->setVisible(false);
	settingLayer->setTouchEnabled(false);

	auto setting = MenuItemLabel::create(
		Label::createWithTTF("Setting", "fonts/Marker Felt.ttf", 50),
		CC_CALLBACK_1(RoomScene::menuSettingCallback, this));
	setting->setPosition(750, 250);
	setting->setColor(ccc3(3, 38, 58));
	auto menu = Menu::create();
	menu->addChild(setting, 0);
	menu->setPosition(0, 0);

	addChild(menu, 3);
	addChild(settingLayer,10);
}

void RoomScene::createTitle()
{
	auto label = Label::createWithTTF("ROOM", "fonts/Marker Felt.ttf",50);
	auto visiblesize = Director::getInstance()->getVisibleSize();
	label->setPosition(visiblesize.width / 2, visiblesize.height - 70);
	label->enableGlow(Color4B::BLUE);
	addChild(label, 0);
}

void RoomScene::initUIBox()
{
	auto visiblesize = Director::getInstance()->getVisibleSize();
	std::vector<Sprite*> roomitems = {
		Sprite::create("Scene/Room/roomcase_01.png"),
		Sprite::create("Scene/Room/roomcase_01.png"),
		Sprite::create("Scene/Room/roomcase_01.png"),
		Sprite::create("Scene/Room/roomcase_01.png")
	};

	for (int i = 0; i < roomitems.size(); ++i)
	{
		const int highsize = 550;
		roomitems[i]->setPosition(120 + i * 170, highsize);
		roomitems[i]->setTag(i);
		this->addChild(roomitems[i], 0);
	}

	auto clickme = MenuItemLabel::create(
		Label::createWithTTF("click me", "Fonts/Marker Felt.ttf", 55),
		CC_CALLBACK_1(RoomScene::clickmeCallback, this));
	clickme->setPosition(250, 250);
	clickme->setColor(ccc3(3, 38, 58));
	auto menu = Menu::create();
	menu->addChild(clickme, 0);
	menu->setPosition(0, 0);
	addChild(menu, 3);
}

void RoomScene::creatCharacter()
{
	for (auto it = Player::Players.begin(); it != Player::Players.end(); ++it)
	{
		auto name = it->first;
		auto player = it->second;
	    int roomID = Player::Players[name]->getRoomID();
		auto _room = getChildByTag(roomID);
		Sprite* room = static_cast<Sprite*>(_room);
	    auto roomsize = room->getContentSize();

		auto nameLabel =  cocos2d::ui::Text::create(name , "fonts/È«ÐÂÓ²±Ê¿¬Êé¼ò.ttf",17);
		auto namesize = nameLabel->getContentSize();
		nameLabel->setColor(cocos2d::Color3B::YELLOW);
		nameLabel->setPosition(Vec2(roomsize.width / 2, roomsize.height*0.2));

		std::string pic = Path::Player::getPicCharacter(player->getNumber());
		auto characpic = Sprite::create(pic);
		characpic->setPosition(Vec2(roomsize.width / 2, roomsize.height*0.65));

		room->removeAllChildren();
		room->addChild(characpic);
		room->addChild(nameLabel);
	}
}


void RoomScene::menuBackCallback(cocos2d::Ref * pSender)
{
   auto  quitLayer = PopupLayer::create("Scene/Room/c8.png");
	quitLayer->setContentSize(CCSizeMake(600, 360));
	quitLayer->setTitle("Quit", 20);
	quitLayer->setContentText("You will leave the room",30,30,300);
	quitLayer->addButton("Scene/Room/button_normal.png", "Scene/Room/button_selected.png", 
	  	"Ok",1,menu_selector(RoomScene::OKCallback));
	quitLayer->addButton("Scene/Room/button_normal.png", "Scene/Room/button_selected.png","Cancel");
	this->addChild(quitLayer, 5,50);
}

void RoomScene::OKCallback(Ref * pSender)
{
	StopClient();
	for (auto it = Player::Players.begin(); it != Player::Players.end(); ++it)
	{
		auto name = it->first;
		auto player = it->second;
		delete(player);
	}
	Player::Players.clear();
	Director::getInstance()->popScene();
	Sleep(50);
}


void RoomScene::clickmeCallback(Ref * pSender)
{
	SendMsg_ChangeSprite(Player::local_Username);
	Sleep(50);
}

void RoomScene::menuSettingCallback(cocos2d::Ref * pSender)
{
	Action *popupactions = Sequence::create(ScaleTo::create(0.0, 0.0), ScaleTo::create(0.5, 1.05), ScaleTo::create(0.2, 0.95), ScaleTo::create(0.2, 1.0), NULL);
	settingLayer->runAction(popupactions);
	settingLayer->setVisible(true);
	settingLayer->setTouchEnabled(true);
}


void RoomScene::checkConnect()
{
	FOR_ALL_PLAYERS{
		auto player = it->second;
	    auto name = it->first;
	    if (!player->isconnect)
		{
			printf("%s!!!!!!!!\n", name);
			auto room = getChildByTag(player->getRoomID());
			room->removeAllChildren();
			Player::Players.erase(name);
			delete(player);
			break;
		}
	}
}

void RoomScene::checkCharacter()
{
	FOR_ALL_PLAYERS{
		auto player = it->second;
	    auto name = it->first;
	    if (!player->ischange) continue;
	    player->ischange = false;
	    creatCharacter();
	}
}
