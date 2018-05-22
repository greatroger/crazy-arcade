#pragma once
#include"cocos2d.h"
class StartScene:public cocos2d::Scene
{
public:
	StartScene();
	~StartScene();
	CREATE_FUNC(StartScene);
	bool init();
	void addBackground();
	void menuPlayCallback(cocos2d::Ref * pSender);
	void menuSettingsCallback(cocos2d::Ref * pSender);
	void menuHelpCallback(cocos2d::Ref * pSender);
	void menuExitCallback(Ref * pSender);
	void addButton();
private:

};
