#pragma once
#include"cocos2d.h"
#include"Global/Player.h"

class Pop : public cocos2d::Sprite
{
public:
	Pop(Player* player);
	~Pop();
	static Pop* create(Player* player);
    static void getInPop(Player * player);
	void puncturePop(int team);
private:
	void update(float det);
	int m_team;
	Player* m_player;
};
