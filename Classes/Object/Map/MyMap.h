#pragma once
#include"cocos2d.h"

#define MAP_CREATE_FUN(__TYPE__) \
static __TYPE__* create(const std::string & tmxFile) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet->initWithTMXFile(tmxFile) && pRet->init()) \
    { \
        pRet->Myinit(); \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        CC_SAFE_DELETE(pRet);\
        return nullptr; \
    } \
}

class MyMap:public cocos2d::TMXTiledMap
{
public:
	MyMap();
	~MyMap();
	void Myinit();
	MAP_CREATE_FUN(MyMap);
	bool init();
    virtual	bool ifCanMove(cocos2d::Vec2 position);
    virtual	bool ifCanDamage(cocos2d::Vec2 pos);
    virtual	void removeNomove(cocos2d::Vec2 pos);
    virtual	void damage(cocos2d::Vec2 pos);
	cocos2d::Vec2 standard(cocos2d::Vec2 pos);
	virtual void start() {};
	bool ifInScene(cocos2d::Vec2);
	void setOrder(cocos2d::Scene *);
	void setNomove(cocos2d::Vec2 pos);

	cocos2d::Vec2 MyMap::tileCoordToPosition(cocos2d::Vec2 pos);
	cocos2d::Vec2 MyMap::positionToTileCoord(cocos2d::Vec2 pos);
protected:
	cocos2d::TMXLayer *m_nomoveLayer, *m_removeLayer, *m_backgroundLayer,
		  *m_buildingLayer,*m_building_topLayer,*m_building_top_topLayer;
	unsigned int m_gid_nomove, m_gid_remove;
};
