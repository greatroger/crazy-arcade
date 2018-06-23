#pragma once
#include"cocos2d.h"
#include<iostream>

namespace Path {

	namespace Player
	{
		constexpr char* colour[] = {
			"red","blue","fat","bee","strong","purple","nannan","cute","dragon","captain"
		};
		constexpr char picGold[] = "Player/gold.png";

		constexpr char player[] = "Player/";
		constexpr char* sprite[] = {
			"/up.png",
			"/down.png",
			"/left.png",
			"/right.png",
		};
		constexpr char bomb[] = "/bomb.png";
		constexpr char water[] = "/water.png";
		constexpr char character[] = "/face.png";

		static std::string getPicSprite(const int ID,const int direction)
		{
			// such as  path = "Player/red/up.png"
			std::string path = "";
			path=path + player + colour[ID] + sprite[direction];
			return path;
		}

		static std::string getPicBomb(const int ID)
		{
			std::string path = "";
			path=path + player + colour[ID] + bomb;
			return path;
		}

		static std::string getPicWater(const int ID)
		{
			std::string path = "";
			path = path + player+ colour[ID] + water;
			return path;
		}

		static std::string getPicCharacter(const int ID)
		{
			std::string path = "";
			path = path + player + colour[ID] + character;
			return path;
		}
	}

	constexpr char* picMap[] = {
		"Map/village/village.tmx",
		"Map/ice/ice.tmx",
		"Map/tomb/tomb.tmx",
		"Map/bunHouse/bunHouse.tmx"
	};

	constexpr char* picProp[] = {
		"Prop/speed.png",
		"Prop/power.png",
		"Prop/bubble.png",
		"Prop/rpg.png",
		"Prop/stopwatch .png",
	};
	constexpr char* picBun[] = {
		"Prop/redbun.png",
		"Prop/bluebun.png",
	};

	constexpr char* picPop[] = {
		"Player/pop.png",
		"Player/popbreak2.png",
		"Player/popbreak1.png",
	};

	constexpr char picBazooka[] = "Prop/bazooka.png";
	constexpr char picBawater[] = "Prop/bawater.png";
}

namespace Setting {
	constexpr int MaxMapNum = 4;
	extern bool musicSwitch;
}

namespace Music {
	enum music {
		main,room,eatProp,setbomb,bombExplode,win,start,tomb,village,ice,bunHouse,stopwatch,poplive,popdie,_max
	};
	void PlayMusic(music type);
	void stopMusic();
}