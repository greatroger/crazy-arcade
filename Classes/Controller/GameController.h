#pragma once
#include"cocos2d.h"
#include"Global/Player.h"
#include"Object/Map/MyMap.h"

//游戏控制器类
//检测本地玩家的操作，并发送数据给服务器
//包含 移动检测（w,s,a,d) 道具或炸弹使用检测(空格） 特殊道具使用检测（e)
class GameController:public cocos2d::Layer
{
public:
	GameController();
	~GameController();
	void start(Player*, MyMap*);
	CREATE_FUNC(GameController);
	void update(float det);
private:
	struct isKeyPressed
	{
		bool w = false, s = false, d = false, a = false;
	};
	
	isKeyPressed m_bkey;
	void walkUpdate(float tmd);
	bool ifCanMove(cocos2d::Vec2&);
	void startSpaceListener();
	void startKeyEListener();
	void startKeyQListener();
	bool ifcanBomb(cocos2d::Vec2);
	void startWalkListener();
	float m_speed;
	Player* m_player;
	MyMap* m_map;
};

