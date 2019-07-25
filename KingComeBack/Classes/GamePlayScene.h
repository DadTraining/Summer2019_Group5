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

#include "Dragon.h"

#include "Knight.h"

#include "Bullet.h"


USING_NS_CC;
const float wigthWall = 1;
const float heightWall = 1;

const int BITMASK_MAP = 100;
const int BITMASK_LAYER_UI = 101;

#define SPEED 165

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

	void CreateKnight();

	void createLayerUI();

	void update(float dt) override;

	void heroAttack(int);

	void createButtonAttack();


	void createButton_Skill_1();
	void createButton_Skill_2();

	void miniMap();
	
	void HandleMinimap();

	

	void AddKnightRed();

	

	

	CREATE_FUNC(GamePlayScene);
private:
	Size screenSize;
	TMXTiledMap *map, *mapTop;
	Size sizeWall;
	float m_scaleX;
	float m_scaleY;
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

	Vec2 positionWeapons;

	Size mapContentSize;
	Point touchCurrenPositon;

	ScoutTown *newScoutTown;
  
	cocos2d::Animation * animaton;

	std::vector<Knight *> knight;
	Sprite* gameSprite;
	Sprite * gameSpriteAttack;
	CCCallFunc * callBackAttack;
	Vec2 tempTouch;
	bool stateTouchHero = false;
	
	PhysicsBody * bodyA;
	Vec2 tempPositinSprite;
	int count[10] = {0};
	Action* mListAction[10];
	Sprite * mButtonAttack;
	Vec2  mCurrentTouch;
	Hero * hero;
	DelayTime * pause;
	int keep_Press = -1;
	Sprite * dot, *m_miniMap, *map_1;
	Vec2 condinatorBigMap ;
	Vec2 condinatorMiniMap ;
	Sprite * mButtonSkill_1;
	Sprite * mButtonSkill_2;

	Dragon * dragon;


	Bullet * bullet;

	
	

	// Knight
	std::vector<Knight*> m_knightRead;



	std::vector<TownHall *> newHallTown;

	std::vector < Bullet * > m_listBullets;

	std::vector < ScoutTown * > m_listScoutTowns;

	float count_bullet =0;

	float count_attack = 0.0;
	bool shoot = false;
	Point postScountTower;
};

