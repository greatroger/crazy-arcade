#include "Ice.h"


Ice::Ice()
{
}


Ice::~Ice()
{
}

bool Ice::init()
{
	Normal::init();
	Normal::bornPlace[0] = cocos2d::Vec2(220, 100);
	Normal::bornPlace[1] = cocos2d::Vec2(780, 100);
	Normal::bornPlace[2] = cocos2d::Vec2(740, 580);
	Normal::bornPlace[3] = cocos2d::Vec2(180, 580);
	return true;
}
