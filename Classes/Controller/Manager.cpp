#include"Object/MyMap.h"
#include"Network/Msg.h"
#include"cocos2d.h"

namespace Manager{
	void getMap(MyMap*);
}

void Manager::getMap(MyMap* map)
{
	for (int i = 0; i <= map->getMapSize().width; ++i)
	{
		for (int j = 0; j <= map->getMapSize().height; ++i)
		{
			using cocos2d::Vec2;
			Vec2 pos = map->tileCoordToPosition(Vec2(i, j));
			if (map->ifCanDamage(pos))
			{
				SendMsg_Map(i, j);
			}
		}
	}
	SendMsg_Map(-1, -1);
}