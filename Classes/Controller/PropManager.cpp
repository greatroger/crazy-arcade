#include "PropManager.h"
#include"Object/Prop.h"
#include<iostream>
#include"Global/Global.h"
#include"Object/Bazooka.h"
#include"Network/Msg.h"
USING_NS_CC;

#define PT Prop::Type  

PropManager::PropManager()
{
}


PropManager::~PropManager()
{
}

void PropManager::start(MyMap* map,GameController* controller)
{
	m_map = map;
	m_gamecontroller = controller;
	scheduleUpdate();
}

void PropManager::update(float det)
{
	for (auto it = Player::Players.begin(); it != Player::Players.end(); ++it)
	{
		auto name = it->first;
		auto player = it->second;

		if (player->msg_pickupProp != -1)
		{
			if (name == Player::local_Username)
				Music::PlayMusic(Music::eatProp);

			pickupProp(player->msg_pickupProp,player);
			player->msg_pickupProp = -1;
		}

		if (player->msg_useProp != -1)
		{
			useProp(player->msg_useProp, player);
			player->msg_useProp = -1;
		}
	}

	for(auto it=Msg::Game.createProp.begin(); it!= Msg::Game.createProp.end();++it)
	{
		Msg::Game.v_mutex.lock();
		auto pos = m_map->tileCoordToPosition(it->pos);
		auto prop = Prop::create(it->type);
		prop->setPosition(pos);
		m_map->addChild(prop,1);
		Msg::Game.createProp.erase(it);
		Msg::Game.v_mutex.unlock();
		break;
	}
}


void PropManager::pickupProp(int type,Player* player)
{
	switch (type)
	{
	default:
		break;
	case PT::shoes:case PT::powerliquid:case PT::bombliquid:
		useProp(type, player);
		break;
	case PT::bazooka:
		player->pickupProp(PT::bazooka,2);
		break;
	case PT::stopwatch:
		player->addStopwatch(1);
		break;
	}
}

void PropManager::useProp(int type, Player* player)
{
	switch (type)
	{
	default:
		break;
	case PT::shoes:
		if (player->getName() != Player::local_Username) break;
		player->addSpeed(-0.01f);
		break;
	case PT::powerliquid:
		player->addBombWidth(1);
		break;
	case PT::bombliquid:
		player->addMaxBombNmu(1);
		break;
	case PT::bazooka:
		useProp_bazooka(player);
		break;
	case PT::stopwatch:
		useProp_stopwatch(player);
		break;
	}
}

void PropManager::useProp_bazooka(Player* player)
{
	Vec2 dir = player->getDirection();
	auto moveBy = MoveBy::create(3,dir*2000);
	auto baz = Bazooka::create();
	m_map->addChild(baz, 15);
	baz->start(m_map);
	baz->setPosition(player->getPosition()+dir*m_map->getTileSize().width);
	baz->runAction(moveBy);
	player->useProp();
}

void PropManager::useProp_stopwatch(Player* player)
{
	//ÇÐ»»Í¼Æ¬
	player->isgold=true;
	player->addStopwatch(-1);
	auto sprite = player->getSprite();
	sprite->setTexture(Path::Player::picGold);

	auto act1 = DelayTime::create(2.0f);
	auto act2 = CallFunc::create([player,sprite]()
	{
		auto texture = Path::Player::getPicSprite(player->getNumber(), Player::down);
		sprite->setTexture(texture);
		player->isgold = false;
	});
	sprite->runAction(Sequence::create(act1, act2, nullptr));
}