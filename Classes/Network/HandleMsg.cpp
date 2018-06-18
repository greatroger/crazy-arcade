#include"Network/Msg.h"
#include "json/json.h"
#include"cocos2d.h"
#include"Global/Player.h"
#include<assert.h>

#pragma comment(lib, "json_vc71_libmtd.lib")

using namespace std;

static map <string, void(*)(Json::Value&)> handlefunSet;
void handle_Hello(Json::Value& msg);
void handle_Walk(Json::Value& msg);
void handle_Bomb(Json::Value& msg);
void handle_ChangeSprite(Json::Value& msg);
void handle_ChangeMode(Json::Value& msg);
void handle_ChangeMap(Json::Value& msg);
void handle_CreateProp(Json::Value& msg);
void handle_Chat(Json::Value& msg);
void handle_PickupProp(Json::Value& msg);
void handle_UseProp(Json::Value& msg);
void handle_Start(Json::Value& msg);
void handle_StopConnect(Json::Value& msg);

void HandleMsg(const string& strmsg)
{
	if (strmsg.empty()) return;
	printf(strmsg.c_str());
	Json::Reader reader;
	Json::Value jsonmsg;
	reader.parse(strmsg, jsonmsg);
	Json::Value::Members members=jsonmsg.getMemberNames();
	std::string msgType = *(members.begin());
	assert(handlefunSet.find(msgType) != handlefunSet.end());
	if (handlefunSet.find(msgType)==handlefunSet.end()) return;

	Json::Value msg = jsonmsg[msgType];
	handlefunSet[msgType](msg);
}


static void registerMsg(const string& msgType,void handlefun(Json::Value&))
{
	assert(!msgType.empty());
	assert(handlefun != nullptr);
	handlefunSet[msgType] = handlefun;
}

void MsgLoad()
{
	registerMsg("Hello", handle_Hello);
	registerMsg("Walk", handle_Walk);
	registerMsg("Bomb", handle_Bomb);
	registerMsg("ChangeSprite", handle_ChangeSprite);
	registerMsg("ChangeMap", handle_ChangeMap);
	registerMsg("ChangeMode", handle_ChangeMode);
	registerMsg("CreateProp", handle_CreateProp);
	registerMsg("Chat", handle_Chat);
	registerMsg("PickupProp", handle_PickupProp);
	registerMsg("UseProp", handle_UseProp);
	registerMsg("Start", handle_Start);
	/*registerMsg("GameOver", handle_GameOver);
	registerMsg("Dead", handle_Dead);*/
}

static void handle_Hello(Json::Value& msg)
{
	std::string name = msg["Name"].asString();
	int RoomID = msg["RoomID"].asInt();
	auto player = Player::create(name);
	player->setRoomID(RoomID);
	Player::Players[name] = player;
	if (name == Player::local_Username)
		Player::local_player = player;

	handle_ChangeSprite(msg["Sprite"]);
}

static void handle_Dead(Json::Value& msg)
{

}

static void handle_GameOver(Json::Value& msg)
{

}

static void handle_Bomb(Json::Value& msg)
{
	cocos2d::Vec2 pos;
	pos.x = msg["X"].asInt();
	pos.y = msg["Y"].asInt();
	assert(pos != cocos2d::Vec2(0, 0));
	std::string name = msg["Name"].asString();
	Player::Players[name]->msg_bomb = pos;
	cout << "Bomb " << name << endl;
}

static void handle_Start(Json::Value& msg)
{
	Msg::Room.isstart = true;
	cout << "Start" << endl;
}

void handle_StopConnect(Json::Value& msg)
{
	std::string name = msg["Name"].asString();
	Player::Players[name]->isconnect = false;
}

static void handle_Walk(Json::Value& msg)
{
	int dir = msg["Dir"].asInt();
	int step = msg["Step"].asInt();
	std::string name = msg["Name"].asString();

	Player::Players[name]->msg_dir = dir;
	Player::Players[name]->msg_walk = step;
	cout << "Walk "<<name<< endl;
}

void handle_CreateProp(Json::Value& msg)
{
	cocos2d::Vec2 pos;
	pos.x = msg["X"].asInt();
	pos.y = msg["Y"].asInt();
	int type = msg["Type"].asInt();
	Player::local_player->msg_createprop_pos = pos;
	Player::local_player->msg_createprop_type = type;
}

static void handle_ChangeSprite(Json::Value& msg)
{
	std::string name = msg["Name"].asString();
	int number = msg["Number"].asInt();
	Player::Players[name]->setNumber(number);
	Player::Players[name]->ischange = true;
}

static void handle_ChangeMap(Json::Value& msg)
{
	std::string name = msg["Name"].asString();
	int mapID = msg["Number"].asInt();
	Msg::Room.ismapchange = true;
}

static void handle_ChangeMode(Json::Value& msg)
{
	std::string name = msg["Name"].asString();
	int modID = msg["Number"].asInt();
	Msg::Room.ismodechange = true;
}

static void handle_Chat(Json::Value& msg)
{
	std::string name = msg["Name"].asString();
	std::string chatmsg = msg["Msg"].asString();
	Player::Players[name]->msg_chat = chatmsg;
}

static void handle_PickupProp(Json::Value& msg)
{
	std::string name = msg["Name"].asString();
	int type = msg["Type"].asInt();
	Player::Players[name]->msg_pickupProp = type;
	cout << "PickupProp  " << name << endl;
}

static void handle_UseProp(Json::Value& msg)
{
	std::string name = msg["Name"].asString();
	int type = msg["Type"].asInt();
	Player::Players[name]->msg_useProp = type;
	cout << "UseProp  " << name << endl;
}

/*
int HandleMsg(string& strdata)
{
	Json::Reader reader;
	Json::Value root, msg;
	reader.parse(strdata, msg);
	//	cout << data << endl;

	if (msg["Start"].asBool())
	{
		g_bstart = true;
		cout << "Start" << endl;
	}

	if (msg["GameOver"].asBool())
	{
		g_bstart = false;
		cout << "GameOver" << endl;
	}

	if (msg["Dead"].asBool())
	{
		root = msg["Dead"];
		std::string name = root["Name"].asString();
		Players[name]->m_bdead = true;
		cout << name <<"  Dead" << endl;
	}



	if (msg["Hello"].asBool())
	{
		root = msg["Hello"];
		std::string name = root["Name"].asString();
		int number = root["Number"].asInt();
		cout << number << endl;
		if (number == 1)  Players[name] = &player1;
		if (number == 2)  Players[name] = &player2;
		if (number == 3)  Players[name] = &player3;
		if (number == 4)  Players[name] = &player4;
		Players[name]->m_number = number;
		Players[name]->m_name = name;
		for (auto it = Players.begin(); it != Players.end(); ++it)
		{
			it->second->m_bchange = true;
		}
		cout << "Hello " << number << endl;
	}

	if (msg["Bomb"].asBool())
	{
		root = msg["Bomb"];
		std::string name = root["Name"].asString();
		cocos2d::Vec2 pos;
		pos.x = root["X"].asInt();
		pos.y = root["Y"].asInt();
		Players[name]->msg_bomb_pos = pos;
		cout << "Bomb " << name << endl;
	}

	if (msg["Pickup"].asBool())
	{

	}
	return 1;
}
*/
