#include"Scene/LoadingScene.h"
#include"Scene/StartScene.h"
#include "SimpleAudioEngine.h"
#include<assert.h>
USING_NS_CC;


LoadingScene::LoadingScene()
{
}

LoadingScene::~LoadingScene()
{
}

bool LoadingScene::init()
{
	addBackground();
	if (load())
	{
	   scheduleOnce(CC_SCHEDULE_SELECTOR(LoadingScene::endLoad), 0.5);
	}
	return true;
}

bool LoadingScene::load()
{
	//load something
	return true;
}

void LoadingScene::endLoad(float dt)
{
	const auto transition = TransitionFade::create(1, StartScene::create());
	Director::getInstance()->replaceScene(transition);
}

void LoadingScene::addBackground()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//create "Loading...."
	auto label = Label::createWithTTF("Loading....", "fonts/Marker Felt.ttf", 30);
	assert(label != nullptr);
	label->setPosition(Vec2(visibleSize.width - label->getContentSize().width,
		label->getContentSize().height));

	this->addChild(label, -1);

	//create loadingbar
	auto sprite = Sprite::create("Scene/Loading/loading bar.jpg");
	assert(sprite != nullptr);
	sprite->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	sprite->setScale(0.6);

	this->addChild(sprite, -1);
}