#include"Msg.h"
#include "json/json.h"
#include"every.h"
#include"Client.h"
#pragma comment(lib, "json_vc71_libmtd.lib")

int SendMsg_Walk(int x, int y)
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["X"] = x;
	writedata["Y"] = y;
	writedata["Name"] = g_name;
	data["Walk"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
	return 1;
}

int SendMsg_Bomb(int x, int y)
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["X"] = x;
	writedata["Y"] = y;
	writedata["Name"] = g_name;
	data["Bomb"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
	return 1;
}

int SendMsg_Start()
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["Name"] = g_name;
	data["Start"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
	return 1;
}

int SendMsg_Dead()
{
	Json::Value data, writedata;
	Json::FastWriter writer;
	writedata["Name"] = g_name;
	data["Dead"] = writedata;
	std::string senddata = writer.write(data);
	SendMsg(senddata);
	return 1;
}