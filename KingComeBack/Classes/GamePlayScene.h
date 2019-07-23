#pragma once
#include"cocos2d.h"
#include"SneakyButton.h"
#include"SneakyButtonSkinnedBase.h"
#include"SneakyJoystickSkinnedBase.h"
#include"ui/CocosGUI.h"
#include"VisibleRect.h"
#include"Popup.h"
#include"TownHall.h"
#include"ScoutTown.h"
#include "Hero.h"
#include "Knight.h"

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


	virtual bool init() override;

	void createLayer2D();

	bool OnTouchBegan(Touch *touch, Event *unused_event);
	void OnTouchMove(Touch *touch, Event *unused_event);
	void OnTouchEnd(Touch *touch, Event *unused_event);

	bool OnContactBegin(PhysicsContact &contact);

	void AddMap();
	void AddCameraUSER1();
	void AddCameraUSER2();
	void AddListener();
	void AddJoystick();
	void AddButtonPopUpHero();
	void AddButtonPopUpHouse();
	void AddSpriteUI();
	void AddPopupHero();
	void AddPopupHouse();

	void AddEventForPopupTownHall();
	void AddEventForPopupScoutTown();

	void createLayerUI();

	void update(float dt) override;

	void heroAttack(int);

	void createButtonAttack();

	void AddKnight();


	CREATE_FUNC(GamePlayScene);
private:
	Size screenSize;
	TMXTiledMap *map;
	Size sizeWall;
	Vec2 positionJoystick;
	Sprite *joystickBack;
	Sprite *joystick;
	Camera *camera;
	Camera *cameraUS2;
	bool createListenerForTownHall = true;

	SneakyJoystick *leftJoystick;
	SneakyJoystickSkinnedBase *joystickBase;
	SneakyJoystick *aJoystick;

	GLView *MyGLView;

	Layer *_layer2D;
	Layer *_layerUI;

	static const int indexMap = 1;
	static const int indexCamera = 4;
	static const int indexJoystick = 3;
	static const int indexLayerUI = 2;

	Size mapContentSize;
	Point touchCurrenPositon;

	ScoutTown *newScoutTown;
	TownHall *newHallTown;
  
	cocos2d::Animation * animaton;


	Sprite* gameSprite;
	Sprite * gameSpriteAttack;
	CCCallFunc * callBackAttack;
	Vec2 tempTouch;
	bool stateTouchHero = false;
	
	PhysicsBody * bodyA;
	Vec2 tempPositinSprite;
	int count = 0;
	Action* mListAction[10];
	Sprite * mButtonAttack;
	Vec2  mCurrentTouch;
	Hero * hero;

	// Knight
	Knight *knight;

};

