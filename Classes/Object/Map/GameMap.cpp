#include "GameMap.h"
#include"Object/Map/BunHouse.h"
#include"Object/Map/Normal.h"
USING_NS_CC;

MyMap* GameMap::create(int mapID)
{
	switch (mapID)
	{
	default:
		break;
	case Village:
		return Normal::create(Path::picMap[Village]);
	case Tomb:
		return Normal::create(Path::picMap[Tomb]);
	case BunHouse:
		return BunHouse::create(Path::picMap[BunHouse]);
	}
	return nullptr;
}


void GameMap::DeadAudioPlay(Sprite* layer)
{
	layer->setPosition(0, 0);
	layer->setAnchorPoint(Vec2(0, 0));
	layer->setScaleY(1.2f);

	auto act1 = DelayTime::create(1.0f);
	auto act2 = CallFunc::create([layer]()
	{
		layer->removeAllChildren();
		auto size = layer->getContentSize();
		auto label = Label::createWithTTF("3", "fonts/Marker Felt.ttf", 200);
		label->setPosition(size.width / 2, size.height / 2-20);
		layer->addChild(label, 1);
	});
	layer->runAction(Sequence::create(act1, act2, nullptr));

	auto act3 = DelayTime::create(2.0f);
	auto act4 = CallFunc::create([layer]()
	{
		layer->removeAllChildren();
		auto size = layer->getContentSize();
		auto label = Label::createWithTTF("2", "fonts/Marker Felt.ttf", 200);
		label->setPosition(size.width / 2, size.height / 2-20);
		layer->addChild(label, 1);
	});
	layer->runAction(Sequence::create(act3, act4, nullptr));

	auto act5 = DelayTime::create(3.0f);
	auto act6 = CallFunc::create([layer]()
	{
		layer->removeAllChildren();
		auto size = layer->getContentSize();
		auto label = Label::createWithTTF("1", "fonts/Marker Felt.ttf", 200);
		label->setPosition(size.width / 2, size.height / 2-20);
		layer->addChild(label, 1);
	});
	layer->runAction(Sequence::create(act5, act6, nullptr));

	auto act7 = DelayTime::create(3.5f);
	auto act8 = CallFunc::create([layer]()
	{
		layer->removeAllChildren();
		layer->removeFromParent();
	});
	layer->runAction(Sequence::create(act7, act8, nullptr));

}

