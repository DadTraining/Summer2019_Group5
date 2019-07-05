#pragma once
#include"cocos2d.h"

USING_NS_CC;

class GamePlayScene :public cocos2d::Scene
{
public:
	GamePlayScene();
	~GamePlayScene();

	static Scene *createScene();

	virtual bool init() override;

	CREATE_FUNC(GamePlayScene);
private:

};

