#pragma once
#include"cocos2d.h"
#include"Object/Map/Normal.h"

//模式 多人混战，地图 墓地
class Tomb: public Normal
{
public:
	Tomb();
	~Tomb();
	virtual bool init();
	MAP_CREATE_FUN(Tomb);
protected:
};

