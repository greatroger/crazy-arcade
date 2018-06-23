#include"Global/Global.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

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
	case Music::setbomb:

		break;
	case Music::explode:

		break;
	case Music::eatProp:
		SimpleAudioEngine::getInstance()->playEffect("Music/eatProp.mp3", false);
		SimpleAudioEngine::getInstance()->setEffectsVolume(1);
		break;
	case Music::win:
		SimpleAudioEngine::getInstance()->playEffect("Music/win.wav", false);
		SimpleAudioEngine::getInstance()->setEffectsVolume(1);
		break;
	case Music::start:
		SimpleAudioEngine::getInstance()->playEffect("Music/start.wav", false);
		SimpleAudioEngine::getInstance()->setEffectsVolume(1);
		break;
	case Music::village:
		break;
	case Music::tomb:
		break;
	case Music::bun:
		break;
	case Music::stopwatch:
		break;
	}
}