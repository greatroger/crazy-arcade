#pragma once
#include"cocos2d.h"
#include"Object/Map/MyMap.h"
#include"Global/Player.h"

#include"Controller/GameController.h"

class PropManager :public cocos2d::Layer
{
public:
	PropManager();
	~PropManager();
	void start(MyMap * map,GameController*);
	CREATE_FUNC(PropManager);
private:

	Player *m_player;
	MyMap *m_map;
	GameController *m_gamecontroller;
	void pickupProp(int type,Player* player);
	void useProp(int type, Player * player);
	void useProp_bazooka(Player * player);
	void useProp_stopwatch(Player * player);
	void update(float det);
};

