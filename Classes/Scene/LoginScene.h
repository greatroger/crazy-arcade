#pragma once
#include"cocos2d.h"
#include "extensions\cocos-ext.h"  

class LoginScene :public cocos2d::Scene
{
public:
	LoginScene();
	~LoginScene();

	CREATE_FUNC(LoginScene);
	bool init();
private:
	cocos2d::ui::EditBox *usernameInput, *IPAddressInput;
	void update(float det);
	void checkLogin();
	void addInputBox();
	void addBackground();
	void addLoginButton();
};

