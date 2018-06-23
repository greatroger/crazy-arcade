#include"cocos2d.h"

class LoadingScene:public cocos2d::Scene
{
public:
	LoadingScene();
	~LoadingScene();
	CREATE_FUNC(LoadingScene);
	bool init();

private:
	bool load();
	void endLoad(float dt);
	void addBackground();
	void MusicLoad();
};

