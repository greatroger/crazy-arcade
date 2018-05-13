#pragma once
#include"MySprite.h"
#include"MyBomb.h"
#include"Player.h"


extern Player player1,player2, player3, player4;

extern bool g_bstart;
extern Player *g_Player;
extern MySprite * g_sprite;
extern std::string g_name;

extern std::map<std::string,Player*> Players;
extern std::list<MyBomb*> g_list_bomb;
extern std::vector<MySprite*> g_vector_sprite;

const cocos2d::Vec2 bornPos[4]
{ cocos2d::Vec2(60, 180),cocos2d::Vec2(60+800, 180+400),cocos2d::Vec2(60, 180),cocos2d::Vec2(60, 180) };


template <class container>
typename container::iterator myFind(container &con, cocos2d::Vec2 pos)
{
	for (typename container::iterator  it = con.begin(); it != con.end(); ++it)
	{
		if ((*it)->getPosition() == pos)
			return it;
	}
	return con.end();
}