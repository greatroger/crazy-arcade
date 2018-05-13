#pragma once
#include"MySprite.h"
class Player
{
public:
	Player(std::string,std::string,std::string);
	Player();
	MySprite* creatSprite();
	std::string m_name;
	MySprite * m_sprite;
	int m_number;
	cocos2d::Vec2 msg_walk_pos, msg_bomb_pos;
	std::string m_picFilename_sprite,m_picFilename_bomb, m_picFilename_water;
	bool m_bchange,m_bdead;
};