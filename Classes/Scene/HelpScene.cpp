#include"Scene/HelpScene.h"
#include"Scene/StartScene.h"
USING_NS_CC;

HelpScene::HelpScene()
{
}


HelpScene::~HelpScene()
{
}

bool HelpScene::init()
{
	addBackground();
	return true;
}

bool HelpScene::onTouchEnter(Touch*touch, Event* event)
{
	return true;
}

bool HelpScene::onTouchEnded(Touch*touch, Event* event)
{
	auto bg = getChildByTag(1);
	Sprite* sprite = static_cast<Sprite*>(bg);
	sprite->setTexture("Player/red/sprite.png");
	return true;
}

void HelpScene::addBackground()
{
	auto bg = Sprite::create("Scene/Start/button_normal.png");
	assert(bg != nullptr);
	auto visiblesize = Director::getInstance()->getVisibleSize();
	bg->setPosition(visiblesize.width / 2, 100);
	addChild(bg, 5,1);
	bg->setTag(1);
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelpScene::onTouchEnter,this);

	listener->onTouchEnded = CC_CALLBACK_2(HelpScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}

