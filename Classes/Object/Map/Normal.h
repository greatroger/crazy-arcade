#pragma once
#include"Object/Map/MyMap.h"
#include"Global/Player.h"
#include"Global/Global.h"
#include"cocos2d.h"

//普通多人混战模式
class Normal:public MyMap
{
public:
	Normal();
	~Normal();
	MAP_CREATE_FUN(Normal);
	bool init();
virtual	void start();
	void update(float det);
	void checkOver();
	void checkDead();
	void DeadAudioPlay();
	void reborn(Player * player);
protected:
	cocos2d::Vec2 bornPlace[4] = {
		cocos2d::Vec2(20,20),
		cocos2d::Vec2(20,740),
		cocos2d::Vec2(0,0),
		cocos2d::Vec2(0,0),
	};
};

