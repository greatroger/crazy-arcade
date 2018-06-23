#include"Object/Map/MyMap.h"
#include"Network/Msg.h"
#include"Object/Prop.h"
USING_NS_CC;

MyMap::MyMap()
{
}

MyMap::~MyMap()
{
}

void MyMap::Myinit()
{
	assert(getLayer("nomove") != nullptr);
	m_nomoveLayer = getLayer("nomove");
	assert(getLayer("remove") != nullptr);
	m_removeLayer = getLayer("remove");
	assert(getLayer("building") != nullptr);
	m_buildingLayer = getLayer("building");
	assert(getLayer("background") != nullptr);
	m_backgroundLayer = getLayer("background");
	assert(getLayer("building top") != nullptr);
	m_building_topLayer = getLayer("building top");
	assert(getLayer("building top top") != nullptr);
	m_building_top_topLayer = getLayer("building top top");

	m_building_top_topLayer->setZOrder(12);
	m_building_topLayer->setZOrder(11);
	m_buildingLayer->setZOrder(10);
	m_backgroundLayer->setZOrder(-1);
	auto Size = getMapSize();
	for (int i = 0; i <= Size.width; ++i)
	{
		for (int j = 0; j <= Size.height; ++j)
		{
			m_gid_nomove = m_nomoveLayer->getTileGIDAt(Vec2(i, j));
			if (m_gid_nomove > 0)break;
		}
		if (m_gid_nomove > 0)break;
	}

	for (int i = 0; i <= Size.width; ++i)
	{
		for (int j = 0; j <= Size.height; ++j)
		{
			m_gid_remove = m_removeLayer->getTileGIDAt(Vec2(i, j));
			if (m_gid_remove > 0)break;
		}
		if (m_gid_remove > 0)break;
	}
}

bool MyMap::init()
{
	return true;
}


Vec2 MyMap::positionToTileCoord(Vec2 pos)  //屏幕坐标转瓦片坐标
{
	int x = pos.x / getTileSize().width;
	int y = ((getMapSize().height * getTileSize().height) - pos.y) /
		getTileSize().height;
	return Vec2(x, y);

}

Vec2 MyMap::tileCoordToPosition(Vec2 pos)  //瓦片坐标转屏幕坐标
{
	int x = (pos.x + 0.5) * getTileSize().width;
	int y = (getMapSize().height - pos.y - 0.5) * getTileSize().height;
	return Vec2(x, y);
}

bool MyMap::ifCanMove(Vec2 pos)    //判断可否移动
{
	Vec2 tileCoord = positionToTileCoord(pos);

	//can't move because it can't go out the screen
	if (!ifInScene(pos))return false;

	//can't move because there are something 
	if (m_nomoveLayer->getTileGIDAt(tileCoord) > 0) return false;

	return true;
}

void MyMap::setOrder(Scene*scene)
{
	m_backgroundLayer->removeFromParent();
	scene->addChild(m_backgroundLayer, -1);
}

void MyMap::setNomove(Vec2 pos)
{
	auto tileCoord = positionToTileCoord(pos);
	m_nomoveLayer->setTileGID(m_gid_nomove, tileCoord);
}

void MyMap::removeNomove(Vec2 pos)
{
	auto tileCoord = positionToTileCoord(pos);
	if (m_nomoveLayer->getTileGIDAt(tileCoord) == 0) return;
	m_nomoveLayer->removeTileAt(tileCoord);
}

void MyMap::damage(Vec2 pos)
{
	auto tileCoord = positionToTileCoord(pos);
	assert(ifCanDamage(pos));
	if (!ifCanDamage(pos)) return;

	int propType = RandProp();
	if (propType != -1)
	{
		SendMsg_CreateProp(tileCoord.x, tileCoord.y, propType);
	}

	removeNomove(pos);
	m_removeLayer->removeTileAt(tileCoord);
	m_buildingLayer->removeTileAt(tileCoord);

	pos.y += getTileSize().height;
	if (!ifInScene(pos)) return;

	tileCoord=positionToTileCoord(pos);
	m_building_topLayer->removeTileAt(tileCoord);
}

Vec2 MyMap::standard(Vec2 pos)
{
	return tileCoordToPosition(positionToTileCoord(pos));
}

int MyMap::RandProp()
{
	const int item_breed = Prop::Type::MaxNum; //道具种类
	static const int item_breedMaxNumber[item_breed] = { 10,20,20,5,3 }; //对于每种道具所能存在的最大数目
	static int item_matrix[item_breed] = { 0,0,0,0,0 };	//已经产生了的道具数量

	static int breed = 0;
	breed=(breed + 71) % 101;
	static int bol5 = 0;
	bol5 = (bol5 + 1) % 5;
	if (bol5 == 0) return -1;
	static bool bol2 = true;
	static int last = -1;

	srand((unsigned)time(NULL));

	int n = (rand()+breed*23) % 100;
	int m = (n + breed) % item_breed;

	//不产生道具
	if (n <50) return -1;    
	if (!bol2)
	{
		bol2 = true;
		return -1;
	}

	int change = 0;  //已经产生完的道具类型数
	while (true)
	{
		if (change >= item_breed) break;

		if (item_matrix[m] >= item_breedMaxNumber[m])	++change;

		if (item_matrix[m] < item_breedMaxNumber[m])
		{
			if (last != m)
			{
				last = m;
				++item_matrix[m];
				bol2 = false;
				return m;
			}
		}
			
		m = (m + 1) % item_breed;
	}
	return -1;
}

bool MyMap::ifCanDamage(Vec2 pos)
{
	auto tileCoord = positionToTileCoord(pos);

	if (!ifInScene(pos)) return false;

	if (m_removeLayer->getTileGIDAt(tileCoord) == 0) return false;

	return true;
}

bool MyMap::ifInScene(Vec2 pos)
{
	auto Size = getMapSize();
	Size.width *= getTileSize().width;
	Size.height *= getTileSize().height;
	if (pos.x<0 || pos.y<0 || pos.x>Size.width || pos.y>Size.height)
		return false;
	return true;
}