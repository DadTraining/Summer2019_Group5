#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class SettingScene : public cocos2d::Layer
{
public:
	SettingScene();
	~SettingScene();
	virtual bool init();
	static cocos2d::Scene* createScene();

	CREATE_FUNC(SettingScene);
private:

};
