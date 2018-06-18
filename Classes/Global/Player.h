#pragma once
#include"cocos2d.h"
#include"Object/MyMap.h"

class Player
{
public:
	static std::map<std::string, Player*> Players;
	static std::string local_Username;
	static Player* local_player;

	Player(const std::string& name);
	~Player();
	void setRoomID(int ID);
	void setBunType(int type);
	static Player *create(const std::string& name)
	{
		auto player = new Player(name);
		return player;
	}
	cocos2d::Sprite* createSprite();
	void runAction(MyMap* );
	void addLife(const int & life);
	void addSpeed(const float & i);
	void addMaxBombNmu(const int & i);
	void addBombWidth(const int & i);
	void addBombNum(const int & i);
	void getDamageByBomb();
	int getLife();
	bool ifcanBomb();
	int getBunType();
	bool ifcanMove();
	void setDirection(int dir);
	void setNumber(int number);
	void pickupProp(int type, int number);
	int getNumber();
	int getStopwatch();
	cocos2d::Vec2 getDirection();
	void addStopwatch(int m);
	void useProp();
	std::string getName();
	cocos2d::Sprite * getSprite();
	int getRoomID();
	int getBombWidth();
	cocos2d::Vec2 getPostion();
	float getSpeed();
	int getPropType();
	bool isDead();

	cocos2d::Vec2  msg_bomb;
	std::string msg_chat;
	int msg_pickupProp,msg_useProp;
	cocos2d::Vec2 msg_createprop_pos;
	int msg_walk,msg_dir,msg_createprop_type,msg_changeMap,msg_changeMode;
	bool ischange,isconnect,isinpop, isgold;
	enum direction {
		up, down, left, right
	};
	int m_team;
private:
	std::string m_name;
	cocos2d::Sprite* m_sprite;
	float m_speed;
	bool m_isdead,m_isunhurtable,m_ishaveBun;
	int m_roomID,m_number,m_life,m_maxBombNum,m_bombNum,m_bombWidth;
	int m_propType,m_propNum,m_stopwatch;
	int m_bunType;
	direction m_dir;
};


#define FOR_ALL_PLAYERS for (auto it = Player::Players.begin(); it != Player::Players.end(); ++it)