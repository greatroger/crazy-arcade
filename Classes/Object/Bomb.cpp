#include "Bomb.h"
#include"Global/Global.h"
#include"Network/Msg.h"
#include"Object/Pop.h"
USING_NS_CC;

std::list<Bomb*> Bomb::bombList;


Bomb::Bomb()
{
	
}

Bomb::~Bomb()
{}


void Bomb::start(cocos2d::Vec2 pos, Player* player, MyMap* map)
{
	m_picBomb = Path::Player::getPicBomb(player->getNumber());
	m_picWater = Path::Player::getPicWater(player->getNumber());
	m_width = player->getBombWidth();
	m_player= player;
	m_map = map;

	//ը����������
	Texture2D *bombPlay = Director::getInstance()->getTextureCache()->addImage(m_picBomb);
	Vector<SpriteFrame *> animFrames(14);
	for (int i = 0; i <3; ++i) {
		SpriteFrame* frame = SpriteFrame::createWithTexture(bombPlay, Rect(72 * i, 0, 72, 72));
		animFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
	runAction(RepeatForever::create(Animate::create(animation)));

	//����ը������ը������
	bombList.push_back(this);

	m_player->addBombNum(1);
	this->setPosition(pos);
	m_map->setNomove(pos);

	//3s��ը
	auto act1 = DelayTime::create(3.0f);
	auto act2 = CallFunc::create([this]()
	{
		explode();
	});
	runAction(Sequence::create(act1, act2, nullptr));
}


void Bomb::explode()
{
	Vec2 pos = getPosition();
	hurtPlayer(pos);
	creatWater(pos);
	
	Music::PlayMusic(Music::music::bombExplode);

	//���Լ���ը�������Ƴ�
	for (auto it = bombList.begin(); it != bombList.end(); ++it)
	{
		if ((*it)->getPosition() == pos)
		{
			bombList.erase(it);
			m_map->removeNomove(pos);
			break;
		}
	} 

	//�ƻ���ͼ����
	if (m_map->ifCanDamage(pos)) {
		m_map->damage(pos);
	}

	m_player->addBombNum(-1);

	//һ��ը�����ĸ�����ı�ը
	Remove(0, 1);
	Remove(1, 0);
	Remove(0, -1);
	Remove(-1, 0);
	this->removeFromParent();
}

void Bomb::Remove(int a, int b)
{
	Size size = m_map->getTileSize();
	int bombWidth = m_width;
	Vec2 pos = getPosition();

	while (--bombWidth >= 0)
	{
		pos.x += a * size.width;
		pos.y += b * size.height;

		//���������˺�(����ɶ���˺����ش˼�¼�� 
		hurtPlayer(pos);

		//����������ը
		for (auto it = bombList.begin(); it != bombList.end(); ++it)
		{
			if ((*it)->getPosition() == pos)
			{
				(*it)->explode();
				break;
			}
		}

		//�ƻ���ͼ����
		if (!m_map->ifCanMove(pos))
		{
			if (m_map->ifCanDamage(pos)) {
				m_map->damage(pos);
				creatWater(pos);
			}
			break;
		}
		else {
			if (m_map->ifCanDamage(pos)) {
				m_map->damage(pos);
			}
			creatWater(pos);
		}
	}
}

void Bomb::creatWater(Vec2 pos) //����ˮ��
{
	auto water = Sprite::create(m_picWater);
	water->setPosition(Vec2(pos.x, pos.y));
	m_map->addChild(water,5);
	auto act1 = DelayTime::create(0.3f);
	auto act2 = CallFunc::create([water]() {
		water->removeFromParent();
	});
	water->runAction(Sequence::create(act1, act2, nullptr));
}

void Bomb::hurtPlayer(Vec2 pos)
{
	for (auto it = Player::Players.begin(); it != Player::Players.end(); ++it)
	{
		auto player = it->second;
		Vec2 playerpos = player->getPosition();
		playerpos = m_map->standard(playerpos);

		if (playerpos != pos) continue;
		if (player->isgold)continue;
		if (player->isinpop)continue;

		player->isinpop = true;
		auto pop = Pop::create(player->m_team, player);
		player->getSprite()->addChild(pop);
		pop->setPosition(Vec2(20,20));
	}
}

