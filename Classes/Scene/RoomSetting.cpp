#include "RoomSetting.h"
#include"Scene/ProgressScene.h"
#include"Scene/RoomScene.h"
#include"Network/Msg.h"
#include"Global/Global.h"
USING_NS_CC;


RoomSetting::RoomSetting()
{
}

RoomSetting::~RoomSetting()
{
}

bool RoomSetting::init()
{
	m_mapID = 0;
	m_modeID = 0;
	Msg::Room.ismapchange = false;
	Msg::Room.ismodechange = false;
	addBackground();
	createReadyButton();
	createPatternButton();
	createMapButton();
	createBackButton();
	scheduleUpdate();
	return true;
}

void RoomSetting::update(float det)
{
	if (Msg::Room.ismapchange){
		changeMap();
		Msg::Room.ismapchange = false;
	}

	if (Msg::Room.ismodechange){
		Msg::Room.ismodechange = false;
	}
	if (Msg::Room.isstart)
	{
		auto scene = ProgressScene::create();
		scene->start(m_mapID);
		Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
	}
}


void RoomSetting::addBackground()
{
	auto visiblesize = Director::getInstance()->getVisibleSize();
	
	auto background = Sprite::create("Scene/Room/bg.png");
	assert(background != nullptr);
	background->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	background->setScale(1.4f);
	addChild(background, -1);
	
	auto map = TMXTiledMap::create(Path::picMap[0]);
	assert(map != nullptr);
	map->setPosition(600,250);
	map->setScale(0.38f);
	map->setTag(1);
	addChild(map, -1);
	
	auto label1 = Label::createWithTTF("Only the host has the right", "fonts/Marker Felt.ttf", 35);
	label1->setPosition(visiblesize.width / 2, visiblesize.height - 80);
	label1->setColor(ccc3(117,27,19));
	addChild(label1, 0);
	auto label2 = Label::createWithTTF("to change the map and the pattern", "fonts/Marker Felt.ttf", 35);
	label2->setPosition(visiblesize.width / 2, visiblesize.height - 120);
	label2->setColor(ccc3(117, 27, 19));
	addChild(label2, 0);

	auto disbox = Sprite::create("Scene/Room/roomcase_02.png");
	assert(disbox != nullptr);
	disbox->setPosition(260, 280);
	disbox->setScale(1.8f);
	addChild(disbox, -1);
}

void RoomSetting::onTouchEnter(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)  //ready的回调函数
{
	static bool isready = false;
	if (type != ui::Widget::TouchEventType::ENDED) return;

	isready = !isready;
	if (isready){
		m_readyButton->setTitleText("cancle");
	}
	else{
		m_readyButton->setTitleText("ready");
	}
	SendMsg_Ready();
	Sleep(100);
}

void RoomSetting::changeMap()
{
	if( getChildByTag(1)!=nullptr ) removeChildByTag(1);
	m_mapID = (m_mapID + 1) % Setting::MaxMapNum;
	auto map = TMXTiledMap::create(Path::picMap[m_mapID]);
	assert(map != nullptr);
	map->setPosition(600, 250);
	map->setScale(0.38f);
	map->setTag(1);
	addChild(map, -1);
}

void RoomSetting::createReadyButton()    
{
	auto visiblesize = Director::getInstance()->getVisibleSize();
    m_readyButton = ui::Button::create("Scene/RoomScene/button_normal.png", "Scene/RoomScene/button_selected.png");
	m_readyButton->setTitleText("ready");
	m_readyButton->setTitleFontSize(35);
	m_readyButton->setContentSize(Size(100, 50));
	m_readyButton->setPosition(Vec2(visiblesize.width / 2, 100));
	addChild(m_readyButton, 5);
	m_readyButton->addTouchEventListener(CC_CALLBACK_2(RoomSetting::onTouchEnter, this));
}

void RoomSetting::createMapButton()
{
	auto map = MenuItemLabel::create(
		Label::createWithTTF("Map", "fonts/Marker Felt.ttf", 40),
		CC_CALLBACK_1(RoomSetting::menuMapCallback, this));
	map->setPosition(750, 200);
	map->setColor(ccc3(3, 38, 58));
	auto menu = Menu::create();
	menu->addChild(map, 0);
	menu->setPosition(0, 0);
	addChild(menu, 3);
}
void RoomSetting::menuMapCallback(cocos2d::Ref * pSender)
{
	SendMsg_ChangeMap(1);
	Sleep(50);
}

void RoomSetting::createPatternButton()
{
	auto pattern = MenuItemLabel::create(
		Label::createWithTTF("Pattern", "fonts/Marker Felt.ttf", 40),
		CC_CALLBACK_1(RoomSetting::menuPatternCallback, this));
	pattern->setPosition(250, 200);
	pattern->setColor(ccc3(3, 38, 58));
	auto menu = Menu::create();
	menu->addChild(pattern, 0);
	menu->setPosition(0, 0);
	addChild(menu, 3);
}
void RoomSetting::menuPatternCallback(cocos2d::Ref * pSender)
{
	SendMsg_ChangeMode(1);
	Sleep(50);
}

void RoomSetting::createBackButton()
{
	auto back = MenuItemLabel::create(
		Label::createWithTTF("Back", "fonts/Quicksand-Bold.ttf", 50),
		CC_CALLBACK_1(RoomSetting::menuBackCallback, this));
	back->setPosition(90, 650);
	back->setColor(ccc3(3, 38, 58));
	auto menu = Menu::create();
	menu->addChild(back, 0);
	menu->setPosition(0, 0);
	addChild(menu, 3);
}

void RoomSetting::menuBackCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1, RoomScene::create()));
}
