#pragma once
#include"cocos2d.h"
#include"Object/GameMap.h"

//游戏场景类
//在游戏场景中加载游戏地图
//检测玩家移动，玩家受伤，游戏结束
class GameScene:public cocos2d::Scene
{
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	bool init();
	void start(int mapID);
private:
	void update(float delta);
	void walkUpdate(float tmd);
	void addMap(int mapID);
	void addSprite();
	void addManager();
	void checkOver();
	void checkPop();
	MyMap *m_map;
};

