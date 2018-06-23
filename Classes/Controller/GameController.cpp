#include "Controller/GameController.h"
#include"Object/Prop.h"
#include"Network/Msg.h"
USING_NS_CC;

#define SETKEY(keycode) m_bkey.w = false;\
m_bkey.s = false;\
m_bkey.a = false;\
m_bkey.d = false;\
m_bkey.keycode = true;\

GameController::GameController()
{
}


GameController::~GameController()
{
}


void GameController::start(Player* player,MyMap* map)
{
	m_player = player;
	m_speed = m_player->getSpeed();
	m_map = map; 
	startWalkListener();
	startSpaceListener();
	startKeyEListener();
	scheduleUpdate();
}

void GameController::startWalkListener()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](EventKeyboard::KeyCode keycode, Event * event) {
		EventKeyboard::KeyCode W = EventKeyboard::KeyCode::KEY_W;
		EventKeyboard::KeyCode S = EventKeyboard::KeyCode::KEY_S;
		EventKeyboard::KeyCode D = EventKeyboard::KeyCode::KEY_D;
		EventKeyboard::KeyCode A = EventKeyboard::KeyCode::KEY_A;
		if (keycode == W) { SETKEY(w) }
		if (keycode == S) { SETKEY(s) }
		if (keycode == D) { SETKEY(d) }
		if (keycode == A) { SETKEY(a) }
	};

	listener->onKeyReleased = [this](EventKeyboard::KeyCode keycode, Event * event) {
		EventKeyboard::KeyCode W = EventKeyboard::KeyCode::KEY_W;
		EventKeyboard::KeyCode S = EventKeyboard::KeyCode::KEY_S;
		EventKeyboard::KeyCode D = EventKeyboard::KeyCode::KEY_D;
		EventKeyboard::KeyCode A = EventKeyboard::KeyCode::KEY_A;
		if (keycode == W) { m_bkey.w = false; }
		if (keycode == S) { m_bkey.s = false; }
		if (keycode == D) { m_bkey.d = false; }
		if (keycode == A) { m_bkey.a = false; }
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	schedule(schedule_selector(GameController::walkUpdate),m_player->getSpeed()+0.01);
}

void GameController::update(float det)
{
	if (m_speed != m_player->getSpeed())
	{
		m_speed = m_player->getSpeed();
		unschedule(schedule_selector(GameController::walkUpdate));
		schedule(schedule_selector(GameController::walkUpdate), m_speed+0.01);
	}
}

void GameController::walkUpdate(float tmd)
{ 
	int step = m_map->getTileSize().width;
	auto  pos = m_player->getPosition();

	if (m_player->isgold) return;
	if (m_player->isdead) return;
	if (m_bkey.w)
	{
		m_player->setDirection(Player::direction::up);
		if (ifCanMove(Vec2(0, step))) 
		{
			Vec2 walk = m_player->getDirection()*step;
			auto moveBy = MoveBy::create(m_speed, walk);
			m_player->getSprite()->runAction(moveBy);
			SendMsg_Walk(m_player->m_dir, step, pos.x, pos.y);
		}
		else
		SendMsg_Walk(m_player->m_dir, 0, pos.x, pos.y);
		return;
	}
	if (m_bkey.s)
	{
		m_player->setDirection(Player::direction::down);
		if (ifCanMove(Vec2(0, -step))) 
		{
			Vec2 walk = m_player->getDirection()*step;
			auto moveBy = MoveBy::create(m_speed, walk);
			m_player->getSprite()->runAction(moveBy);
			SendMsg_Walk(m_player->m_dir, step, pos.x, pos.y);
		}
		else
		SendMsg_Walk(m_player->m_dir, 0, pos.x, pos.y);
		return;
	}

	if (m_bkey.a)
	{
		m_player->setDirection(Player::direction::left);
		if (ifCanMove(Vec2(-step, 0)))
		{
			Vec2 walk = m_player->getDirection()*step;
			auto moveBy = MoveBy::create(m_speed, walk);
			m_player->getSprite()->runAction(moveBy);
			SendMsg_Walk(m_player->m_dir, step, pos.x, pos.y);
		}
		else
		SendMsg_Walk(m_player->m_dir, 0, pos.x, pos.y);
		return;
	}

	if (m_bkey.d)
	{
		m_player->setDirection(Player::direction::right);
		if (ifCanMove(Vec2(step, 0)))
		{
			Vec2 walk = m_player->getDirection()*step;
			auto moveBy = MoveBy::create(m_speed, walk);
			m_player->getSprite()->runAction(moveBy);
			SendMsg_Walk(m_player->m_dir, step, pos.x, pos.y);
		}
		else
		SendMsg_Walk(m_player->m_dir, 0, pos.x, pos.y);
		return;
	}
}

bool GameController::ifCanMove(Vec2& direction)
{
	Vec2 pos = m_player->getPosition() + direction;
	if (!m_map->ifCanMove(pos)) return false;
	if (!m_player->ifcanMove()) return false;
	return true;
}

void GameController::startSpaceListener()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](EventKeyboard::KeyCode keycode, Event * event) {
		if (keycode == EventKeyboard::KeyCode::KEY_SPACE)
		{
			if (m_player->isdead) return;
			if (m_player->isinpop) return;
			if (m_player->getPropType() != -1)
			{
				SendMsg_UseProp(m_player->getName(), m_player->getPropType());
			}
			else
			{
				Vec2 pos = m_player->getPosition();
				pos = m_map->tileCoordToPosition(m_map->positionToTileCoord(pos));
				if (!ifcanBomb(pos)) return;
				SendMsg_Bomb(pos.x, pos.y);
			}
			Sleep(50);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameController::startKeyEListener()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](EventKeyboard::KeyCode keycode, Event * event) {
		if (keycode == EventKeyboard::KeyCode::KEY_E)
		{
			if(m_player->getStopwatch()<=0)  return;
			if (m_player->isgold)return;
			if (m_player->isinpop)return;
			if (m_player->isdead)return;
			SendMsg_UseProp(m_player->getName(),Prop::Type::stopwatch);
			Sleep(50);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool GameController::ifcanBomb(Vec2 pos)
{
	if (!m_player->ifcanBomb()) return false;
	if (!m_map->ifCanMove(pos)) return false;
	return true;
}

/*void GameController::MapAnalyse()
{
	for (int i = 0; i <= m_map->getMapSize().width; ++i)
	{
		for (int j = 0; j <= m_map->getMapSize().height; ++i)
		{
			using cocos2d::Vec2;
			Vec2 pos = m_map->tileCoordToPosition(Vec2(i, j));
			if (m_map->ifCanDamage(pos))
			{
				SendMsg_Map(i, j,"Damage");
				continue;
			}
			if (m_map->ifCanMove(pos))
			{
				SendMsg_Map(i, j, "Move");
				continue;
			}
		}
	}
	SendMsg_Map(-1, -1,"");
}*/