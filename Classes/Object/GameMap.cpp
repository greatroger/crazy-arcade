#include "GameMap.h"
#include"Network/Msg.h"
#include"Object/Prop.h"
#include"Controller/PropManager.h"
USING_NS_CC;

MyMap* GameMap::create(int mapID)
{
	switch (mapID)
	{
	default:
		break;
	case Village:
		return Village::create(Path::picMap[Village]);
	case Tomb:
		return Tomb::create(Path::picMap[Tomb]);
	case BunHouse:
		return BunHouse::create(Path::picMap[BunHouse]);
	}
	return nullptr;
}


void GameMap::BunHouse::bunCreate()
{
	static int bunNum = 0;
	if (bunNum >= m_maxBunNum){
		return;
	}
	++bunNum;
}

void GameMap::BunHouse::update(float det)
{

	FOR_ALL_PLAYERS
	{
		auto player = it->second;
	    int bunType = player->getBunType();
	    int team = player->m_team;
	    int oppteam = (team + 1) % 2;

    	if (player->getLife() == 0)
    	{ 
			//包子掉落
			if (bunType != 0)
			{
				auto bun = Bun::create(bunType);
				bun->setPosition(player->getPostion());
				Bun::loseBun(player);
			}

			//玩家死亡与复活
			player->getSprite()->setVisible(false);
			auto act1 = DelayTime::create(3.0f);
			auto act2 = CallFunc::create([player]()
			{
				player->getSprite()->setPosition(Setting::bornPlace[1]);
				player->getSprite()->setVisible(true);
				player->addLife(1);
			});
			runAction(Sequence::create(act1, act2, nullptr));
		}
	}
	CheakEat();
}

void GameMap::BunHouse::CheakEat()
{
	static int bunNum[2] = { 0,0 };

	FOR_ALL_PLAYERS	{
	auto player = it->second;
    int bunType = player->getBunType();
    int team = player->m_team;
    int oppteam = (team + 1) % 2;
	auto pos = player->getPostion();

	if (pos == m_bunpos[oppteam] && bunType == 0 && bunNum[oppteam]<m_maxBunNum)
	{
		Bun::getBun(player, oppteam);
		++bunNum[oppteam];
		bunNum[oppteam] += m_maxBunNum;
		auto act1 = DelayTime::create(5.0f);
		auto act2 = CallFunc::create([this,oppteam]()
		{
			bunNum[oppteam] -= m_maxBunNum;
		});
		runAction(Sequence::create(act1, act2, nullptr));
	}

	if (pos == m_bunpos[team])
	{
		if (bunType == 0) return;
		if (bunType == team)
		{
			--bunNum[team];
			Bun::loseBun(player);
		}

		if (bunType == oppteam)
		{
			SendMsg_GetBunScore();
			Bun::loseBun(player);
		}
	}

	}

}
void GameMap::BunHouse::loseBun(Player * player)
{
	if (player->getBunType() == 0) return;
	player->addSpeed(-0.5f);
	player->setBunType(0);
}


