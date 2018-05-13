#pragma once
#include "cocos2d.h"
#include "every.h"

class GameScene:public cocos2d::Scene
{
public:
	GameScene();
	CREATE_FUNC(GameScene);
	void update(float delta);
	bool init();
	MyMap* m_map;
};

