#include "Pop.h"
#include<iostream>
#include"Global/Global.h"
USING_NS_CC;

Pop::Pop(Player* player):m_player(player)
{
	m_team = player->m_team;
	auto act1 = DelayTime::create(5.0f);
	auto act2 = CallFunc::create([this]()
	{
		puncturePop((m_team + 1) % 2);
	});
	runAction(Sequence::create(act1, act2, nullptr));
	scheduleUpdate();
}


Pop::~Pop()
{
}

Pop* Pop::create(Player* player)
{
	Pop* pop = new Pop(player);
	std::string path = Path::picPop[0];
	if (pop && pop->initWithFile(path))
	{
		pop->autorelease();
		return pop;
	}
	CC_SAFE_DELETE(pop);
	return nullptr;
}

void Pop::update(float det)
{
	Vec2 pos = m_player->getPosition();
	FOR_ALL_PLAYERS{
		auto player = it->second;
	    if (player == m_player) continue;
	    Vec2 playerpos = player->getPosition();
	    float distance = (abs(playerpos.x - pos.x) + abs(playerpos.y - pos.y)) / 2;
	    if (distance<5)
	    {
		   puncturePop(player->m_team);
		   break;
	    }
	}
}

void Pop::getInPop(Player* player)
{
	player->isinpop = true;
	auto pop = Pop::create(player);
	player->getSprite()->addChild(pop);
	pop->setPosition(Vec2(20, 20));
}

void Pop::puncturePop(int team)
{
	this->setTexture(Path::picPop[1]);
	auto act1 = DelayTime::create(0.1f);
	auto act2 = CallFunc::create([this]()
	{
		this->setTexture(Path::picPop[2]);
	});
	runAction(Sequence::create(act1, act2, nullptr));

	auto act3 = DelayTime::create(0.15f);
	auto act4 = CallFunc::create([this,team]()
	{
		if (team == m_team)
		{
			Music::PlayMusic(Music::music::poplive);
		}
		else
		{
			Music::PlayMusic(Music::music::popdie);
			m_player->msg_ishurt = true;
		}
		assert(m_player->isinpop = true);
		m_player->isinpop = false;
		this->removeFromParent();
	});
	runAction(Sequence::create(act3, act4, nullptr));
}

