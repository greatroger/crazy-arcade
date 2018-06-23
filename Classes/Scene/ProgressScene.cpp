#include "ProgressScene.h"
#include"Scene/RoomScene.h"
#include"Scene/GameScene.h"

USING_NS_CC;

ProgressScene::ProgressScene()
{
}

ProgressScene::~ProgressScene()
{
}

bool ProgressScene::init()
{
	return true;
}

void ProgressScene::start(int ID)
{
	m_mapID = ID;
	Music::stopMusic();
	scheduleOnce(schedule_selector(ProgressScene::updateEachSecond5), 1.0f);
	scheduleOnce(schedule_selector(ProgressScene::updateEachSecond4), 2.0f);
	scheduleOnce(schedule_selector(ProgressScene::updateEachSecond3), 3.0f);
	scheduleOnce(schedule_selector(ProgressScene::updateEachSecond2), 4.0f);
	scheduleOnce(schedule_selector(ProgressScene::updateEachSecond1), 5.0f);
	scheduleOnce(schedule_selector(ProgressScene::updateEachSecond), 6.0f);
}

void ProgressScene::updateEachSecond5(float dt)
{
	auto visiblesize = Director::getInstance()->getVisibleSize();
	auto label = Label::createWithTTF("5", "fonts/Marker Felt.ttf", 200);
	label->setPosition(visiblesize.width / 2, visiblesize.height/2 );
	addChild(label, 0);
}

void ProgressScene::updateEachSecond4(float dt)
{
	removeAllChildren();
	auto visiblesize = Director::getInstance()->getVisibleSize();
	auto label = Label::createWithTTF("4", "fonts/Marker Felt.ttf", 200);
	label->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	addChild(label, 0);
}

void ProgressScene::updateEachSecond3(float dt)
{
	removeAllChildren();
	auto visiblesize = Director::getInstance()->getVisibleSize();
	auto label = Label::createWithTTF("3", "fonts/Marker Felt.ttf", 200);
	label->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	addChild(label, 0);
}

void ProgressScene::updateEachSecond2(float dt)
{
	removeAllChildren();
	auto visiblesize = Director::getInstance()->getVisibleSize();
	auto label = Label::createWithTTF("2", "fonts/Marker Felt.ttf", 200);
	label->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	addChild(label, 0);
}
void ProgressScene::updateEachSecond1(float dt)
{
	removeAllChildren();
	auto visiblesize = Director::getInstance()->getVisibleSize();
	auto label = Label::createWithTTF("1", "fonts/Marker Felt.ttf", 200);
	label->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	addChild(label, 0);
}

void ProgressScene::updateEachSecond(float dt)
{
	removeAllChildren();
	auto visiblesize = Director::getInstance()->getVisibleSize();
	auto label = Label::createWithTTF("START", "fonts/Marker Felt.ttf", 200);
	label->setPosition(visiblesize.width / 2, visiblesize.height / 2);
	addChild(label, 0);

	Music::PlayMusic(Music::start);

	auto scene = GameScene::create();
	scene->start(m_mapID);
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}




