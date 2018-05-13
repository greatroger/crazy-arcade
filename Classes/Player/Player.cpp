#include "Player.h"
#include"every.h"

Player::Player()
{

}
Player::Player(std::string picFilename_sprite, std::string picFilename_bomb,std::string picFilename_water)
	:m_picFilename_sprite(picFilename_sprite),m_picFilename_bomb(picFilename_bomb), m_picFilename_water(picFilename_water)

{
	m_number = 0;
	msg_walk_pos = cocos2d::Vec2(0, 0);
	msg_bomb_pos = cocos2d::Vec2(0, 0);
}

MySprite* Player::creatSprite()
{
	m_sprite = MySprite::create(m_picFilename_sprite.c_str(), m_picFilename_bomb, m_picFilename_water);
	m_bdead = false;
	m_bchange = false;
	m_sprite->setPosition(bornPos[m_number-1]);
	m_sprite->setScale(0.8);
	return m_sprite;
}

