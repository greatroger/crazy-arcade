#pragma once
#include"cocos2d.h"
#include"Global/Player.h"

class Pop : public cocos2d::Sprite
{
public:
	Pop(Player* player);
	~Pop();
	static Pop* create(Player* player);
	void update(float det);
static	void getInPop(Player * player);
	void puncturePop(int team);
private:
	int m_team;
	Player* m_player;
};
