#include "BunHouse.h"
#include"Network/Msg.h"
#include"Object/Prop.h"
#include"Scene/RoomScene.h"
#include"Object/Map/GameMap.h"
USING_NS_CC;

bool BunHouse::init()
{
	m_bunpos[0] = Vec2(300, 380);
	m_bunpos[1] = Vec2(660, 380);
	m_maxBunNum = 3;
	m_bunNum[0] = 0;
	m_bunNum[1] = 0;
	return true;
}

void BunHouse::start()
{
	//设置玩家出生位置以及队伍
	FOR_ALL_PLAYERS
	{
		auto player = it->second;
	    player->m_team = (player->getRoomID()) % 2;
	    player->getSprite()->setPosition(bornPlace[player->m_team]);
	}
	scheduleUpdate();
}


void BunHouse::update(float det)
{
	checkDead();
	checkEat();
	checkLoseBun();
	checkPickupBun();
}


void BunHouse::checkPickupBun()
{
	//每帧根据网络消息检查玩家是否拾取包子
	FOR_ALL_PLAYERS{
		auto player = it->second;
		bool isFromHouse = player->Msg.PickupBun.isFromHouse;
		int bunType = player->Msg.PickupBun.bunType;
		Vec2 pos = player->Msg.PickupBun.pos;

		if (bunType == -1) continue;
		player->Msg.PickupBun.bunType=-1;

		int team = player->m_team;
		int oppteam = (team + 1) % 2;
		//从敌方包子铺夺取包子
		if (isFromHouse)
		{
			assert(pos == m_bunpos[oppteam]);
			assert(bunType == oppteam);
			++m_bunNum[oppteam];
			m_bunNum[oppteam] += m_maxBunNum;
			auto act1 = DelayTime::create(5.0f);
			auto act2 = CallFunc::create([this, oppteam]()
			{
				m_bunNum[oppteam] -= m_maxBunNum;
			});
			runAction(Sequence::create(act1, act2, nullptr));
		}
		else // 从地上拾取包子
		{
			for (auto it = Bun::bunList.begin(); it != Bun::bunList.end(); ++it)
			{
				auto bunpos = (*it)->getPosition();
				if (bunpos == pos)
				{
					(*it)->removeFromParent();
					Bun::bunList.erase(it);
					player->Msg.PickupBun.pos = Vec2(-1, -1);
					break;
				}
			}
		}
		Bun::getBun(player, bunType);	
	}
}

//每帧根据网络消息检查玩家是否掉落包子
void BunHouse::checkLoseBun()
{
	FOR_ALL_PLAYERS{
		auto player = it->second;
	bool isFromHouse = player->Msg.LoseBun.isFromHouse;
	Vec2 pos = player->Msg.LoseBun.pos;
	int bunType = player->Msg.LoseBun.bunType;

	if (bunType == -1) continue;
	player->Msg.LoseBun.bunType = -1;
	
	int team = player->m_team;
	int oppteam = (team + 1) % 2;
	if (isFromHouse) //把包子放回自家包子铺
	{
		assert(pos == m_bunpos[team]);

		//包子是友方的
		if (bunType == team)
		{
			--m_bunNum[team];
		}
	}  
	else // 由于死亡而导致包子掉落
	{
		auto bun = Bun::create(bunType);
		bun->setPosition(pos);
		addChild(bun, 20);
		Bun::bunList.push_back(bun);
	}
	Bun::loseBun(player);
	}
}


//每帧判断本地玩家是否进入包子铺
void BunHouse::checkEat()
{
	auto player = Player::local_player;
	int bunType = player->getBunType();
	int team = player->m_team;
	int oppteam = (team + 1) % 2;
	auto pos = player->getPosition();

	//来到敌方包子铺
	if (ifInHouse(pos,oppteam) && bunType == -1 && m_bunNum[oppteam]<m_maxBunNum)
	{
		SendMsg_PickupBun(true,oppteam,m_bunpos[oppteam]);
		player->setBunType(oppteam);
	}

	//回到自己的包子铺
	if (ifInHouse(pos,team))
	{
		if (bunType == -1) return;
		if (bunType == team)
		{
			SendMsg_LoseBun(true,team,m_bunpos[team]);
			player->setBunType(-1);
		}

		if (bunType == oppteam)
		{
			SendMsg_LoseBun(true,oppteam,m_bunpos[team]);
			player->setBunType(-1);
			SendMsg_GetBunScore(team);
		}
	}

}


void BunHouse::checkDead()
{
	FOR_ALL_PLAYERS
	{
		auto name = it->first;
		auto player = it->second;
	    auto bunType = player->getBunType();
	    auto sprite = player->getSprite();
	    if (player->msg_ishurt) {

			player->msg_ishurt = false;
			player->isdead = true;

			//包子掉落
			if (bunType != -1 && player==Player::local_player)	{
				SendMsg_LoseBun(false,bunType,player->getPosition());
				player->setBunType(-1);
			}
			//玩家的死亡与复活
		    sprite->setVisible(false);
		    sprite->setPosition(Vec2(0, 0));

			if (name == Player::local_Username)
			{
				auto deadlayer = Sprite::create("Map/black.png");
				addChild(deadlayer, 100);
				GameMap::DeadAudioPlay(deadlayer);
			}
		
		    auto act1 = DelayTime::create(4.0f);
			auto act2 = CallFunc::create([this,player]()
		    {
				  reborn(player);
			});
			runAction(Sequence::create(act1, act2, nullptr));
		    }
	}
}

//玩家复活
void BunHouse::reborn(Player* player)
{
	if (player == nullptr) return;
	player->spriteInit();
	player->isdead = false;
	auto sprite = player->getSprite();
	sprite->setPosition(bornPlace[player->getRoomID()]);
	sprite->setVisible(true);
}

//判断是否在包子铺里
bool BunHouse::ifInHouse(Vec2 pos,int team)
{
	const int size = getTileSize().width;
	if (pos == m_bunpos[team])return true;
	if (pos.x == m_bunpos[team].x + size && pos.y == m_bunpos[team].y) return true;
	if (pos.x == m_bunpos[team].x - size && pos.y == m_bunpos[team].y) return true;
	if (pos.x == m_bunpos[team].x  && pos.y == m_bunpos[team].y + size) return true;
	if (pos.x == m_bunpos[team].x  && pos.y == m_bunpos[team].y - size) return true;
	return false;
}