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
	void update(float det);
	void checkPickupBun();
	void checkLoseBun();
	void checkEat();
	void checkDead();
	void reborn(Player * player);
	bool ifInHouse(cocos2d::Vec2 pos, int team);
	int m_maxBunNum;
    int m_bunNum[2] = { 0,0 };
protected:
	cocos2d::Vec2 bornPlace[4] = {
		cocos2d::Vec2(140,340),
		cocos2d::Vec2(900,340),
		cocos2d::Vec2(140,420),
		cocos2d::Vec2(900,420),
	};
};