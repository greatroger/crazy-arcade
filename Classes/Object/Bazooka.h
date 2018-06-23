#pragma once
#include"cocos2d.h"
#include"Object/Bomb.h"

class Bazooka : public Bomb
{
public:
	Bazooka() {};
	~Bazooka() {};
	static Bazooka* create();
	void update(float det);
	void explode();
	void start(MyMap* map);
};
