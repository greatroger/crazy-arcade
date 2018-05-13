#include "MyMap.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


MyMap::MyMap()
{
}

MyMap * MyMap::create(const std::string& tmxFile)
{
	MyMap *ret = new (std::nothrow) MyMap();
	if (ret->initWithTMXFile(tmxFile))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool MyMap::init()
{
	//创建地图
	m_nomoveLayer = getLayer("nomove");
	m_removeLayer = getLayer("remove");
	m_buildingLayer = getLayer("building");
	m_backgroundLayer = getLayer("background");

	m_gid_nomove = m_nomoveLayer->getTileGIDAt(Vec2(0,0));
	m_gid_remove = m_removeLayer->getTileGIDAt(Vec2(0, 0));

	//将背景调至最低层
	m_backgroundLayer->removeFromParent();
	addChild(m_backgroundLayer, -1);
	m_buildingLayer->removeFromParent();
	addChild(m_buildingLayer, 1);
	return true;
}


bool MyMap::remove(Vec2 position)  //用来判断炸弹可否移除物体，如果可以，则移除，（后期考虑重构）
{
	Point tileCoord = tileCoordFromPosition(position);
	unsigned int gid = m_removeLayer->getTileGIDAt(tileCoord);
	if (gid > 0)
	{
		//移除物体
		m_removeLayer->removeTileAt(tileCoord);
		m_nomoveLayer->removeTileAt(tileCoord);
		m_buildingLayer->removeTileAt(tileCoord);
		position.y += 40;
	    tileCoord = tileCoordFromPosition(position);
	    m_buildingLayer->removeTileAt(tileCoord);
		return true;
	}
	return false;
}

Point MyMap::tileCoordFromPosition(Point pos)  //屏幕坐标转瓦片坐标
{
	int x = pos.x / getTileSize().width;

	int y = ((getMapSize().height * getTileSize().height) - pos.y) /
		getTileSize().height;   
	return Point(x, y);

}

Vec2 MyMap::positionFromTileCoord(Point pos)  //瓦片坐标转屏幕坐标
{
	int x = (pos.x+0.5) * getTileSize().width;
	int y = (getMapSize().height- pos.y-0.5) * getTileSize().height;
	return Vec2(x, y);
}

bool MyMap::bnoMove(Vec2 position)    //判断可否移动
{
	Point tileCoord = tileCoordFromPosition(position);

	unsigned int gid = m_nomoveLayer->getTileGIDAt(tileCoord);
    if (gid > 0) return true;
	return false;
}
