#include"MySprite.h"
#include"MyBomb.h"
#include"every.h"

Player player1("sprite/redsprite.png", "sprite/redbomb.png", "sprite/redsprite.png"), 
       player2("sprite/bluesprite.png", "sprite/bluebomb.png", "sprite/bluewater.png"), 
	   player3, player4;

std::map<std::string, Player*> Players;
std::list<MyBomb*> g_list_bomb;
std::vector<MySprite*> g_vector_sprite;
bool g_bstart = false;
std::string g_name;
MySprite * g_sprite;
