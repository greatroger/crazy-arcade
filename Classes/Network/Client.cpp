#include <WinSock2.h>
#include<iostream>
#include <process.h>
#include "json/json.h"
#include<cstdio>
#include"Client.h"
#include"cocos2d.h"
#include"every.h"
#include"Msg.h"
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "json_vc71_libmtd.lib")

using namespace std;
#define uPort 3563
SOCKET ClientSocket;

unsigned __stdcall ThreadRecv(void* param)
{
	char buf[1024] = { 0 };
	while (1)
	{
		int ret = recv(*(SOCKET*)param, buf, sizeof(buf), 0);
		if (ret == SOCKET_ERROR) {
			Sleep(50);
			continue;
		}
		if (ret > 0){
			cout << "recive msg  " << ret << endl;
		}
		string strdata;
		for (int i = 2; i < ret; ++i){
			strdata.push_back(buf[i]);
		}
		HandleMsg(strdata);
	}
	return 0;
}

int  StartClient(const char* _name,const char * ip)
{
	WSADATA wsaData = { 0 };//����׽�����Ϣ
	SOCKADDR_IN ServerAddr = { 0 };//����˵�ַ
	char IP[32] = { 0 };
	string name = _name;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		printf("WSAStartup failed with error code: %d\n", WSAGetLastError());
		return -1;
	}
	//�ж��׽��ְ汾
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		printf("wVersion was not 2.2\n");
		return -1;
	}
	//�����ͻ����׽���
	
	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == INVALID_SOCKET)
	{
		printf("socket failed with error code: %d\n", WSAGetLastError());
		return -1;
	}

	//���������IP
	printf("Please input server IP:");
	strcpy(IP, ip);
	//gets_s(IP);
	//���÷�������ַ
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(uPort);//�������˿�
	ServerAddr.sin_addr.S_un.S_addr = inet_addr(IP);//��������ַ

	printf("connecting......\n");
	//���ӷ�����
	if (SOCKET_ERROR == connect(ClientSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)))
	{
		printf("connect failed with error code: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return -1;
	}

	printf("Connecting server successfully IP:%s Port:%d\n",
		IP, htons(ServerAddr.sin_port));

	Json::Value data,writedata;
	Json::FastWriter writer;
	writedata["Name"] = name;
	
	data["Hello"] = writedata;

	string senddata = writer.write(data);

	char mydata[1024];
	mydata[0] = senddata.length() >> 8;
	mydata[1] = senddata.length();

	memcpy(&mydata[2], &senddata[0], senddata.length());

	_beginthreadex(NULL, 0, ThreadRecv, &ClientSocket, 0, NULL); //�������պͷ�����Ϣ�߳�

	send(ClientSocket, mydata, senddata.length() + 2, 0);
	Sleep(100);
	//closesocket(ClientSocket);
	//WSACleanup();
	return 1;
}

int SendMsg(std::string &senddata)
{
	char mydata[1024];
	mydata[0] = senddata.length() >> 8;
	mydata[1] = senddata.length();

	memcpy(&mydata[2], &senddata[0], senddata.length());
	send(ClientSocket, mydata, senddata.length() + 2, 0);
	return 1;
}
