#pragma once
#include"cocos2d.h"
#include"Global/Player.h"
#include"Object/MyMap.h"

class GameController:public cocos2d::Layer
{
public:
	GameController();
	~GameController();
	void start(Player*, MyMap*);
	CREATE_FUNC(GameController);
	void update(float det);
private:
	struct isKeyPressed
	{
		bool w = false, s = false, d = false, a = false;
	};
	
	isKeyPressed m_bkey;
	void walkUpdate(float tmd);
	bool ifCanMove(cocos2d::Vec2&);
	void startSpaceListener();
	void startKeyEListener();
	bool ifcanBomb(cocos2d::Vec2);
	void startWalkListener();
	float m_speed;
	Player* m_player;
	MyMap* m_map;
};

