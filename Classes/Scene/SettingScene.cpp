#include"Scene/StartScene.h"
#include"Global/Global.h"
#include"Scene/SettingScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

SettingScene::SettingScene()
{
}

SettingScene::~SettingScene()
{
}

bool SettingScene::init()
{
	addBackground();
	addButton();
	createBackButton();
	return true;
}

void SettingScene::addBackground()
{
	auto visiblesize = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("Scene/Setting/background1.jpg");
	assert(background != nullptr);
	background->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	background->setScale(1.4f);
	addChild(background, -1);
	auto label = Label::createWithTTF("Music", "fonts/Marker Felt.ttf", 50);
	label->setPosition(800,580);
	label->setColor(ccc3(255, 245, 153));
	addChild(label, 0);
}


void SettingScene::addButton()
{
	int size = 50;
	std::vector<MenuItem *> items =
	{
		m_music=MenuItemLabel::create(
			Label::createWithTTF("On", "Fonts/Quicksand-Bold.ttf",size),
			CC_CALLBACK_1(SettingScene::menuMusicOnCallback, this))
	};
	auto menu = Menu::create();
	menu->setPosition(0, 0);
	items[0]->setPosition(950,580);
	items[0]->setColor(ccc3(255,255,255));
	menu->addChild(items[0], 0);
	addChild(menu, 0);
}


void SettingScene::menuMusicOnCallback(cocos2d::Ref * pSender)
{
	using namespace CocosDenshion;
	//SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	if (Setting::musicSwitch)
	{
		m_music->setString("Off");
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

	}
	else
	{
		m_music->setString("On");
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
	Setting::musicSwitch = !Setting::musicSwitch;
}

void SettingScene::createBackButton()
{
	auto back = MenuItemLabel::create(
		Label::createWithTTF("Back", "fonts/Quicksand-Bold.ttf", 50),
		CC_CALLBACK_1(SettingScene::menuBackCallback, this));
	back->setPosition(90, 680);
	back->setColor(ccc3(255, 245, 247));
	auto menu = Menu::create();
	menu->addChild(back, 0);
	menu->setPosition(0, 0);
	addChild(menu, 3);
}

void SettingScene::menuBackCallback(cocos2d::Ref * pSender)
{
//	Director::getInstance()->replaceScene(TransitionFade::create(1, StartScene::create()));
	Director::getInstance()->popScene();
}