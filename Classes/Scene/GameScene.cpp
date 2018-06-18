#include "Scene/GameScene.h"
#include"Global/Global.h"
#include"Global/Player.h"
#include"Controller/GameController.h"
#include"Controller/PropManager.h"
#include<assert.h>
USING_NS_CC;

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

bool GameScene::init()
{
	return true;
}

void GameScene::start(int mapID)
{
	addMap(mapID);
	addSprite();
	addManager();
	scheduleUpdate();
}

void GameScene::update(float det)
{
	for (auto it = Player::Players.begin(); it != Player::Players.end(); ++it)
	{
		auto player = it->second;
		player->runAction(m_map);
	}
}

void GameScene::addMap(int mapID)
{
	m_map=GameMap::create(mapID);
	this->addChild(m_map,1);
}

void GameScene::addSprite()
{
	for (auto it = Player::Players.begin(); it != Player::Players.end(); ++it)
	{
		auto player = it->second;
		auto sprite=player->createSprite();
		sprite->setPosition(Setting::bornPlace[player->getNumber()]);
		m_map->addChild(sprite,3);
	}
}

void GameScene::addManager()
{
	auto Controller = GameController::create();
	assert(Player::local_player != NULL);
	Controller->start(Player::local_player, m_map);
	this->addChild(Controller);

	auto propManager = PropManager::create();
	propManager->start(m_map,Controller);
	this->addChild(propManager);
}