#include<iostream>
#include"Msg.h"
#include "json/json.h"
#include"every.h"
#pragma comment(lib, "json_vc71_libmtd.lib")
using namespace std;

int HandleMsg(string strdata)
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

	if (msg["Walk"].asBool())
	{
		root = msg["Walk"];
		cocos2d::Vec2 pos;
		pos.x = root["X"].asInt();
		pos.y = root["Y"].asInt();
		std::string name = root["Name"].asString();
		Players[name]->msg_walk_pos = pos;
		cout << "Walk " << name << endl;
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
	return 1;
}