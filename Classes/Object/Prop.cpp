#include "Prop.h"
#include"Global/Global.h"
#include"Object/Pop.h"
#include"Network/Msg.h"
USING_NS_CC;

std::list<Bun*> Bun::bunList;
Prop::Prop(int type):m_type(type)
{
	scheduleUpdate();
}


Prop::~Prop()
{
}

Prop* Prop::create(int type)
{
	Prop* prop = new Prop(type);
	std::string path = Path::picProp[type];
	if (prop && prop->initWithFile(path))
	{
		prop->autorelease();
		return prop;
	}
	CC_SAFE_DELETE(prop);
	return nullptr;
}

void Prop::update(float det)
{
	Vec2 pos = this->getPosition();
	FOR_ALL_PLAYERS
	{
		auto name = it->first;
		auto player = it->second;
	    Vec2 playerpos = player->getPosition();
		float distance = (abs(playerpos.x - pos.x) + abs(playerpos.y - pos.y)) / 2;
		if (distance<10)
		{
			SendMsg_PickupProp(name, m_type);
			this->removeFromParent();
		}
	}
}


Bun::Bun(int type) :m_type(type)
{
	scheduleUpdate();
}

Bun* Bun::create(int type)
{
	Bun* bun = new Bun(type);
	std::string path = Path::picBun[type];
	if (bun && bun->initWithFile(path))
	{
		bun->autorelease();
		return bun;
	}
	CC_SAFE_DELETE(bun);
	return nullptr;
}


void Bun::update(float det)
{
	//检测本地玩家是否拾取包子
	Vec2 bunpos = this->getPosition();
	auto player = Player::local_player;

	Vec2 playerpos = player->getPosition();
	float distance = (abs(playerpos.x - bunpos.x) + abs(playerpos.y - bunpos.y)) / 2;
	if (distance < 10 && player->getBunType() == -1)
	{
		SendMsg_PickupBun(false, m_type,bunpos);
		player->setBunType(-1);
	}

	//根据网络消息移除包子
	/*Vec2 msg_pos = player->Msg.PickupBun.pos;
	if (bunpos == msg_pos)
	{
		player->Msg.PickupBun.pos = Vec2(-1, -1);
		this->removeFromParent();
	}*/
}

void Bun::getBun(Player *player,int type)
{
	//assert(player->getBunType() == -1);
	player->addSpeed(m_speed);
	player->setBunType(type);
	auto bun = Sprite::create("Prop/bun.png");
	player->getSprite()->addChild(bun,1,1);
	bun->setPosition(20, 40);
}

void Bun::loseBun(Player * player)
{
//	if (player->getBunType() == -1) return;
	player->addSpeed(-m_speed);
	player->setBunType(-1);
	player->getSprite()->removeChildByTag(1);
}

