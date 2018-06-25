#include "Bazooka.h"
#include"Global/Global.h"
#include"Global/Player.h"
#include"Object/Pop.h"
USING_NS_CC;

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

void Bazooka::start(MyMap * map)
{
	m_map = map;
	assert(map != nullptr);
	m_picWater = Path::picBawater;
	scheduleUpdate();
}

void Bazooka::update(float det)
{
	Vec2 pos = this->getPosition();
	//×²ÉÏÕ¨µ¯
	for (auto it = bombList.begin(); it != bombList.end(); ++it) {
		if ((*it)->getPosition() == pos) {
			explode();
			return;
		}
	}
	//×²ÉÏ½¨ÖþÎï
	pos = m_map->standard(pos);
	if (!m_map->ifCanMove(pos)) 
	{
		if (m_map->ifCanDamage(pos)){
			m_map->damage(pos);
		}
		explode();
		return;
	}
	//×²ÉÏÍæ¼Ò
	auto player = Player::local_player;
	Vec2 playerpos = player->getPosition();
	float distance = (abs(playerpos.x - pos.x) + abs(playerpos.y - pos.y)) / 2;

	if (distance > 5) return;
	if (player->isgold)return;
	if (player->isinpop)return;
	SendMsg_GetHurt();
	explode();
}

void Bazooka::explode()
{
	//»ð¼ý±¬Õ¨
	Vec2 pos = getPosition();
	creatWater(pos);
	unscheduleUpdate();
	Music::PlayMusic(Music::music::bombExplode);
	this->removeFromParent();
}

