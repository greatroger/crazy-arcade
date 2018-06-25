#pragma once
#include"cocos2d.h"
#include"Object/GameMap.h"

//��Ϸ������
//����Ϸ�����м�����Ϸ��ͼ
//�������ƶ���������ˣ���Ϸ����
class GameScene:public cocos2d::Scene
{
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	bool init();
	void start(int mapID);
private:
	void update(float delta);
	void walkUpdate(float tmd);
	void addMap(int mapID);
	void addSprite();
	void addManager();
	void checkOver();
	void checkPop();
	MyMap *m_map;
};

