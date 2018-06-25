#pragma once
#include"cocos2d.h"
#include"Object/Map/MyMap.h"
#include"Global/Player.h"

//���߹�����
//������Ϸ�е��ߵĲ�����ʹ��
//Ŀǰ���߰��� Ь�ӣ�ˮ�ݣ�ҩˮ����������
class PropManager :public cocos2d::Layer
{
public:
	PropManager();
	~PropManager();
	void start(MyMap * map);
	CREATE_FUNC(PropManager);
	static int RandProp();
private:

	Player *m_player;
	MyMap *m_map;
	void pickupProp(int type,Player* player);
	void useProp(int type, Player * player);
	void useProp_bazooka(Player * player);
	void useProp_stopwatch(Player * player);
	void update(float det);
};

