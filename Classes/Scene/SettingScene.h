#pragma once
#include"cocos2d.h"

class SettingScene :public cocos2d::Scene
{
public:
	SettingScene();
	~SettingScene();
	bool init();
	void addBackground();
	void addButton();
	void menuMusicOnCallback(cocos2d::Ref * pSender);
	void createBackButton();
	void menuBackCallback(cocos2d::Ref * pSender);
	CREATE_FUNC(SettingScene);

private:
	cocos2d::MenuItemLabel* m_music;
};

