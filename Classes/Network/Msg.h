#pragma once
#include<iostream>
#include"cocos2d.h"

void SendMsg_Hello(std::string&);
void SendMsg_Walk(int x, int y);
void SendMsg_Bomb(int x, int y);
void SendMsg_Start();
void SendMsg_Dead();
void SendMsg_Map(int x, int y,std::string&);
void SendMsg_Chat(std::string&);
void SendMsg_ChangeSprite(std::string&name );
void SendMsg_ChangeMap(int mapID);
void SendMsg_ChangeMode(int modeID);
void SendMsg_PickupProp(std::string& name, int type);
void SendMsg_CreateProp(int x, int y,int type);
void SendMsg_DamageMap(int x,int y);
void SendMsg_UseProp(std::string& name,int type);
void SendMsg_GetBunScore();
void SendMsg_Ready();
void HandleMsg(const std::string& strdata);

#define FOR_Msg_Player for (auto it = Msg::Players.begin(); it != Msg::Players.end(); ++it)

struct Msg_Player
{
	cocos2d::Vec2  msg_bomb;
	std::string msg_chat;
	int msg_pickupProp, msg_useProp;
	cocos2d::Vec2 msg_createprop_pos;
	int msg_walk, msg_dir, msg_createprop_type, msg_changeMap, msg_changeMode;
	bool ischange;
};

struct Msg_Room
{
	bool ismapchange, ismodechange,isstart;
};

namespace Msg {
    extern	std::map<std::string, Msg_Player*> Players;
	extern Msg_Room Room;
};