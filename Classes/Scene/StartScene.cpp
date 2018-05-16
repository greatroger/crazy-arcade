#include"StartScene.h"
USING_NS_CC;

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::init()
{
	addBackground();
	addButton();
	return true;
}

void StartScene::addBackground()
{
	auto visiblesize = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("");
	assert(background != nullptr);
	background->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	addChild(background,-1);
}

void StartScene::addButton()
{

}