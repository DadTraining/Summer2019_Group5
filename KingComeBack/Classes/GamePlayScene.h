#pragma once
#include"cocos2d.h"

USING_NS_CC;

class GamePlayScene :public cocos2d::Scene
{
public:
	GamePlayScene();
	~GamePlayScene();

	static Scene *createScene();
	Camera *camera;

	virtual bool init() override;

	bool OnTouchBegan(Touch *touch, Event *unused_event);
	void OnTouchMove(Touch *touch, Event *unused_event);

	CREATE_FUNC(GamePlayScene);
private:
	Vec2 touchLocation;
	TMXTiledMap *map;
};

