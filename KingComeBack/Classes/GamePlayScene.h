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
#include "HouseDragon.h"


#include "Bullet.h"

#include "dotMiniMap.h"



USING_NS_CC;
const float wigthWall = 1;
const float heightWall = 1;

const int BITMASK_MAP = 100;
const int BITMASK_LAYER_UI = 101;


#define SPEED 100




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
	void AddButtonAttack();
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
	void AddGold();

	void update(float dt) override;

	void heroAttack(int, int);


	void miniMap();
	
	void HandleMinimap();

	void AddKnightRed();
	
	//knight Attack
	Vec2 CheckRangerAttack(std::vector<Knight*> red, std::vector<Knight*> blue);
	void MoveAttack(std::vector<Knight*> red, std::vector<Knight*> blue);
	void ChekAttackKnight(std::vector<Knight*> red, std::vector<Knight*> blue, Dragon* dra, float dt);
	void ReduceBloodKnight(Knight* red, Knight* blue);
	void RemoveKnightRed(Knight* red);
	void RemoveKnightBlue(Knight* blue);

	void RemoveKnightRedMove(Knight* k);
	//bool CheckAttack(std::vector<Knight*> red, std::vector<Knight*> blue);

	//-- Dragon --
	void DragonCheck(std::vector<ScoutTown*>, std::vector<TownHall*>,std::vector<StoreHouse *>, 
		std::vector<Knight *>, Hero*);
	void DragonAttack(Human* hm, float dt);
	void RedurceBloodBlueTeam(std::vector<ScoutTown*>, std::vector<TownHall*>, 
		std::vector<StoreHouse *>, std::vector<Knight *>, Hero*, Vec2);
	void AddHouseDragon();

	//------Add Knight Red Move-----
	Human* KnightRedMoveCheck(std::vector<ScoutTown*>, std::vector<TownHall*>, std::vector<StoreHouse *>,
		std::vector<Knight *>, Hero*);
	void KnightRedMoveAttack(float dt);
	void KnightRedMoveAttackHuman(Human *hm, float dt);

	//-------Knight Blue Attack-------
	void KnightBlueCheckAttack(Dragon * dra, std::vector<Knight*> red, std::vector<Knight*> redMove, float dt);

	//-------Scout Town Attack--------------
	void ScoutAttack(std::vector<ScoutTown*> m_listScoutTowns, std::vector<Knight*> m_knightRed, 
		std::vector<Knight*> m_knightRedMove, float count_bullet);

	//----------------------------------
	void handleJoystick();

	void handleDragonVsScout();


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

	static int m_gold;
	static const int indexMap = 1;
	static const int indexCamera = 4;
	static const int indexJoystick = 3;
	static const int indexLayerUI = 2;
	std::string stringChooseKnight = "0";
	Label *labelChooseKnight;
	Label *labelSumKnight;
	Label* labelGold;
	Vec2 positionWeapons;

	Size mapContentSize;
	Point touchCurrenPositon;

	// house
	ScoutTown *newScoutTown;
	MainHouse *newMainHouse;
	HouseDecorate *newDecorateHouse;
	StoreHouse *newStoreHouse;

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
	int tagButton = 1;

	Dragon * dragon = nullptr;


	Bullet * bullet;

	void handleDragonVsHero();
	

	//-------Knight-------------------
	std::vector<Knight*> m_knightRed;
	bool m_checkKnight = KNIGHT_STATE_FIND;
	Human * m_humanKnigthBlueAttack;
	
	// Atribute of hero
	MenuItemLabel *menuLabelHp;
	MenuItemLabel *menuLabelDamage;
	MenuItemLabel *menuLabelArmor;
	MenuItemLabel *menuLabelStrength;

	std::vector < Bullet * > m_listBullets;
	std::vector < ScoutTown * > m_listScoutTowns;
	float count_bullet =0;
	float count_attack = 0.0, count_dragon =0.0, count_dragon_fire=0.0 ;
	bool shoot = false;
	Point postScountTower;
	float countBlood, countRebirth =0.0;

	dotMiniMap * dotHero;

	std::vector<HouseDecorate *> containerDecorateHouse;
	std::vector<TownHall *> containerHallTown;
	std::vector<StoreHouse *> containerStoreHouse;
	std::vector<Knight *> knight;
	std::vector<Item *> menuItem;
	std::vector<Item *> menuItemShop;

	float countSkill_1 =0.0, countSkill_2 =0.0, countNormal = 0.0;

	Vector<MenuItemLabel *> menuItemLabelAtribute;


	//---dragon----
	bool m_dragonState = DRAGON_STATE_FIND;
	Human *m_humanDragonAttack = nullptr;
	bool m_stateReduce = false;
	Vec2 m_vecPosition = Vec2::ZERO;
	HouseDragon* m_houseDragon;

	//--- Add Knight Red Move----
	std::vector<Knight*> m_knightRedMove;
	bool m_stateKnightRedMove = DRAGON_STATE_FIND;
	Human *m_humanKnightRedAttack = nullptr;
};

