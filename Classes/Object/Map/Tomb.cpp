#include "Tomb.h"

//Ĺ�ص�ͼ��Ŀǰδ������飬�Ժ���ʱ������˿�

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

