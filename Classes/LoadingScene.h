#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class LoadingScene : public Scene
{
public:
	LoadingScene();
	~LoadingScene();
	static Scene* createScene();
	virtual bool init() override;
	void update(float detaTime) override;

	CREATE_FUNC(LoadingScene);
private:
	Sprite *background, *loadingBar, *loadingPress;
	Label *lbLoading, *lbNameGame;
	float scale = 0;
};


