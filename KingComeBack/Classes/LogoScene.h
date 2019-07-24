#pragma once
#include "cocos2d.h"

USING_NS_CC;

class LogoScene : public Scene
{
public:
	LogoScene();
	~LogoScene();
	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(LogoScene);
private:
	Sprite* logoScene;
};

