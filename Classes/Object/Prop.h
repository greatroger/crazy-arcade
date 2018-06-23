#pragma once
#include"cocos2d.h"
#include"Global/Player.h"
class Prop: public cocos2d::Sprite
{
public:
	Prop(int type);
	~Prop();
	static Prop* create(int type);
	void update(float det);
	static enum Type { shoes, powerliquid, bombliquid, bazooka, stopwatch,MaxNum};
private:
    int m_type;
};

class Bun : public cocos2d::Sprite
{
public:
	Bun(int type);
	~Bun() {};
	static Bun* create(int type);
	void update(float det);
	static void getBun(Player* player, int type);
	static void loseBun(Player* player);
private:
	int m_type;
	constexpr static float m_speed = 0.2f;
};



