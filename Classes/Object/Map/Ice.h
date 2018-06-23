#pragma once
#pragma once
#include"cocos2d.h"
#include"Object/Map/Normal.h"

//模式 多人混战，地图 冰雪
class Ice : public Normal
{
public:
	Ice();
	~Ice();
	virtual bool init();
	MAP_CREATE_FUN(Ice);
protected:
};
