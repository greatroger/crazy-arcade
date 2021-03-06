#include "Scene/GameScene.h"
#include"Global/Global.h"
#include"Global/Player.h"
#include"Controller/GameController.h"
#include"Controller/PropManager.h"
#include"Network/Msg.h"
#include"Scene/RoomScene.h"
#include"Object/Pop.h"
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
	m_map->start();
	scheduleUpdate();
}

void GameScene::update(float det)
{
	checkOver();
	checkPop();
	FOR_ALL_PLAYERS
	{
		auto player = it->second;
		player->runAction(m_map);
	}
}

void GameScene::walkUpdate(float tmd)
{
	auto player = Player::local_player;
	auto pos = player->getPosition();
	SendMsg_Walk(-1, 0, pos.x, pos.y);
}

void GameScene::addMap(int mapID)
{
	m_map=GameMap::create(mapID);
	assert(m_map != nullptr);
	this->addChild(m_map,1);
}

void GameScene::addSprite()
{
	for (auto it = Player::Players.begin(); it != Player::Players.end(); ++it)
	{
		auto player = it->second;
		auto sprite=player->createSprite();
		player->init();
		assert(sprite != nullptr);
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
	propManager->start(m_map);
	this->addChild(propManager);
}

void GameScene::checkOver()
{
	if (Msg::Game.isgameOver)
	{
		Msg::Game.isgameOver = false;
		Music::stopMusic();
		Music::PlayMusic(Music::music::win);
		Sleep(500);
		auto roomScene = RoomScene::create();
		Director::getInstance()->replaceScene(TransitionFade::create(1, roomScene));
	}
}

void GameScene::checkPop()
{
	FOR_ALL_PLAYERS{
		auto name = it->first;
	    auto player = it->second;
	    auto sprite = player->getSprite();
	    if (player->Msg.isinpop)
		{
		   player->Msg.isinpop = false;
	 	   Pop::getInPop(player);
	    }
	}
}