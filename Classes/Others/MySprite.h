#pragma once
#include "cocos2d.h"
#include "MyMap.h"
#include"MyBomb.h"


class MySprite :public cocos2d::Sprite
{
private: 
	struct BKeyPressed
	{
		bool w = false, s = false, d = false, a = false;
	};
public:
	MySprite();
	static MySprite* create(const char*,std::string picFilename_bomb, std::string picFilename_water);//жиди 
	MySprite(std::string picFilename_bomb,std::string picFilename_water);
	void myUpdate(float tmd);
	void Mydelete();
	void walk();
	void plantBomb();
	int  m_maxbombNum,m_bombNum,m_bombWidth;
	int m_life;
	bool m_bmove;
	float m_speed;
	int m_number;
	cocos2d::Animation* m_animation;
	BKeyPressed m_bkey;
	std::string m_picFilename_bomb, m_picFilename_water;
};


