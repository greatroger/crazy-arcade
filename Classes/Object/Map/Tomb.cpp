#include "Tomb.h"

//墓地地图，目前未添加幽灵，以后有时间再填此坑

Tomb::Tomb()
{
}


Tomb::~Tomb()
{
}

bool Tomb::init()
{
	Normal::init();
	Normal::bornPlace[0] = cocos2d::Vec2(540, 20);
	Normal::bornPlace[1] = cocos2d::Vec2(20, 340);
	Normal::bornPlace[2] = cocos2d::Vec2(980, 420);
	Normal::bornPlace[3] = cocos2d::Vec2(460, 740);
	return true;
}

