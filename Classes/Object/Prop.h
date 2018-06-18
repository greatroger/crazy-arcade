#pragma once
#include"cocos2d.h"
#include"Object/Bomb.h"

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
};



class Bazooka: public Bomb
{
public:
	Bazooka() {};
	~Bazooka() {};
	static Bazooka* create();
	void update(float det);
	void explode();
	void start();
};
