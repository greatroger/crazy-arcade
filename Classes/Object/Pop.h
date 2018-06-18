#pragma once
#include"cocos2d.h"
#include"Global/Player.h"

class Pop : public cocos2d::Sprite
{
public:
	Pop(int type, Player* player);
	~Pop();
	static Pop* create(int type, Player* player);
	void update(float det);
	void puncturePop(int team);
	void audioPlay();
private:
	int m_team;
	Player* m_player;
};
