#pragma once
#pragma once
#include"cocos2d.h"
#include"Object/Map/Normal.h"

//ģʽ ���˻�ս����ͼ ��ѩ
class Ice : public Normal
{
public:
	Ice();
	~Ice();
	virtual bool init();
	MAP_CREATE_FUN(Ice);
protected:
};
