#include "Normal.h"
#include"Network/Msg.h"
#include"Scene/RoomScene.h"
#include"GameMap.h"
USING_NS_CC;


Normal::Normal()
{

}


Normal::~Normal()
{
}

bool Normal::init()
{
	return true;
}

void Normal::start()
{
	FOR_ALL_PLAYERS
	{
		auto player = it->second;
	    player->m_team = player->getRoomID();
		player->getSprite()->setPosition(bornPlace[player->getRoomID()]);
	}
	scheduleUpdate();
}

void Normal::update(float det)
{
	checkDead();
}


void Normal::checkDead()
{
	FOR_ALL_PLAYERS{
		auto name = it->first;
		auto player = it->second;
	    auto sprite = player->getSprite();
	    if (sprite == nullptr) return;
	    if (player->msg_ishurt) {

		player->msg_ishurt = false;
		player->addLife(-1);
		player->isdead = true;
		sprite->setVisible(false);
		sprite->setPosition(Vec2(0, 0));


		if (player->getLife() > 0)
		{
			if (name == Player::local_Username)
			{
				auto deadlayer = Sprite::create("Map/black.png");
				addChild(deadlayer, 100);
				GameMap::DeadAudioPlay(deadlayer);
			}

			auto act1 = DelayTime::create(4.0f);
			auto act2 = CallFunc::create([player,this]()
			{
				reborn(player);
			});
			runAction(Sequence::create(act1, act2, nullptr));
		}
		else
		{
			if (name == Player::local_player->getName())
				SendMsg_Dead();
		}
	}
	}
}



 void Normal::reborn(Player* player)
 {
	 if (player == nullptr) return;
	 player->spriteInit();
	 player->isdead = true;
	 auto sprite=player->getSprite();
	 sprite->setPosition(bornPlace[player->getRoomID()]);

	 auto act1 = DelayTime::create(0.2f);
	 auto act2 = CallFunc::create([sprite,player]()
	 {
		 player->isdead = false;
		 sprite->setVisible(true);
	 });
	 runAction(Sequence::create(act1, act2, nullptr));
 }
