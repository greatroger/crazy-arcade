#pragma once
#include"cocos2d.h"
#include"ui/UIButton.h"
#include "ui/UIListView.h"
#include "extensions/cocos-ext.h"  


class RoomScene :public cocos2d::Scene
{
public:
	RoomScene();
	~RoomScene();
	CREATE_FUNC(RoomScene);
	bool init();
	void update(float det);
/*	bool pictureChangeNormal();
	bool pictureChangeSelected();*/

	void readyCallback(cocos2d::Ref * pSender);

	void createTitle();

	void creatCharacter();

	void initUIBox();
	void clickmeCallback(cocos2d::Ref * pSender);
	void createChatBox();
	void updataMessage();
	void createBackButton();
	void createSettingButton();

	void menuSettingCallback(cocos2d::Ref * pSender);
	void menuBackCallback(cocos2d::Ref * pSender);

	void menuSendCallback(cocos2d::Ref * pSender);
	void checkConnect();
	void createBackground();
private:
	cocos2d::ui::ListView *boxHistory;
	cocos2d::ui::EditBox *msgInput;
	bool isEnter;
};