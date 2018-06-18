#include "PropManager.h"
#include"Object/Prop.h"

#include<iostream>
#include"Global/Global.h"
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
		auto player = it->second;

		if (player->msg_pickupProp != -1)
		{
			pickupProp(player->msg_pickupProp,player);
			player->msg_pickupProp = -1;
		}

		if (player->msg_useProp != -1)
		{
			useProp(player->msg_useProp, player);
			player->msg_useProp = -1;
		}
	}

	auto player = Player::local_player;
	if (player->msg_createprop_pos != Vec2(0, 0))
	{
		auto pos = m_map->tileCoordToPosition(player->msg_createprop_pos);
		auto prop = Prop::create(player->msg_createprop_type);
		prop->setPosition(pos);
		m_map->addChild(prop,1);
		player->msg_createprop_pos = Vec2(0, 0);
		player->msg_createprop_type = -1;
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
	}
}

void PropManager::useProp_bazooka(Player* player)
{
	auto baz =Bazooka::create();
	Vec2 dir = player->getDirection()*2000;
	auto moveBy = MoveBy::create(20,dir);
	baz->runAction(moveBy);
	baz->start();
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