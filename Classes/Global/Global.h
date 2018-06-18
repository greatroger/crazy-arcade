#pragma once
#include"cocos2d.h"
#include<iostream>

namespace Path {

	namespace Player
	{
		constexpr char* colour[] = {
			"red","blue","green"
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
		"Map/tomb/tomb.tmx",
	};

	constexpr char* picProp[] = {
		"Prop/speed.png",
		"Prop/power.png",
		"Prop/bubble.png",
		"Prop/shoes.png",
		"Prop/stopwatch .png",
	};
	constexpr char* picBun[] = {
		"Prop/speed.png",
		"Prop/power.png",
	};

	constexpr char picPop[] = "Prop/pop1.png";
	constexpr char picBazooka[] = "Prop/bazooka.png";
}

namespace Setting {
	using cocos2d::Vec2;
    static 	Vec2 bornPlace[] = {
		Vec2(20,20),
		Vec2(20,740),
	};
	constexpr int MaxMapNum = 2;

	extern bool musicSwitch;
}