#pragma once
#include"cocos2d.h"
#include"Object/GameMap.h"
class GameScene:public cocos2d::Scene
{
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	bool init();
	void start(int mapID);
	void update(float delta);
private:
	void addMap(int mapID);
	void addSprite();
	void addManager();
	void checkOver();
	MyMap *m_map;
};
