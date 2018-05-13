#include "GameScene.h"
#include"every.h"
#include"WaitScene.h"
#include"Msg.h"
USING_NS_CC;


GameScene::GameScene()
{

}

bool GameScene::init()
{
	//创建地图
	m_map = MyMap::create("map/green/green.tmx");
	m_map->init();
	addChild(m_map,0)
		;
	//加载玩家精灵
	for (auto it = Players.begin(); it != Players.end(); ++it)
	{
		auto player = it->second;
		auto sprite=player->creatSprite();
		g_vector_sprite.push_back(sprite);
		m_map->addChild(sprite, 0);
	}

	//给本地玩家精灵加上监听器
	g_sprite = Players[g_name]->m_sprite;
	g_sprite->plantBomb();
	g_sprite->walk();

	//开启帧更新函数
	scheduleUpdate();
	return true;
}

void GameScene::update(float delta)
{
	//重新进入大厅
	if (g_bstart == false)
	{
		//加钱优化~~
		Sleep(300);
		auto myScene = WaitScene::create();
		Director::getInstance()->replaceScene(myScene);
	}

	//本地角色死亡消息
	if (g_sprite->m_life<=0)
	{
		SendMsg_Dead();
	}

	//刷新死亡
	for (auto it = Players.begin(); it != Players.end(); ++it)
	{
		auto player = it->second;
		if (player->m_bdead && player->m_sprite != nullptr)
		{
			player->m_sprite->Mydelete();
		}
	}

	//刷新移动
	for (auto it = Players.begin(); it != Players.end(); ++it)
	{
		auto player = it->second;
		if (player->m_bdead) continue;
		if (player->msg_walk_pos != Vec2(0, 0))
		{
			auto sprite = player->m_sprite;
			//判断可否移动
			cocos2d::Vec2 pos=sprite->getPosition();
			pos = pos + player->msg_walk_pos;
			if (m_map->bnoMove(pos)) continue;
			//精灵移动
			auto moveBy = cocos2d::MoveBy::create(sprite->m_speed, player->msg_walk_pos);
			sprite->runAction(moveBy);
			//重置信息
			player->msg_walk_pos = Vec2(0, 0);
		}
	}

	//刷新炸弹
	for (auto it = Players.begin(); it != Players.end(); ++it)
	{
		auto player = it->second;
		if (player->m_bdead) continue;
		if (player->msg_bomb_pos != Vec2(0, 0))
		{
			auto sprite = player->m_sprite;
			//矫正炸弹位置，保证在瓦片中心  
			cocos2d::Vec2 pos = player->msg_bomb_pos;
			auto tileCoord = m_map->tileCoordFromPosition(pos);
			pos=m_map->positionFromTileCoord(tileCoord);

			//判断可否放置炸弹
			if (m_map->bnoMove(pos)) continue;

			//放置炸弹
			auto bomb = MyBomb::create(player->m_sprite,this,m_map);
			addChild(bomb);
			bomb->plantBomb(pos);

			player->msg_bomb_pos = Vec2(0, 0);
		}
	}
}


