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

	for (auto it = bombList.begin(); it != bombList.end(); ++it) {
		if ((*it)->getPosition() == pos) {
			explode();
			(*it)->explode();
			return;
		}
	}

	FOR_ALL_PLAYERS
	{
		auto player = it->second;
	Vec2 playerpos = player->getPosition();
	float distance = (abs(playerpos.x - pos.x) + abs(playerpos.y - pos.y)) / 2;

	if (distance>5) continue;
	if (player->isgold)continue;
	if (player->isinpop)continue;

	player->isinpop = true;
	auto pop = Pop::create(player->m_team, player);
	player->getSprite()->addChild(pop);
	pop->setPosition(Vec2(20, 20));

	explode();
	return;
	}

	pos = m_map->standard(pos);
	if (!m_map->ifCanMove(pos)) 
	{
		if (m_map->ifCanDamage(pos)){
			m_map->damage(pos);
		}
		explode();
	}
}

void Bazooka::explode()
{
	Vec2 pos = getPosition();
	creatWater(pos);
	unscheduleUpdate();
	Music::PlayMusic(Music::music::bombExplode);
	this->removeFromParent();
}

