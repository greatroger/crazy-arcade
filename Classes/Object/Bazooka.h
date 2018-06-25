#pragma once
#include"cocos2d.h"
#include"Object/Bomb.h"

//火箭炸弹类
//包含火箭的发射的炸弹的生成与销毁函数
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
