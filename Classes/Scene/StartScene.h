#include"cocos2d.h"
class StartScene:public cocos2d::Scene
{
public:
	StartScene();
	~StartScene();
	CREATE_FUNC(StartScene);
	bool init();
	void addBackground();
	void addButton();
private:

};
