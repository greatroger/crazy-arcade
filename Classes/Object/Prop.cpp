#include "Prop.h"
#include"Global/Global.h"
#include"Network/Msg.h"
#include"Controller/PropManager.h"
USING_NS_CC;

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
		auto player = it->second;
	    Vec2 playerpos = player->getPostion();
		float distance = (abs(playerpos.x - pos.x) + abs(playerpos.y - pos.y)) / 2;
		if (distance<10)
		{
			player->msg_pickupProp = m_type;
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
	Vec2 pos = this->getPosition();
	FOR_ALL_PLAYERS
	{
		auto player = it->second;
	    if (player->getBunType() != 0)return;

		Vec2 playerpos = player->getPostion();
		float distance = (abs(playerpos.x - pos.x) + abs(playerpos.y - pos.y)) / 2;
	    if (distance<10)
	    {
		   getBun(player,m_type);
		   this->removeFromParent();
		   break;
	    }
	}
}

void Bun::getBun(Player *player,int type)
{
	assert(player->getBunType() == 0);
	player->addSpeed(0.5f);
	player->setBunType(type);
	auto bun = Sprite::create("Prop/bun.png");
	player->getSprite()->addChild(bun,1);
	bun->setPosition(20, 40);
}

void Bun::loseBun(Player * player)
{
	if (player->getBunType() == 0) return;
	player->addSpeed(-0.5f);
	player->setBunType(0);
	player->getSprite()->removeChildByTag(1);
}


Bazooka* Bazooka::create()
{
	Bazooka* baz = new Bazooka();
	if (baz && baz->initWithFile(Path::picBazooka))
	{
		baz->autorelease();
		return baz;
	}
	CC_SAFE_DELETE(baz);
	return nullptr;
}

void Bazooka::start()
{
	scheduleUpdate();
}

void Bazooka::update(float det)
{
	Vec2 pos = this->getPosition();

	for (auto it = bombList.begin(); it != bombList.end(); ++it){
		if ((*it)->getPosition() == pos){
			explode();
			(*it)->explode();
			return;
		}
	}

	for (auto it = Player::Players.begin(); it != Player::Players.end(); ++it){
		auto player = it->second;
		if (player->getPostion() != pos) continue;
		else{
			explode();
			player->getDamageByBomb();
			return;
		}
	}

	if (m_map->ifCanDamage(pos)) {
		explode();
		m_map->damage(pos);
		auto tile = m_map->positionToTileCoord(pos);
		SendMsg_DamageMap(tile.x, tile.y);
	}
	else {
		if (!m_map->ifCanMove(pos)) {
			explode();
		}
	}
}

void Bazooka::explode()
{
	Vec2 pos = getPosition();
	creatWater(pos);
	unscheduleUpdate();
	this->removeFromParent();
}
