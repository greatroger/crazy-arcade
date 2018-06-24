#pragma once
#include<iostream>
#include"cocos2d.h"
#include<mutex>


void SendMsg_Hello(std::string&);
void SendMsg_Walk(int dir, int step, int x, int y);
void SendMsg_Bomb(int x, int y);
void SendMsg_Start();
void SendMsg_Dead();
void SendMsg_Map(int x, int y,std::string&);
void SendMsg_Chat(std::string&);
void SendMsg_ChangeSprite(std::string&name );
void SendMsg_ChangeMap(int mapID);
void SendMsg_ChangeMode(int modeID);
void SendMsg_PickupProp(std::string& name, int type);
void SendMsg_PickupBun(bool isFromHouse,int bunType, cocos2d::Vec2 pos);
void SendMsg_LoseBun(bool isFromHouse, int bunType,cocos2d::Vec2 pos);
void SendMsg_CreateProp(int x, int y,int type);
void SendMsg_DamageMap(int x,int y);
void SendMsg_UseProp(std::string& name,int type);
void SendMsg_GetBunScore(int team);
void SendMsg_GetHurt();
void SendMsg_Ready();
void HandleMsg(const std::string& strdata);

#define FOR_Msg_Player for (auto it = Msg::Players.begin(); it != Msg::Players.end(); ++it)

struct Msg_Player
{
private:
	struct msg_walk
	{
		cocos2d::Vec2 pos=cocos2d::Vec2(-1,-1);
		int step=0;
		int dir=-1;
	};
	struct msg_Bun
	{
		bool isFromHouse=false;
		int bunType=-1;
		cocos2d::Vec2 pos = cocos2d::Vec2(-1, -1);
	};
public:

	msg_Bun PickupBun,LoseBun;
	cocos2d::Vec2  msg_bomb;
	std::string msg_chat;
	int msg_pickupProp, msg_useProp;
	cocos2d::Vec2 msg_createprop_pos;
	int  msg_dir, msg_createprop_type, msg_changeMap, msg_changeMode;
	bool ischange=false,isinpop=false;

	std::vector<msg_walk> Walk;
	std::recursive_mutex walk_mutex;

	void addWalk(cocos2d::Vec2 pos, int dir,int step)
	{
		msg_walk m;
		walk_mutex.lock();
		m.pos = pos;
		m.step = step;
		m.dir = dir;
		Walk.push_back(m);
		walk_mutex.unlock();
	}
};

struct Msg_Room
{
	bool ismodechange;
	int  mapID;
};

struct Msg_Login
{
	int loginFeedbackType=-1;
};

struct Msg_Game
{
private:
	struct msg_createProp
	{
		cocos2d::Vec2 pos;
		int type;
		bool isused;
	};
public:
	bool isgameOver,isstart;
	std::vector<msg_createProp> createProp;
    std::recursive_mutex v_mutex;

	void addProp(cocos2d::Vec2 pos, int type)
	{
		msg_createProp m;
		v_mutex.lock();
		m.pos = pos;
		m.type = type;
		m.isused = false;
		createProp.push_back(m);
		v_mutex.unlock();
	}
};

namespace Msg {
	extern Msg_Room Room;
	extern Msg_Game Game;
	extern Msg_Login Login;
};