#include "Scene/RoomScene.h"
#include"Scene/GameScene.h"
#include"Network/Msg.h"
#include"Global/Player.h"
#include"Global/Global.h"
#include"Scene/RoomSetting.h"
#include"Scene/ChatBox.h"
#include "ui/UIText.h"

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
	createSettingButton();
	auto ChatBox = ChatBox::create();
	addChild(ChatBox);
	scheduleUpdate();
	return true;
}

void RoomScene::update(float det)
{
	checkConnect();
	creatCharacter();
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
	auto setting = MenuItemLabel::create(
		Label::createWithTTF("Setting", "fonts/Marker Felt.ttf", 50),
		CC_CALLBACK_1(RoomScene::menuSettingCallback, this));
	setting->setPosition(750, 250);
	setting->setColor(ccc3(3, 38, 58));
	auto menu = Menu::create();
	menu->addChild(setting, 0);
	menu->setPosition(0, 0);
	addChild(menu, 3);
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

		if (!player->ischange) continue;

	    int roomID = Player::Players[name]->getRoomID();
		auto _room = getChildByTag(roomID);
		Sprite* room = static_cast<Sprite*>(_room);
	    auto roomsize = room->getContentSize();

		auto nameLabel =  cocos2d::ui::Text::create(name , "fonts/全新硬笔楷书简.ttf",17);
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
	// 你给我下了毒，和你聊天是唯一的解药
}





void RoomScene::menuBackCallback(cocos2d::Ref * pSender)
{
	for (auto it = Player::Players.begin(); it != Player::Players.end(); ++it)
	{
		auto name = it->first;
		auto player = it->second;
		delete(player);
	}
	Player::Players.clear();
	Director::getInstance()->popScene();
}

void RoomScene::clickmeCallback(Ref * pSender)
{
	SendMsg_ChangeSprite(Player::local_Username);
	Sleep(50);
}

void RoomScene::menuSettingCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1, RoomSetting::create()));
}

void RoomScene::readyCallback(Ref * pSender)
{
	//Director::getInstance()->pushScene(TransitionFade::create(1, GameScene::create()));
}


void RoomScene::checkConnect()
{
	FOR_ALL_PLAYERS{
		auto player = it->second;
	    auto name = it->first;
	    if (!player->isconnect)
		{
			auto room = getChildByTag(player->getRoomID());
			room->removeAllChildren();
			Player::Players.erase(name);
			delete(player);
			break;
		}
	}
}


