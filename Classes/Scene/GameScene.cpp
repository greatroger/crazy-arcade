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
	//������ͼ
	m_map = MyMap::create("map/green/green.tmx");
	m_map->init();
	addChild(m_map,0)
		;
	//������Ҿ���
	for (auto it = Players.begin(); it != Players.end(); ++it)
	{
		auto player = it->second;
		auto sprite=player->creatSprite();
		g_vector_sprite.push_back(sprite);
		m_map->addChild(sprite, 0);
	}

	//��������Ҿ�����ϼ�����
	g_sprite = Players[g_name]->m_sprite;
	g_sprite->plantBomb();
	g_sprite->walk();

	//����֡���º���
	scheduleUpdate();
	return true;
}

void GameScene::update(float delta)
{
	//���½������
	if (g_bstart == false)
	{
		//��Ǯ�Ż�~~
		Sleep(300);
		auto myScene = WaitScene::create();
		Director::getInstance()->replaceScene(myScene);
	}

	//���ؽ�ɫ������Ϣ
	if (g_sprite->m_life<=0)
	{
		SendMsg_Dead();
	}

	//ˢ������
	for (auto it = Players.begin(); it != Players.end(); ++it)
	{
		auto player = it->second;
		if (player->m_bdead && player->m_sprite != nullptr)
		{
			player->m_sprite->Mydelete();
		}
	}

	//ˢ���ƶ�
	for (auto it = Players.begin(); it != Players.end(); ++it)
	{
		auto player = it->second;
		if (player->m_bdead) continue;
		if (player->msg_walk_pos != Vec2(0, 0))
		{
			auto sprite = player->m_sprite;
			//�жϿɷ��ƶ�
			cocos2d::Vec2 pos=sprite->getPosition();
			pos = pos + player->msg_walk_pos;
			if (m_map->bnoMove(pos)) continue;
			//�����ƶ�
			auto moveBy = cocos2d::MoveBy::create(sprite->m_speed, player->msg_walk_pos);
			sprite->runAction(moveBy);
			//������Ϣ
			player->msg_walk_pos = Vec2(0, 0);
		}
	}

	//ˢ��ը��
	for (auto it = Players.begin(); it != Players.end(); ++it)
	{
		auto player = it->second;
		if (player->m_bdead) continue;
		if (player->msg_bomb_pos != Vec2(0, 0))
		{
			auto sprite = player->m_sprite;
			//����ը��λ�ã���֤����Ƭ����  
			cocos2d::Vec2 pos = player->msg_bomb_pos;
			auto tileCoord = m_map->tileCoordFromPosition(pos);
			pos=m_map->positionFromTileCoord(tileCoord);

			//�жϿɷ����ը��
			if (m_map->bnoMove(pos)) continue;

			//����ը��
			auto bomb = MyBomb::create(player->m_sprite,this,m_map);
			addChild(bomb);
			bomb->plantBomb(pos);

			player->msg_bomb_pos = Vec2(0, 0);
		}
	}
}


