#pragma once
#include "cocos2d.h"
#include"MyMap.h"
#include"MySprite.h"

class MySprite;
class MyBomb :public cocos2d::Sprite
{                          
public:
	MyBomb();
	static MyBomb* create(MySprite*,cocos2d::Scene* scene, MyMap* map);
	MyBomb(MySprite* sprite,cocos2d::Scene* scene,MyMap* map);
	void plantBomb(cocos2d::Vec2 pos);
	void  explode();
	void MyRemove(int a, int b);
	void creatWater(cocos2d::Vec2 pos);
    MySprite* m_man;
	MyMap* m_map;
	cocos2d::Scene* m_scene;
	std::string m_picFilename_bomb, m_picFilename_water;
};

