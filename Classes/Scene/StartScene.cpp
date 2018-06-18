#include"Scene/StartScene.h"
#include"Scene/RoomScene.h"
#include"Scene/LoginScene.h"
#include"Scene/HelpScene.h"
#include"Scene/SettingScene.h"
#include "SimpleAudioEngine.h"
#include"Scene/HelpScene.h"
#include"Global/Global.h"

USING_NS_CC;
using namespace CocosDenshion;

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::init()
{
	if (Setting::musicSwitch)
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/mainScene.mp3", true);
	}
	addBackground();
	addButton();
	return true;
}

void StartScene::addBackground()
{
	auto visiblesize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create("Scene/Start/background.jpg");
	assert(background != nullptr);
	background->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	background->setScale(1.55f);
	addChild(background,-1);
}


void StartScene::menuPlayCallback(cocos2d::Ref * pSender) 
{
	Director::getInstance()->replaceScene(TransitionFade::create(1, LoginScene::create()));
}

void StartScene::menuSettingsCallback(cocos2d::Ref * pSender) 
{
	Director::getInstance()->pushScene(TransitionFade::create(1, SettingScene::create()));
}
void StartScene::menuHelpCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->pushScene(TransitionFade::create(1, HelpScene::create()));
}

void StartScene::menuExitCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void StartScene::addButton()
{
	const int size = 50;
	std::vector<MenuItem *> items =
	{
		MenuItemLabel::create(
			Label::createWithTTF("Play", "Fonts/Marker Felt.ttf",size),
			CC_CALLBACK_1(StartScene::menuPlayCallback, this)),
		MenuItemLabel::create(
			Label::createWithTTF("Settings","Fonts/Marker Felt.ttf",size),
			CC_CALLBACK_1(StartScene::menuSettingsCallback, this)),
		MenuItemLabel::create(
			Label::createWithTTF("Help","Fonts/Marker Felt.ttf",size),
			CC_CALLBACK_1(StartScene::menuHelpCallback, this)),
		MenuItemLabel::create(
			Label::createWithTTF("Exit","Fonts/Marker Felt.ttf",size),
			CC_CALLBACK_1(StartScene::menuExitCallback, this))
	};
	
	auto menu = Menu::create();
	menu->setPosition(0, 0);
	for (int i = 0; i < items.size(); ++i)
	{
		const int highsize = 50;
		const int widesize = 900;
		items[i]->setPosition(widesize, highsize*(12 - i*2 ));
		items[i]->setColor(ccc3(3,38,58));
		menu->addChild(items[i], 0);
	}
	addChild(menu, 0);
}

