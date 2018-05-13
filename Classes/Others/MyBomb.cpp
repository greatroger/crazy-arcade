#include "MySprite.h"
#include"every.h"
USING_NS_CC;

MyBomb::MyBomb(){}

MyBomb::MyBomb(MySprite* sprite,Scene* scene,MyMap* map)
	           :m_man(sprite),m_map(map),m_scene(scene)
{
	m_picFilename_bomb = m_man->m_picFilename_bomb;
	m_picFilename_water = m_man->m_picFilename_water;
}

MyBomb* MyBomb::create(MySprite* sprite, Scene* scene, MyMap* map)
{
	MyBomb* bomb = new MyBomb(sprite,scene,map);
	if (bomb && bomb->init())
	{
		bomb->autorelease();
		return bomb;
	}
	CC_SAFE_DELETE(bomb);
	return nullptr;
}

void MyBomb::plantBomb(cocos2d::Vec2 pos)
{      
	//炸弹动画播放
	setPosition(pos);
    runAction(RepeatForever::create(Animate::create(m_man->m_animation)));

	//将此炸弹加入炸弹队列
	++m_man->m_bombNum;
	g_list_bomb.push_back(this);
	auto tileCoord = m_map->tileCoordFromPosition(pos);
	m_map->m_nomoveLayer->setTileGID(m_map->m_gid_nomove,tileCoord);

	//3s后爆炸
	auto act1 = DelayTime::create(3.0f);   
	auto act2 = CallFunc::create([this]()
	{
		explode();
	});
	runAction(Sequence::create(act1, act2, nullptr));
}


void MyBomb::explode()
{
	Vec2 pos = getPosition();
	auto tileCoord = m_map->tileCoordFromPosition(pos);

	m_map->m_nomoveLayer->removeTileAt(tileCoord);
	--m_man->m_bombNum;

	//将自己从炸弹队列移除
	auto it = myFind(g_list_bomb,pos);
	if (it != g_list_bomb.end())  g_list_bomb.erase(it);

	//对玩家造成伤害
	if (g_sprite != nullptr && g_sprite->getPosition()==pos)
	{
		--g_sprite->m_life;
	}
	creatWater(pos);

	//一个炸弹的四个方向的爆炸
	MyRemove(0, 1);
	MyRemove(1, 0);
	MyRemove(0, -1);
	MyRemove(-1, 0);
	this->removeFromParent();
}

void MyBomb::MyRemove(int a,int b)
{
	int size = 40;
	int k = m_man->m_bombWidth;
	Vec2 pos = getPosition();

	while (--k >= 0)
	{
		pos.x += a * size;
		pos.y += b * size;

		//引发连环爆炸
		if (m_map->bnoMove(pos)){
			auto it = myFind(g_list_bomb,pos);
			if (it != g_list_bomb.end()) (*it)->explode();    
		}

		//破坏地图物体
		if (!m_map->remove(pos) && m_map->bnoMove(pos)) break;

		//对本地玩家造成伤害
		if (g_sprite != nullptr && g_sprite->getPosition() == pos)
		{
			--g_sprite->m_life;
		}
		creatWater(pos);
	}
}

void MyBomb::creatWater(Vec2 pos) //制作水花
{
	auto water = Sprite::create(m_picFilename_water);
	water->setPosition(Vec2(pos.x, pos.y));
	m_scene->addChild(water);
	auto act1 = DelayTime::create(0.5f);
	auto act2 = CallFunc::create([water]() {
		water->removeFromParent();
	});
	water->runAction(Sequence::create(act1, act2, nullptr));
}

