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
	return true;
}

void BunHouse::start()
{
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
	checkOver();
	checkDead();
	checkEat();
	checkBun();
}

void BunHouse::checkOver()
{
	if (Msg::Game.isgameOver)
	{
		Msg::Game.isgameOver = false;
		Sleep(500);
		auto roomScene = RoomScene::create();
		Director::getInstance()->replaceScene(TransitionFade::create(1, roomScene));
	}
}

void BunHouse::checkBun()
{
	FOR_ALL_PLAYERS{
		auto player = it->second;
	    int type = player->msg_pickupBun;
		int bunType = player->msg_bunType;

	    if (type == -1) continue;
		if (bunType == -1) continue;
	    player->msg_pickupBun = -1;
		player->msg_bunType = -1;


		switch (type)
		{
		default:
			break;
		case -1:
			break;
		case 0:
			Bun::getBun(player, bunType);
			break;
		case 1:
			Bun::loseBun(player);
			break;
		}

	}
}

void BunHouse::checkEat()
{
	static int bunNum[2] = { 0,0 };
	auto player = Player::local_player;
	int bunType = player->getBunType();
	int team = player->m_team;
	int oppteam = (team + 1) % 2;
	auto pos = player->getPosition();

	//来到敌方包子铺
	if (ifInHouse(pos,oppteam) && bunType == -1 && bunNum[oppteam]<m_maxBunNum)
	{
		SendMsg_PickupBun(Player::local_Username, 0, oppteam);
		++bunNum[oppteam];
		bunNum[oppteam] += m_maxBunNum;
		auto act1 = DelayTime::create(5.0f);
		auto act2 = CallFunc::create([this,oppteam]()
		{
			bunNum[oppteam] -= m_maxBunNum;
		});
		runAction(Sequence::create(act1, act2, nullptr));
	}

	//回到自己的包子铺
	if (ifInHouse(pos,team))
	{
		if (bunType == -1) return;
		if (bunType == team)
		{
			--bunNum[team];
			SendMsg_PickupBun(Player::local_Username, 1, team);
		}

		if (bunType == oppteam)
		{
			SendMsg_PickupBun(Player::local_Username, 1, oppteam);
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
			if (bunType != -1)
			{
				auto bun = Bun::create(bunType);
				bun->setPosition(player->getPosition());
				addChild(bun, 20);
				Bun::loseBun(player);
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

void BunHouse::reborn(Player* player)
{
	if (player == nullptr) return;
	player->spriteInit();
	player->isdead = false;
	auto sprite = player->getSprite();
	sprite->setPosition(bornPlace[player->getRoomID()]);
	sprite->setVisible(true);
}

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