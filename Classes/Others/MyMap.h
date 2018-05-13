#pragma once
#include "cocos2d.h"


class MyMap :public cocos2d::TMXTiledMap
{
public:
	static MyMap * create(const std::string& tmxFile);
	MyMap();
	bool init();
	bool remove(cocos2d::Vec2 position);
	bool bnoMove(cocos2d::Vec2 position);
	cocos2d::Point tileCoordFromPosition(cocos2d::Point position);
	cocos2d::Vec2 positionFromTileCoord(cocos2d::Point position);
	int m_gid_nomove, m_gid_remove;
	cocos2d::TMXLayer *m_nomoveLayer, *m_removeLayer, *m_buildingLayer,*m_backgroundLayer;
};


