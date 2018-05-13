#pragma once
#include "cocos2d.h"
#include"every.h"

class WaitScene:public cocos2d::Scene
{
public:
	WaitScene();
	CREATE_FUNC(WaitScene);
	void update(float delta);
	bool init();
	MyMap* m_map;
};

