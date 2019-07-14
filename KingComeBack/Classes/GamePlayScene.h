#pragma once
#include"cocos2d.h"
#include"SneakyButton.h"
#include"SneakyButtonSkinnedBase.h"
#include"SneakyJoystickSkinnedBase.h"
#include"ui/UISlider.h"
#include"VisibleRect.h"

USING_NS_CC;
const float wigthWall = 1;
const float heightWall = 1;

const int BITMASK_MAP = 100;
const int BITMASK_LAYER_UI = 101;

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

	void update(float dt) override;

	CREATE_FUNC(GamePlayScene);
private:
	Size screenSize;
	TMXTiledMap *map;
	Size sizeWall;
	Vec2 positionJoystick;
	Sprite *joystickBack;
	Sprite *joystick;

	bool moveOutBackground = true;

	SneakyJoystick *leftJoystick;
	SneakyJoystickSkinnedBase *joystickBase;
	SneakyJoystick *aJoystick;

	GLView *MyGLView;

	Layer *layerUI;

	static const int indexMap = 1;
	static const int indexCamera = 4;
	static const int indexJoystick = 3;
	static const int indexLayerUI = 2;

	Size mapContentSize;
	Point touchCurrenPositon;
};

