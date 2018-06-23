#pragma once
#include"Object/Map/MyMap.h"
#include"cocos2d.h"
#include"Global/Player.h"
// ������ģʽ
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
	void checkOver();
	void checkBun();
	void checkEat();
	void checkDead();
	void reborn(Player * player);
	bool ifInHouse(cocos2d::Vec2 pos, int team);
	int m_maxBunNum;
protected:
	cocos2d::Vec2 bornPlace[4] = {
		cocos2d::Vec2(140,380-40),
		cocos2d::Vec2(900,380 - 40),
		cocos2d::Vec2(140,380+40),
		cocos2d::Vec2(900,380 + 40),
	};
};