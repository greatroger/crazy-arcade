#pragma once
#include<iostream>
int SendMsg_Walk(int x, int y);
int SendMsg_Bomb(int x, int y);
int SendMsg_Start();
int SendMsg_Dead();
int HandleMsg(std::string strdata);