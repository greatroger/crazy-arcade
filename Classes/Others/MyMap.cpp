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
	//������ͼ
	m_nomoveLayer = getLayer("nomove");
	m_removeLayer = getLayer("remove");
	m_buildingLayer = getLayer("building");
	m_backgroundLayer = getLayer("background");

	m_gid_nomove = m_nomoveLayer->getTileGIDAt(Vec2(0,0));
	m_gid_remove = m_removeLayer->getTileGIDAt(Vec2(0, 0));

	//������������Ͳ�
	m_backgroundLayer->removeFromParent();
	addChild(m_backgroundLayer, -1);
	m_buildingLayer->removeFromParent();
	addChild(m_buildingLayer, 1);
	return true;
}


bool MyMap::remove(Vec2 position)  //�����ж�ը���ɷ��Ƴ����壬������ԣ����Ƴ��������ڿ����ع���
{
	Point tileCoord = tileCoordFromPosition(position);
	unsigned int gid = m_removeLayer->getTileGIDAt(tileCoord);
	if (gid > 0)
	{
		//�Ƴ�����
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

Point MyMap::tileCoordFromPosition(Point pos)  //��Ļ����ת��Ƭ����
{
	int x = pos.x / getTileSize().width;

	int y = ((getMapSize().height * getTileSize().height) - pos.y) /
		getTileSize().height;   
	return Point(x, y);

}

Vec2 MyMap::positionFromTileCoord(Point pos)  //��Ƭ����ת��Ļ����
{
	int x = (pos.x+0.5) * getTileSize().width;
	int y = (getMapSize().height- pos.y-0.5) * getTileSize().height;
	return Vec2(x, y);
}

bool MyMap::bnoMove(Vec2 position)    //�жϿɷ��ƶ�
{
	Point tileCoord = tileCoordFromPosition(position);

	unsigned int gid = m_nomoveLayer->getTileGIDAt(tileCoord);
    if (gid > 0) return true;
	return false;
}
