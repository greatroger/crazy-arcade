#pragma once
#include"cocos2d.h"
#include"ui\UIButton.h"
class RoomSetting:public cocos2d::Layer
{
public:
	CREATE_FUNC(RoomSetting);
	RoomSetting();
	~RoomSetting();
	bool init();
	void update(float det);
	void checkStart();
	void addBackground();
	void onTouchEnter(Ref * pSender, cocos2d::ui::Widget::TouchEventType type);
	void changeMap();
	void createReadyButton();
	void createMapButton();
	void menuMapCallback(cocos2d::Ref * pSender);
	void createPatternButton();
	void menuPatternCallback(cocos2d::Ref * pSender);
	void createBackButton();
	void menuBackCallback(cocos2d::Ref * pSender);
private:
	int m_mapID, m_modeID;
	cocos2d::ui::Button *m_readyButton;
	bool isready;
};

