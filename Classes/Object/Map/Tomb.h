#pragma once
#include"cocos2d.h"
#include"Object/Map/Normal.h"

//ģʽ ���˻�ս����ͼ Ĺ��
class Tomb: public Normal
{
public:
	Tomb();
	~Tomb();
	virtual bool init();
	MAP_CREATE_FUN(Tomb);
protected:
};

