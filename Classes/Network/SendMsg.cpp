#include"Network/Msg.h"
#include "json/json.h"
#include"Client.h"
#include"Global/Player.h"
//#pragma comment(lib, "json_vc71_libmtd.lib")
#pragma comment(lib, "jsoncpp.lib")
//本文件实现了游戏消息发送函数

Msg_Room Msg::Room;
Msg_Game Msg::Game;
Msg_Login Msg::Login;

void SendMsg_Walk(int dir, int step,int x, int y)
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["X"] = x;
	writedata["Y"] = y;
	writedata["Dir"] = dir;
	writedata["Step"] = step;
	writedata["Name"] = Player::local_Username;
	data["Walk"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
}


void SendMsg_Bomb(int x, int y)
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["X"] = x;
	writedata["Y"] = y;
	writedata["Name"] = Player::local_Username;
	data["Bomb"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
}

void SendMsg_Start()
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["Name"] = Player::local_Username;
	data["Start"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
}

void SendMsg_Dead()
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["Name"] = Player::local_Username;
	data["Dead"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
}

void SendMsg_PickupProp(std::string& name,int type)
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["Name"] = name;
	writedata["Type"] = type;
	data["PickupProp"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
}


void SendMsg_PickupBun(bool isFromHouse,int bunType, cocos2d::Vec2 pos)
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["Name"] = Player::local_Username;
	writedata["IsFromHouse"] = isFromHouse;
	writedata["BunType"] = bunType;
	writedata["X"] = int(pos.x);
	writedata["Y"] = int(pos.y);
	data["PickupBun"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
}

void SendMsg_LoseBun(bool isFromHouse, int bunType,cocos2d::Vec2 pos)
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["Name"] = Player::local_Username;
	writedata["IsFromHouse"] = isFromHouse;
	writedata["BunType"] = bunType;
	writedata["X"] = int(pos.x);
	writedata["Y"] = int(pos.y);
	data["LoseBun"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
}
void SendMsg_Hello(std::string& name)
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["Name"] =name;
	data["Hello"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
}

void SendMsg_ChangeSprite(std::string& name)
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["Name"] = name;
	data["ChangeSprite"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
}

void SendMsg_ChangeMap(int mapID)
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["Number"] = mapID;
	data["ChangeMap"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
}

void SendMsg_ChangeMode(int modeID)
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["Number"] = modeID;
	data["ChangeMode"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
}

void SendMsg_Chat(std::string& msg)
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["Name"] = Player::local_Username;
	writedata["Msg"] = msg;
	data["Chat"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
}

void SendMsg_Map(int x, int y, std::string& type)
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["X"] = x;
	writedata["Y"] = y;
	writedata["Type"] =type ;
	data["Map"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
}

void SendMsg_CreateProp(int x, int y,int type)
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["X"] = x;
	writedata["Y"] = y;
	writedata["Type"] = type;
	data["CreateProp"] = writedata;
	std::cout << x << "  " << y << std::endl;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
}

void SendMsg_DamageMap(int x,int y)
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["X"] = x;
	writedata["Y"] = y;
	std::cout << x << "  " << y << std::endl;
	data["DamageMap"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
}

void SendMsg_UseProp(std::string& name,int type)
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["Name"] = name;
	writedata["Type"] = type;
	data["UseProp"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
}

void SendMsg_GetBunScore(int team)
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["Team"] = team;
	data["GetBunScore"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
}

void SendMsg_GetHurt()
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["Name"] = Player::local_Username;
	data["GetHurt"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
}

void SendMsg_Ready()
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["Name"] = Player::local_Username;
	data["Ready"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
}