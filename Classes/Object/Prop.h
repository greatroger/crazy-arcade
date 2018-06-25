#pragma once
#include"cocos2d.h"
#include"Global/Player.h"
//������
//Ŀǰ���߰��� Ь�ӣ�ˮ�ݣ�ҩˮ����������
class Prop: public cocos2d::Sprite
{
public:
	Prop(int type);
	~Prop();
	static Prop* create(int type);
	static enum Type { shoes, powerliquid, bombliquid, bazooka, stopwatch,MaxNum};
private:
	void update(float det);
    int m_type;
};

//������
//�������ӵ�ʰȡ����亯��
class Bun : public cocos2d::Sprite
{
public:
	Bun(int type);
	~Bun() {};
	static Bun* create(int type);
	static void getBun(Player* player, int type);
	static void loseBun(Player* player);
	static std::list<Bun*> bunList;
private:
	void update(float det);
	int m_type;
	constexpr static float m_speed = 0.2f;
};



