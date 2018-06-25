#ifndef __SCENE_HELPSCENE_H__
#define __SCENE_HELPSCENE_H__

#include "cocos2d.h"
#include"ui/UIButton.h"

class HelpScene : public cocos2d::Scene
{
private:
	void menuBackCallback(cocos2d::Ref* pSender);
	void bg01Init();
	void bg02Init();
	void bg03Init();
	void createBackButton();
	int  helpOn;
public:
    virtual bool init();
    CREATE_FUNC(HelpScene);
	int m_bgint;
};

#endif // __HELP_SCENE_H__