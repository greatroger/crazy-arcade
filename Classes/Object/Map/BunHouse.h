#pragma once
#include"Object/Map/MyMap.h"
#include"cocos2d.h"
#include"Global/Player.h"
// 抢包子模式
class BunHouse :public MyMap
{
public:
	BunHouse() {};
	~BunHouse() {};
	MAP_CREATE_FUN(BunHouse);
private:
	cocos2d::Vec2 m_bunpos[2];
	bool init();
	void start();
	void bunCreate();
	void update(float det);
	void checkOver();
	void checkBun();
	void checkEat();
	void checkDead();
	void reborn(Player * player);
	int m_maxBunNum;

	cocos2d::Vec2 bornPlace[4] = {
		cocos2d::Vec2(20 + 22 * 40,660),
		cocos2d::Vec2(100,60),
		cocos2d::Vec2(0,0),
		cocos2d::Vec2(0,0),
	};
};