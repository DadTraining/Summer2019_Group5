//#include "GameSetting.h"
//
//GameSetting* GameSetting::sInstance = nullptr;
//
//GameSetting::GameSetting() :
//	mISEnableMusic(true),
//	mIsEnableSound(true),
//	mVolume(100)
//{
//
//}
//
//GameSetting::~GameSetting()
//{
//}
//
//GameSetting * GameSetting::getIntance()
//{
//	if (sInstance == nullptr)
//	{
//		sInstance = new GameSetting();
//	}
//	return sInstance;
//}
//
//void GameSetting::setEnableMusic(bool enable)
//{
//	mISEnableMusic = enable;
//}
//
//bool GameSetting::isEnableMusic()
//{
//	return mISEnableMusic;
//}
//
//void GameSetting::setEnableSound(bool enable)
//{
//	mIsEnableSound = enable;
//}
//
//bool GameSetting::isEnableSound()
//{
//	return mIsEnableSound;
//}
//
//void GameSetting::setVolume(int volume)
//{
//	mVolume = volume;
//}
//
//int GameSetting::getVolume()
//{
//	return mVolume;
//}
