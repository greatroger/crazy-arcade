#pragma once
#include"Object/Map/MyMap.h"
#include"Global/Player.h"
#include"Global/Global.h"

namespace GameMap
{
	enum map {
		Village, Tomb, BunHouse
	};
	MyMap* create(int mapID);

	void DeadAudioPlay(cocos2d::Sprite* layer);
}


