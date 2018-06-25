#include "HelpScene.h"
#include "Scene/StartScene.h"

USING_NS_CC;

bool HelpScene::init()
{

	createBackButton();

	bg01Init();
    auto keyEventListener = EventListenerKeyboard::create();
    keyEventListener->onKeyReleased = [](EventKeyboard::KeyCode code, Event* event)
    {
        if (code == EventKeyboard::KeyCode::KEY_ESCAPE)
        {
			Director::getInstance()->replaceScene(TransitionFade::create(0.6, StartScene::create()));
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyEventListener, this);
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch * t, Event *e)
	{
		return true;
	};
	listener->onTouchEnded = [this](Touch *t, Event *e)
	{
		if (m_bgint == 1)
		{
			bg02Init(); 
			removeChildByTag(1);
			return;
		}
		if (m_bgint == 2)
		{
			bg03Init();
			removeChildByTag(2);
			return;
		}
		if (m_bgint == 3)
		{
			bg02Init();
			removeChildByTag(3);
			return;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void HelpScene::bg01Init()
{
	m_bgint = 1;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2  origin = Director::getInstance()->getVisibleOrigin();
	auto bg = Sprite::create("Scene/Help/help01.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bg->setScale(1.4);
	this->addChild(bg,1.1);
}

void HelpScene::bg02Init()
{
	m_bgint = 2;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2  origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("Scene/Help/help02.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bg->setScale(1.4);
	this->addChild(bg,2,2);
}

void  HelpScene::bg03Init()
{
	m_bgint = 3;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2  origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("Scene/Help/help03.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bg->setScale(1.4);
	this->addChild(bg,3,3);
}


void HelpScene::createBackButton() {                                
    const auto buttons = Menu::create();

    const auto backButton=MenuItemLabel::create(
        Label::createWithTTF("Back", "fonts/Quicksand-Bold.ttf", 50),
        CC_CALLBACK_1(HelpScene::menuBackCallback, this));

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto baseY = visibleSize.height * 0.85f;

    backButton->setPosition(backButton->getContentSize().width / 2+860, baseY + 10);

    buttons->addChild(backButton, 1);

    buttons->setPosition(0, 0);

	addChild(buttons,5);
}


void HelpScene::menuBackCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.6, StartScene::create()));
}