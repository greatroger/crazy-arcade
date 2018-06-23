#include"Global/Global.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace Music;
bool Setting::musicSwitch = true;

void Music::PlayMusic(music type)
{
	if (!Setting::musicSwitch) return;
	switch (type)
	{
	default:
		break;
	case Music::main:
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/mainScene.mp3", true);
		break;
	case Music::room:
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/roomScene.mp3", true);
		break;
	case Music::village:
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/village.mp3", true);
		break;
	case Music::tomb:
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/tomb.mp3", true);
		break;
	case Music::ice:
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/ice.mp3", true);
		break;
	case Music::bunHouse:
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/bunHouse.mp3", true);
		break;
	case Music::setbomb:
		SimpleAudioEngine::getInstance()->playEffect("Music/bombset.wav", false);
		break;
	case Music::bombExplode:
		SimpleAudioEngine::getInstance()->playEffect("Music/bombexplode.wav", false);
		break;
	case Music::eatProp:
		SimpleAudioEngine::getInstance()->playEffect("Music/eatProp.mp3", false);
		SimpleAudioEngine::getInstance()->setEffectsVolume(1);
		break;
	case Music::poplive:
		SimpleAudioEngine::getInstance()->playEffect("Music/poplive.wav", false);
		break;
	case Music::popdie:
		SimpleAudioEngine::getInstance()->playEffect("Music/popdie.wav", false);
		break;
	case Music::win:
		SimpleAudioEngine::getInstance()->playEffect("Music/win.wav", false);
		SimpleAudioEngine::getInstance()->setEffectsVolume(1);
		break;
	case Music::start:
		SimpleAudioEngine::getInstance()->playEffect("Music/gameStart.mp3", false);
		SimpleAudioEngine::getInstance()->setEffectsVolume(1);
		break;
	case Music::stopwatch:
		break;
	}
}

void Music::stopMusic()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}