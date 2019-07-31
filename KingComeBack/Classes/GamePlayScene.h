#pragma once
#include"cocos2d.h"
#include"SneakyJoystickSkinnedBase.h"
#include"ui/CocosGUI.h"
#include"Popup.h"
#include"TownHall.h"
#include"ScoutTown.h"
#include"MainHouse.h"
#include"HouseDecorate.h"
#include"StoreHouse.h"
#include "Hero.h"
#include "Defines.h"
#include "Dragon.h"
#include "Knight.h"
#include"HudGold.h"


#include "Bullet.h"

#include "dotMiniMap.h"



USING_NS_CC;
const float wigthWall = 1;
const float heightWall = 1;

const int BITMASK_MAP = 100;
const int BITMASK_LAYER_UI = 101;


#define SPEED 65




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

	bool onContactBegin(PhysicsContact &contact);
	bool onContactPreSolve(PhysicsContact& contact,
		PhysicsContactPreSolve& solve);


	void AddMap();
	void AddCameraUSER1();
	void AddCameraUSER2();
	void AddListener();
	void AddJoystick();
	void AddHudGoldMessage();
	void AddButtonPopUpHero();
	void AddButtonPopUpHouse();
	void AddSpriteUI();
	void AddPopupHero();
	//void AddListenPopupHero();
	void AddPopupHouse();

//	void AddHeroAndDragon();

	void AddEventForPopupTownHall();
	void AddEventForPopupScoutTown();
	void AddEventForPopupMainHouse();
	void AddEventForPopupDecorateHouse();
	void AddEventForPopupStoreHouse();

	void CreateItem();
	void CreateKnight();

	void CreateLayerUI();
	void CreateChooseKnight();
	void CreatePopupChooseKnight();
	void AddToChooseKnight();
	void SubToChooseKnight();
	void ChooseKnight();

	void update(float dt) override;

	void heroAttack(int);

	void createButtonAttack();


	void createButton_Skill_1();
	void createButton_Skill_2();

	void miniMap();
	
	void HandleMinimap();

	void AddKnightRed();
	
	//knight Attack
	Vec2 CheckRangerAttack(std::vector<Knight*> red, std::vector<Knight*> blue);
	void MoveAttack(std::vector<Knight*> red, std::vector<Knight*> blue);
	//bool CheckAttack(std::vector<Knight*> red, std::vector<Knight*> blue);



	void handleJoystick();


	CREATE_FUNC(GamePlayScene);
private:
	Size screenSize;
	TMXTiledMap *map, *mapTop, *mapRight, *mapTopRight;
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
	std::string stringChooseKnight = "0";
	Label *labelChooseKnight;
	Label *labelSumKnight;

	Vec2 positionWeapons;

	Size mapContentSize;
	Point touchCurrenPositon;

	// house
	ScoutTown *newScoutTown;
	MainHouse *newMainHouse;
	HouseDecorate *newDecorateHouse;
	StoreHouse *newStoreHouse;
	std::vector<Vec2> m_position_house;

	cocos2d::Animation * animaton;


	Sprite* gameSprite;
	Sprite * gameSpriteAttack;
	//CCCallFunc * callBackAttack;
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

	void handleDragonVsHero();
	

	// Knight
	std::vector<Knight*> m_knightRed;
	bool m_checkKnight = false;



	std::vector < Bullet * > m_listBullets;

	std::vector < ScoutTown * > m_listScoutTowns;

	float count_bullet =0;

	float count_attack = 0.0, count_dragon =0.0, count_dragon_fire=0.0 ;
	bool shoot = false;
	Point postScountTower;
	float countBlood, countRebirth =0.0;

	dotMiniMap * dotHero;

	std::vector<TownHall *> containerHallTown;
	std::vector<Knight *> knight;
	std::vector<Item *> menuItem;
};

