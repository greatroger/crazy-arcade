#pragma once
#include"cocos2d.h"
#include"Object/Bomb.h"

//���ը����
//��������ķ����ը�������������ٺ���
class Bazooka : public Bomb
{
public:
	Bazooka() {};
	~Bazooka() {};
	static Bazooka* create();
	void start(MyMap* map);
private:
	void update(float det);
	void explode();
};
