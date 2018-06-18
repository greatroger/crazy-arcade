#pragma once
#include"cocos2d.h"
#include "ui/UIListView.h"
#include "extensions/cocos-ext.h"  
#include"ui/UIButton.h"

class ChatBox :public cocos2d::Layer
{
public:
	CREATE_FUNC(ChatBox);
	ChatBox();
	~ChatBox();
	bool init();
	void update(float det);
	void createChatBox();
	void menuSendCallback(cocos2d::Ref * pSender);
	void updataMessage();
private:
	cocos2d::ui::ListView *boxHistory;
	cocos2d::ui::EditBox *msgInput;
};

