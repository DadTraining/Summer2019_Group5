#pragma once
#include"cocos2d.h"

USING_NS_CC;
const float wigthWall = 1;
const float heightWall = 1;

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

	void AddMap();
	void AddCamera();
	void AddPhysicWall(float _positionX, float _positionY, const float &_width, const float &_height);
	void AddPhysicCamera();
	void MoveCamera();

	CREATE_FUNC(GamePlayScene);
private:
	Size screenSize;
	Vec2 touchLocation;
	TMXTiledMap *map;
	Size sizeWall;
};

