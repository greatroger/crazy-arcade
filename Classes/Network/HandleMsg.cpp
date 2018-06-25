#include"Network/Msg.h"
#include "json/json.h"
#include"cocos2d.h"
#include"Global/Player.h"
#include<assert.h>
#include<mutex>

//#pragma comment(lib, "json_vc71_libmtd.lib")
#pragma comment(lib, "jsoncpp.lib")
using cocos2d::Vec2;
using namespace std;

static map <string, void(*)(Json::Value&)> handlefunSet;
void handle_Hello(Json::Value& msg);
void handle_LoginFeedback(Json::Value& msg);
void handle_Walk(Json::Value& msg);
void handle_Bomb(Json::Value& msg);
void handle_ChangeSprite(Json::Value& msg);
void handle_ChangeMode(Json::Value& msg);
void handle_ChangeMap(Json::Value& msg);
void handle_CreateProp(Json::Value& msg);
void handle_Chat(Json::Value& msg);
void handle_PickupProp(Json::Value& msg);
void handle_LoseBun(Json::Value& msg);
void handle_PickupBun(Json::Value& msg);
void handle_UseProp(Json::Value& msg);
void handle_Start(Json::Value& msg);
void handle_StopConnect(Json::Value& msg);
void handle_GameOver(Json::Value& msg);
void handle_GetHurt(Json::Value& msg);

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
	registerMsg("Login", handle_LoginFeedback);
	registerMsg("Walk", handle_Walk);
	registerMsg("Bomb", handle_Bomb);
	registerMsg("ChangeSprite", handle_ChangeSprite);
	registerMsg("ChangeMap", handle_ChangeMap);
	registerMsg("ChangeMode", handle_ChangeMode);
	registerMsg("CreateProp", handle_CreateProp);
	registerMsg("Chat", handle_Chat);
	registerMsg("PickupProp", handle_PickupProp);
	registerMsg("PickupBun", handle_PickupBun);
	registerMsg("LoseBun", handle_LoseBun);
	registerMsg("UseProp", handle_UseProp);
	registerMsg("Start", handle_Start);
	registerMsg("GameOver", handle_GameOver);
	registerMsg("StopConnect", handle_StopConnect);
	registerMsg("GetHurt", handle_GetHurt);
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

static void handle_LoginFeedback(Json::Value& msg)
{
	int type = msg["Type"].asInt();
	cout << "login   " << type << endl;
	Msg::Login.loginFeedbackType = type;
}

static void handle_GameOver(Json::Value& msg)
{
	Msg::Game.isgameOver = true;
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
	Msg::Game.isstart = true;
	cout << "Start" << endl;
}

void handle_StopConnect(Json::Value& msg)
{
	std::string name = msg["Name"].asString();
	if (name == "") return;
	Player::Players[name]->isconnect = false;
}

static void handle_Walk(Json::Value& msg)
{
	cocos2d::Vec2 pos;
	pos.x = msg["X"].asInt();
	pos.y = msg["Y"].asInt();
	int dir = msg["Dir"].asInt();
	int step = msg["Step"].asInt();
	std::string name = msg["Name"].asString();
	Player::Players[name]->Msg.addWalk(pos, dir, step);
}

void handle_CreateProp(Json::Value& msg)
{
	Vec2 pos;
	pos.x = msg["X"].asInt();
	pos.y = msg["Y"].asInt();
	int type = msg["Type"].asInt();
	Msg::Game.addProp(pos, type);
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
	Msg::Room.mapID = mapID;
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

static void handle_GetHurt(Json::Value& msg)
{
	std::string name = msg["Name"].asString();
	Player::Players[name]->Msg.isinpop = true;
}

static void handle_PickupProp(Json::Value& msg)
{
	std::string name = msg["Name"].asString();
	int type = msg["Type"].asInt();
	Player::Players[name]->msg_pickupProp = type;
	cout << "PickupProp  " << name << endl;
}

static void handle_PickupBun(Json::Value& msg)
{
	std::string name = msg["Name"].asString();
	bool n = msg["IsFromHouse"].asBool();
	int bunType = msg["BunType"].asInt();
	Vec2 pos;
	pos.x = msg["X"].asInt();
	pos.y = msg["Y"].asInt();

	Player::Players[name]->Msg.PickupBun.bunType = bunType;
	Player::Players[name]->Msg.PickupBun.isFromHouse = n;
	Player::Players[name]->Msg.PickupBun.pos = pos;
	cout << "PickupBun  " << name << endl;
}

static void handle_LoseBun(Json::Value& msg)
{
	std::string name = msg["Name"].asString();
	bool n = msg["IsFromHouse"].asBool();
	int bunType = msg["BunType"].asInt();
	Vec2 pos;
	pos.x = msg["X"].asInt();
	pos.y = msg["Y"].asInt();

	Player::Players[name]->Msg.LoseBun.bunType = bunType;
	Player::Players[name]->Msg.LoseBun.isFromHouse = n;
	Player::Players[name]->Msg.LoseBun.pos = pos;
	cout << "PickupBun  " << name << endl;
}

static void handle_UseProp(Json::Value& msg)
{
	std::string name = msg["Name"].asString();
	int type = msg["Type"].asInt();
	Player::Players[name]->msg_useProp = type;
	cout << "UseProp  " << name << endl;
}

