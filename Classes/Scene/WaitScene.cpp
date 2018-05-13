#include "WaitScene.h"
#include "cocos2d.h"
#include"GameScene.h"
#include"every.h"
#include"Msg.h"
USING_NS_CC;


WaitScene::WaitScene()
{

}

bool WaitScene::init()
{
	//创建地图
	m_map=MyMap::create("map/WaitHouse/WaitHouse.tmx");
	m_map->init();
	addChild(m_map,0);
	
	//创建精灵
	for (auto it = Players.begin(); it != Players.end(); ++it)
	{
		auto player = it->second;
		auto sprite = player->creatSprite();
		sprite->setPosition(cocos2d::Vec2(60, 180));
		m_map->addChild(sprite, 0);
	}

	//给本地玩家精灵加上监听器
	g_sprite = Players[g_name]->m_sprite;
	g_sprite->plantBomb();
	g_sprite->walk();

	//开启帧更新函数
	scheduleUpdate();

	//为房主创建开始按钮
	if (Players[g_name]->m_number == 1)
	{
		auto itemNor = Sprite::create("button/start.png");			
		auto closeItem = MenuItemSprite::create(itemNor, nullptr, nullptr, [this](Ref* sender)
		{
			SendMsg_Start();
		});
		closeItem->setPosition(Vec2(400, -100));
		closeItem->setScale(0.5f);
		auto menu = Menu::create(closeItem, NULL);
		menu->setPosition(Vec2::ZERO);
		menu->setScale(0.5f);
		this->addChild(menu, 2);
	}
	return true;
}

void WaitScene::update(float delta)
{
	//刷新精灵外表以及大厅登陆情况
	for (auto it = Players.begin(); it != Players.end(); ++it) 
	{
		auto player = it->second;
		if (player->m_bchange)
		{
			//销毁原来精灵
			if (player->m_sprite != nullptr){
				player->m_sprite->Mydelete();
			}
			//创建精灵
			auto sprite=player->creatSprite();
			sprite->setPosition(cocos2d::Vec2(60, 180));
			m_map->addChild(sprite,0);
			if (player->m_name == g_name)
			{
				sprite->plantBomb();
				sprite->walk();
			}
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
			cocos2d::Vec2 pos = sprite->getPosition();
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

			//判断可否放置炸弹
			cocos2d::Vec2 pos = sprite->getPosition();
			pos = pos + player->msg_walk_pos;
			if (m_map->bnoMove(pos)) continue;
			//放置炸弹
			auto bomb = MyBomb::create(player->m_sprite,this,m_map);
			addChild(bomb);
			bomb->plantBomb(player->msg_bomb_pos);

			player->msg_bomb_pos = Vec2(0, 0);
		}
	}
	//开始游戏
	if (g_bstart)
	{
		auto scene = GameScene::create();
		Director::getInstance()->replaceScene(scene);
	}
}

