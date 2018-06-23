#pragma once
#include<cocos2d.h>
class ProgressScene:public cocos2d::Scene
{
public:
	ProgressScene();
	~ProgressScene();
	CREATE_FUNC(ProgressScene);
	
	bool init();
    void updateEachSecond5(float dt);
	void updateEachSecond4(float dt);
	void updateEachSecond3(float dt);
	void updateEachSecond2(float dt);
	void updateEachSecond1(float dt);
	void updateEachSecond(float dt);
;	void start(int mapID);
private:
	int m_mapID;
};

