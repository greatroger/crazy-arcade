#pragma once
#include"cocos2d.h"
#include"Object/Map/MyMap.h"
#include"Global/Player.h"

//炸弹类
//包含炸弹的产生与销毁，以及对玩家造成伤害的函数

class Bomb : public cocos2d::Sprite
{
public:
	Bomb();
	~Bomb();
	CREATE_FUNC(Bomb);
	virtual void start(cocos2d::Vec2 pos, Player* player,MyMap* map);
    virtual	void explode();
	void Remove(int a, int b);
	void creatWater(cocos2d::Vec2 pos);
	void hurtPlayer(cocos2d::Vec2 pos);
protected:
	int m_width;
	static std::list<Bomb*> bombList;
	MyMap* m_map;
	std::string m_picBomb, m_picWater;
private:
	Player* m_player;
};

