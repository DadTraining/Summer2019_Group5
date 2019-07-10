#pragma once
#include"cocos2d.h"
#include"SneakyButton.h"
#include"SneakyButtonSkinnedBase.h"
#include"SneakyJoystickSkinnedBase.h"

USING_NS_CC;
const float wigthWall = 1;
const float heightWall = 1;

const float BITMASK_MAP = 100;
const float BITMASK_CAMERA = 101;

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
	void OnTouchEnd(Touch *touch, Event *unused_event);

	bool OnContactBegin(PhysicsContact &contact);

	void AddMap();
	void AddCamera();
	void AddListener();
	void AddJoystick();
	void AddButton();

	void createLayerUI();

	//void update(float dt);

	CREATE_FUNC(GamePlayScene);
private:
	Size screenSize;
	Vec2 touchLocation[2];
	TMXTiledMap *map;
	Size sizeWall;

	SneakyJoystick *leftJoystick;
	SneakyButton *jumpBtn;

	GamePlayScene *layerUI;

	static const int indexMap = 1;
	static const int indexCamera = 3;
	static const int indexJoystick = 3;
	static const int indexLayerUI = 2;
};

