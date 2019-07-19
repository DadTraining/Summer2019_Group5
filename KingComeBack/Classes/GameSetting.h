#pragma once
#include "cocos2d.h"

USING_NS_CC;

class GameSetting
{
public:
	~GameSetting();
	static GameSetting* getIntance();
	void setEnableMusic(bool enable);
	bool isEnableMusic();
	void setEnableSound(bool enable);
	bool isEnableSound();
	void setVolume(int volume);
	int getVolume();
private:
	static GameSetting* sInstance;
	bool mISEnableMusic;
	bool mIsEnableSound;
	int mVolume;

	GameSetting();
};


