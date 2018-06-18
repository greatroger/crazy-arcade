#include "Pop.h"
#include"Global/Global.h"
USING_NS_CC;

Pop::Pop(int type, Player* player):m_team(type),m_player(player)
{
	scheduleUpdate();
	auto act1 = DelayTime::create(5.0f);
	auto act2 = CallFunc::create([this]()
	{
		puncturePop((m_team + 1) % 2);
	});
	runAction(Sequence::create(act1, act2, nullptr));
}


Pop::~Pop()
{
}

Pop* Pop::create(int type, Player* player)
{
	Pop* pop = new Pop(type, player);
	std::string path = Path::picPop;
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
	Vec2 pos = this->getPosition();
	FOR_ALL_PLAYERS{
		auto player = it->second;
	    if (player == m_player) continue;
	    Vec2 playerpos = player->getPostion();
	    float distance = (abs(playerpos.x - pos.x) + abs(playerpos.y - pos.y)) / 2;
	    if (distance<10)
	    {
		   puncturePop(player->m_team);
		   break;
	    }
	}
}

void Pop::puncturePop(int team)
{
	if (team == m_team)
	{
	}
	else
	{
		m_player->addLife(-1);
	}
	assert(m_player->isinpop = true);
	m_player->isinpop = false;
	audioPlay();
	this->removeFromParent();
}

void Pop::audioPlay()
{
}
