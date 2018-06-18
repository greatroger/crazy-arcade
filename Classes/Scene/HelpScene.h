#pragma once
#include"cocos2d.h"
class HelpScene:public cocos2d::Scene
{
public:
	HelpScene();
	~HelpScene();
	CREATE_FUNC(HelpScene);
	bool init();
	void addBackground();
	bool onTouchEnter(cocos2d::Touch * touch, cocos2d::Event * event);
	bool onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event);
};

