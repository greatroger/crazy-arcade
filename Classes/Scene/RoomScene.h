#pragma once
#include"cocos2d.h"
#include"ui/UIButton.h"
#include "ui/UIListView.h"
#include "extensions/cocos-ext.h"  
#include"Scene/RoomSetting.h"
#include"Scene/Room/PopupLayer.h"

class RoomScene :public cocos2d::Scene
{
public:
	RoomScene();
	~RoomScene();
	CREATE_FUNC(RoomScene);
	bool init();
	void update(float det);

	void readyCallback(cocos2d::Ref * pSender);

	void createTitle();

	void creatCharacter();

	void initUIBox();
	void CancleCallback(Ref * pSender);
	void clickmeCallback(cocos2d::Ref * pSender);
	void createBackButton();
	void createSettingButton();

	void menuSettingCallback(cocos2d::Ref * pSender);
	void menuBackCallback(cocos2d::Ref * pSender);

	void OKCallback(Ref * pSender);

	void checkConnect();

	void checkCharacter();

	void createBackground();
private:
	cocos2d::ui::ListView *boxHistory;
	cocos2d::ui::EditBox *msgInput;
	bool isEnter;
	RoomSetting* settingLayer;
	//PopupLayer* quitLayer;
};