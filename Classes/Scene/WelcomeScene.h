#pragma once
#include "cocos2d.h"
#include "extensions\cocos-ext.h"  

class WelcomeScene :public cocos2d::Scene
{
public:
	WelcomeScene();
	CREATE_FUNC(WelcomeScene);
	cocos2d::ui::EditBox *m_name,*m_IP;
	
	bool bconnect=false;
};

