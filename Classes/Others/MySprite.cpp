#include "MySprite.h"
#include"every.h"
#include"Msg.h"
USING_NS_CC;

#define SETKEY(keycode) m_bkey.w = false;\
m_bkey.s = false;\
m_bkey.a = false;\
m_bkey.d = false;\
m_bkey.keycode = true;\


MySprite::MySprite()
{
	m_number = 0;
}
MySprite::MySprite(std::string picFilename_bomb,std::string picFilename_water)
	    :m_picFilename_bomb(picFilename_bomb),m_picFilename_water(picFilename_water)
{
	m_speed =0.12f;
	m_bombNum = 0;
	m_maxbombNum = 5;
	m_bombWidth = 2;
	m_bmove= false;
	m_life = 1;
	//创建炸弹动画
	Texture2D *bombPlay = Director::getInstance()->getTextureCache()->addImage(m_picFilename_bomb);
	Vector<SpriteFrame *> animFrames(14);
	for (int i = 0; i <3; ++i) {
		SpriteFrame* frame = SpriteFrame::createWithTexture(bombPlay, Rect(72 * i, 0, 72, 72));
		animFrames.pushBack(frame);
	}
	m_animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
    m_animation->retain(); 

	//每0.1s刷新，判断移动
	schedule(schedule_selector(MySprite::myUpdate), m_speed);
}

MySprite* MySprite::create(const char*filename,std::string picFilename_bomb, std::string picFilename_water)
{
	MySprite* sprite = new MySprite(picFilename_bomb,picFilename_water);
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease(); 
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void MySprite::walk()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](EventKeyboard::KeyCode keycode, Event * event) {
		if (m_life == 0) return; //死亡后不再监听
		EventKeyboard::KeyCode W = EventKeyboard::KeyCode::KEY_W;
		EventKeyboard::KeyCode S = EventKeyboard::KeyCode::KEY_S;
		EventKeyboard::KeyCode D = EventKeyboard::KeyCode::KEY_D;
		EventKeyboard::KeyCode A = EventKeyboard::KeyCode::KEY_A;
		if (keycode == W) { SETKEY(w) }
		if (keycode == S) { SETKEY(s) }
		if (keycode == D) { SETKEY(d) }
		if (keycode == A) { SETKEY(a) }
	};

	listener->onKeyReleased = [this](EventKeyboard::KeyCode keycode, Event * event) {
		if (m_life == 0) return; //死亡后不再监听
		EventKeyboard::KeyCode W = EventKeyboard::KeyCode::KEY_W;
		EventKeyboard::KeyCode S = EventKeyboard::KeyCode::KEY_S;
		EventKeyboard::KeyCode D = EventKeyboard::KeyCode::KEY_D;
		EventKeyboard::KeyCode A = EventKeyboard::KeyCode::KEY_A;
		if (keycode == W) { m_bkey.w = false; }
		if (keycode == S) { m_bkey.s = false; }
		if (keycode == D) { m_bkey.d = false; }
		if (keycode == A) { m_bkey.a = false; }
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void MySprite::plantBomb()
{
	auto listener1 = EventListenerKeyboard::create();
	listener1->onKeyPressed = [this](EventKeyboard::KeyCode keycode, Event * event) {
		if (keycode == EventKeyboard::KeyCode::KEY_SPACE && m_bombNum<m_maxbombNum)
		{
			if (m_life == 0) return; //死亡后不再监听
			Vec2 pos = getPosition();
			SendMsg_Bomb(pos.x, pos.y);  
			Sleep(50);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
}


void MySprite::Mydelete()
{
	m_animation->release();
	removeFromParent();
	return;
}

void MySprite::myUpdate(float tmd)
{
	//每0.1s，刷新一次，目前只加了移动系统
	if (m_bkey.w) {
		SendMsg_Walk(0, 40);
	}
	if (m_bkey.s) {
		SendMsg_Walk(0, -40);
	}
	if (m_bkey.a) {
		SendMsg_Walk(-40, 0);
	}
	if (m_bkey.d) {
		SendMsg_Walk(40, 0);
	}
}