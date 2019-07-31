#include"GamePlayScene.h"
#include<string.h>
GamePlayScene::GamePlayScene()
{
}

GamePlayScene::~GamePlayScene()
{
}

Scene * GamePlayScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = GamePlayScene::create();

	scene->addChild(layer);
	return scene;
}

bool GamePlayScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	newScoutTown = nullptr;
	newDecorateHouse = nullptr;
	newStoreHouse = nullptr;
	newMainHouse = nullptr;
	//newHallTown = nullptr;


	screenSize = Director::getInstance()->getVisibleSize();
	sizeWall = Vec2(3.0f, 3.0f);




	condinatorMiniMap = Vec2(screenSize.width * 1 / 20, screenSize.height * 7 / 10);


	pause = DelayTime::create(20);
	
	this->setCameraMask((unsigned short)CameraFlag::DEFAULT, true);
	this->setCameraMask((unsigned short)CameraFlag::USER1, true);
	
	// create item
	this->CreateItem();

	//Create Layer for map and camera
	this->createLayer2D();

	//add map
	this->AddMap();




	//code duoc
	hero = new Hero(_layer2D);
	


	dragon = new Dragon(_layer2D);

	dragon->getSprite()->setPosition(1500,2000);

	// add camera
	this->AddCameraUSER1();


	//Add listener
	this->AddListener();

	//Add camera User 2
	this->AddCameraUSER2();

	// add layer 

	this->CreateLayerUI();
	hero->createBloodSprite(_layerUI);

	//Add Knight Red
	this->AddKnightRed();

	//code duoc
	createButtonAttack();
	createButton_Skill_1();
	createButton_Skill_2();

	miniMap();



	this->AddButtonPopUpHero();

	this->AddButtonPopUpHouse();


	this->scheduleUpdate();

	return true;
}

void GamePlayScene::createLayer2D()
{
	auto layer2D = Layer::create();
	this->addChild(layer2D, 0);
	_layer2D = layer2D;

	
}

bool GamePlayScene::OnTouchBegan(Touch * touch, Event * unused_event)
{

	mCurrentTouch.x = touch->getLocation().x;
	mCurrentTouch.y = touch->getLocation().y;

	tempTouch.x = (touch->getLocation().x - screenSize.width / 2);
	tempTouch.y = (touch->getLocation().y - screenSize.height / 2);
	//	gameSprite->runAction(sqe);
	tempTouch.x = camera->getPosition().x + tempTouch.x;
	tempTouch.y = camera->getPosition().y + tempTouch.y;
	
	touchCurrenPositon = touch->getLocation()
		+ camera->getPosition() - Director::getInstance()->getVisibleSize() / 2;
	for (auto k : knight)
	{
		if (k != nullptr && k->GetSelected() == true)
		{
			k->Move(touchCurrenPositon);
		}
	}

	if (hero->getState()) {
	//	hero->getBlood()->reduceBlood(-100);
		hero->handleBloodBar();
	}
	


	return true;
}

void GamePlayScene::OnTouchMove(Touch * touch, Event * unused_event)
{

	Point newPos = touch->getPreviousLocation() - touch->getLocation();

	Vec3 cameraForward;
	Vec3 cameraDownDir;
	Vec3 cameraRightDir;

	//camera->getNodeToWorldTransform().getForwardVector(&cameraForward);
	//cameraForward.normalize();
	//cameraForward.y = 0;

	camera->getNodeToWorldTransform().getDownVector(&cameraDownDir);
	cameraDownDir.normalize();
	cameraDownDir.z = 0;

	camera->getNodeToWorldTransform().getRightVector(&cameraRightDir);
	cameraRightDir.normalize();
	cameraRightDir.z = 0;

	Vec3 cameraPos = camera->getPosition3D();
	cameraPos -= cameraDownDir*newPos.y*0.5f;
	cameraPos += cameraRightDir*newPos.x*0.5f;
	camera->setPosition3D(cameraPos);
	
	//log("touch position : %f, %f", touch->getLocation().x, touch->getLocation().y);
	//log("newPos Position : %f, %f", newPos.x, newPos.y);
	//log("LayerUI Position : %f, %f", _layerUI->getPosition().x, _layerUI->getPosition().y);
	//log("Camera Position: %f, %f", camera->getPosition().x, camera->getPosition().y);
	//log("Layer2D Position : %f, %f", _layer2D->getPosition().x, _layer2D->getPosition().y);

}

void GamePlayScene::OnTouchEnd(Touch * touch, Event * unused_event)
{

}


bool GamePlayScene::onContactBegin(PhysicsContact & contact)

{
	auto spriteA = contact.getShapeA()->getBody();
	auto spriteB = contact.getShapeB()->getBody();

	return true;
}

bool GamePlayScene::onContactPreSolve(PhysicsContact & contact, PhysicsContactPreSolve & solve)
{
	///solve.setRestitution(0);

	return true;

}

void GamePlayScene::AddMap()
{
	map = TMXTiledMap::create("map.tmx");
	map->setAnchorPoint(Vec2(0, 0));
	map->setPosition(this->getPosition());
	_layer2D->addChild(map);

	//get contensize big map
	condinatorBigMap = Vec2(2*map->getContentSize().height, 2*map->getContentSize().width);
	log("condinatorBigMap %f %f", map->getContentSize().height, map->getContentSize().width);
	
	// Map top
	mapTop = TMXTiledMap::create("mapTop.tmx");
	mapTop->setAnchorPoint(Vec2(0, 0));
	mapTop->setPositionY(map->getContentSize().height);
	_layer2D->addChild(mapTop);

	//Map right
	mapRight = TMXTiledMap::create("mapLeft.tmx");
	mapRight->setAnchorPoint(Vec2(0, 0));
	mapRight->setPositionX(map->getContentSize().width);
	_layer2D->addChild(mapRight);

	//Map right top
	mapTopRight = TMXTiledMap::create("mapRightTop.tmx");
	mapTopRight->setAnchorPoint(Vec2(0, 0));
	mapTopRight->setPosition(map->getContentSize().width, map->getContentSize().height);
	_layer2D->addChild(mapTopRight);

	auto sizeMapHeight = Size(10, map->getContentSize().height + mapTop->getContentSize().height);
	auto sizeMapUp = Size(map->getContentSize().width * 2, 10);
	
	// add physic for map left
	auto nodeLeft = Node::create();
	auto physicLeft = PhysicsBody::createBox(sizeMapHeight,
		PHYSICSBODY_MATERIAL_DEFAULT);
	physicLeft->setDynamic(false);
	physicLeft->setCategoryBitmask(1);

	physicLeft->setCollisionBitmask(63);

	nodeLeft->setPhysicsBody(physicLeft);
	nodeLeft->setPosition(map->getPositionX() + 10, sizeMapHeight.height / 2);
	_layer2D->addChild(nodeLeft);


	// add physic for map up

	auto nodeUP = Node::create();
	auto physicUp = PhysicsBody::createBox(sizeMapUp,
		PHYSICSBODY_MATERIAL_DEFAULT);
	physicUp->setDynamic(false);
	physicUp->setCategoryBitmask(1);

	physicUp->setCollisionBitmask(63);

	nodeUP->setPhysicsBody(physicUp);
	nodeUP->setPosition(map->getContentSize().width /2 , sizeMapHeight.height - 5);
	_layer2D->addChild(nodeUP);

	// add physic for map right

	auto nodeRight = Node::create();
	auto physicRight = PhysicsBody::createBox(sizeMapHeight,
		PHYSICSBODY_MATERIAL_DEFAULT);
	physicRight->setDynamic(false);
	physicRight->setCategoryBitmask(1);

	physicRight->setCollisionBitmask(63);

	nodeRight->setPhysicsBody(physicRight);
	nodeRight->setPosition(map->getContentSize().width * 2 - 10, sizeMapHeight.height / 2);
	_layer2D->addChild(nodeRight);

	// add physic for map down

	auto nodeDown = Node::create();
	auto physicDown = PhysicsBody::createBox(sizeMapUp,
		PHYSICSBODY_MATERIAL_DEFAULT);
	physicDown->setDynamic(false);
	physicDown->setCategoryBitmask(1);

	physicDown->setCollisionBitmask(63);

	nodeDown->setPhysicsBody(physicDown);
	nodeDown->setPosition(map->getContentSize().width / 2, map->getPosition().y + 5);
	_layer2D->addChild(nodeDown);
}

void GamePlayScene::AddCameraUSER1()
{
	camera = Camera::create(); 
	camera->setCameraFlag(CameraFlag::USER1);

	auto physicBody = PhysicsBody::createBox(screenSize,
		PHYSICSBODY_MATERIAL_DEFAULT);

	physicBody->setCategoryBitmask(2);
	physicBody->setCollisionBitmask(1);
	//physicBody->setContactTestBitmask(2);

	physicBody->setGravityEnable(false);
	physicBody->setRotationEnable(false);
	physicBody->setDynamic(true); 

	camera->setPhysicsBody(physicBody);
	_layer2D->addChild(camera, 1);	
	_layer2D->setCameraMask((unsigned short)CameraFlag::USER1);
}

void GamePlayScene::AddCameraUSER2()
{	
	cameraUS2 = Camera::create();
	cameraUS2->setCameraMask(4);
	this->addChild(cameraUS2);

}

void GamePlayScene::AddListener()
{
	// add listen touch
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GamePlayScene::OnTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GamePlayScene::OnTouchMove, this);
	listener->onTouchEnded = CC_CALLBACK_2(GamePlayScene::OnTouchEnd, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GamePlayScene::onContactBegin, this);
	contactListener->onContactPreSolve = CC_CALLBACK_1(GamePlayScene::onContactBegin, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}
void GamePlayScene::AddJoystick()
{
	Size s = Director::getInstance()->getWinSize();
	Rect joystickBaseDimensions;
	joystickBaseDimensions = Rect(0, 0, 160.0f, 160.0f);

	Point joystickBasePosition;
	joystickBasePosition = Point(screenSize.width / 9, screenSize.height * 2 / 7);

	joystickBase = new SneakyJoystickSkinnedBase();
	joystickBase->init();
	joystickBase->setPosition(joystickBasePosition);

	joystickBack = Sprite::create("res/joystick-back.png");
	joystick = Sprite::create("res/stick.png");
	joystickBack->setOpacity(100);
	joystick->setOpacity(120);
	joystickBase->setBackgroundSprite(joystickBack);
	joystickBase->setThumbSprite(joystick);

	aJoystick = new SneakyJoystick();
	aJoystick->initWithRect(joystickBaseDimensions);

	aJoystick->autorelease();
	joystickBase->setJoystick(aJoystick);
	joystickBase->setPosition(joystickBasePosition);

	leftJoystick = joystickBase->getJoystick();
	leftJoystick->retain();
	joystickBase->setScale(m_scaleX, m_scaleY);
	_layerUI->addChild(joystickBase, 10);
}

void GamePlayScene::AddHudGoldMessage()
{
	auto PosHudGold = Vec2(screenSize.width / 2, screenSize.height/ 2);
	//HudGold *hudGold = HudGold::createLayer("gold", PosHudGold, Color3B::WHITE, Size(10, 10), Vec2(0.5, 0.5));
	//_layerUI->addChild(hudGold,20);
	//hudGold->setCameraMask(8);
}

void GamePlayScene::AddButtonPopUpHero()
{

	auto button = ui::Button::create("backpack.png", "backpack_press.png");
	button->setTitleText("Hero");
	button->setScale(m_scaleX * 0.3, m_scaleY * 0.3);
	button->setPosition(Vec2(screenSize.width / 1.65, screenSize.height / 9.5));
	button->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			this->AddPopupHero();
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});

	_layerUI->addChild(button, 10);
}

void GamePlayScene::AddButtonPopUpHouse()
{
	auto button = ui::Button::create("ButtonShop.png", "ButtonShop_press.png");
	//button->setTitleText("House");
	button->setScale(m_scaleX * 0.3, m_scaleX * 0.3);
	button->setPosition(Vec2(screenSize.width / 1.5, screenSize.height / 9.5));
	button->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			this->AddPopupHouse();
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	_layerUI->addChild(button, 10);
}

void GamePlayScene::AddSpriteUI()
{
	auto containerForSpriteUI = Node::create();
	auto sprite = Sprite::create("UI.png");

	sprite->setPosition(screenSize / 2);
	m_scaleX = screenSize.width / sprite->getContentSize().width;
	m_scaleY = screenSize.height / sprite->getContentSize().height;
	
	sprite->setScale(m_scaleX,m_scaleY);
	containerForSpriteUI->addChild(sprite);

	_layerUI->addChild(containerForSpriteUI, 10);
}

void GamePlayScene::AddPopupHero()
{
	auto popUpHero = UICustom::PopupHero::createAsConfirmDialogue(_layerUI ,"hero", "", menuItem, [=]() {

	});
	_layerUI->addChild(popUpHero, 10);
}

void GamePlayScene::AddPopupHouse()
{
	auto popupHouse = UICustom::PopupHouse::createAsConfirmDialogue("House", "",
		CC_CALLBACK_0(GamePlayScene::AddEventForPopupMainHouse, this),
		CC_CALLBACK_0(GamePlayScene::AddEventForPopupTownHall, this),
		CC_CALLBACK_0(GamePlayScene::AddEventForPopupStoreHouse, this),
		CC_CALLBACK_0(GamePlayScene::AddEventForPopupScoutTown, this),
		CC_CALLBACK_0(GamePlayScene::AddEventForPopupDecorateHouse, this),
		NULL, NULL
		);
	_layerUI->addChild(popupHouse, 10);
}

 // void GamePlayScene::AddHeroAndDragon()
// {
//	hero = new Hero(_layer2D);
//	dragon = new Dragon(_layer2D);
// }

void GamePlayScene::AddEventForPopupTownHall()
{
		//Add house copy
		auto copyHallTown = Sprite::create("HallTown.png");
		copyHallTown->setOpacity(50);
		_layerUI->addChild(copyHallTown);


		//Add event touch
		auto buildHouseListener = EventListenerTouchOneByOne::create();

		buildHouseListener->onTouchBegan = [=](Touch* _touch, Event* _event) {
			copyHallTown->setPosition(_touch->getLocation());
			return true;
		};

		buildHouseListener->onTouchMoved = [=](Touch* _touch, Event* _event) {
			copyHallTown->setPosition(_touch->getLocation());
		};

		buildHouseListener->onTouchEnded = [=](Touch* _touch, Event* _event) {
			copyHallTown->setVisible(false);

			static auto hallTown = new TownHall(_layer2D, 2);
			hallTown->GetButton()->setPosition(_touch->getLocation()
				+ camera->getPosition() - Director::getInstance()->getVisibleSize() / 2);
				
			//code duoc
			auto dotHallTown = new dotMiniMap(_layerUI, 1);
			//code duoc
			dotHallTown->getSprite()->setPosition((hallTown->GetButton()->getPositionX() / condinatorBigMap.x)*(m_miniMap->getContentSize().height) +
			condinatorMiniMap.x, (hallTown->GetButton()->getPositionY() / condinatorBigMap.y)*(m_miniMap->getContentSize().width) + condinatorMiniMap.y);
			dotHallTown->VisiableDot(true);
			hallTown->GetButton()->setCameraMask(2);
			this->getEventDispatcher()->removeEventListener(buildHouseListener);

			m_position_house.push_back(hallTown->GetButton()->getPosition());
			//hallTown->GetButton()->setTag(m_position_house.size() - 1);
			//hallTown->GetButton()->_ID = m_position_house.size() - 1;
			hallTown->GetButton()->setTag(m_position_house.size() - 1);
			//hallTown->GetButton()->getPhysicsBody()->setGroup(m_position_house.size() - 1);
	
			hallTown->GetButton()->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
				switch (type)
				{
				case cocos2d::ui::Widget::TouchEventType::BEGAN:
				{

					auto popup = UICustom::PopupTownHall::createAsConfirmDialogue("Town hall", "", [&]() {
						auto createKnight = new Knight(_layer2D, TEAM_BLUE);
						createKnight->SetPositionKnight(hallTown->GetButton()->getPosition() + createKnight->GetConTentSize());
						knight.push_back(createKnight);
					});
					_layer2D->addChild(popup);
				}
				break;
				case cocos2d::ui::Widget::TouchEventType::ENDED:
					break;
				default:
					break;
				}

				});
			this->getEventDispatcher()->removeEventListener(buildHouseListener);
			containerHallTown.push_back(hallTown);
		};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(buildHouseListener, this);
}

void GamePlayScene::AddEventForPopupScoutTown()
{
	//Add house copy
	auto copyScoutTown = Sprite::create("ScoutTown2D.png");
	copyScoutTown->setOpacity(50);
	_layerUI->addChild(copyScoutTown);

	//Add event touch
	auto buildHouseListener = EventListenerTouchOneByOne::create();

	buildHouseListener->onTouchBegan = [=](Touch* _touch, Event* _event) {

		copyScoutTown->setPosition(_touch->getLocation());

		return true;
	};

	buildHouseListener->onTouchMoved = [=](Touch* _touch, Event* _event) {
		copyScoutTown->setPosition(_touch->getLocation());
	};

	buildHouseListener->onTouchEnded = [=](Touch* _touch, Event* _event) {
		copyScoutTown->setVisible(false);
		newScoutTown = new ScoutTown(_layer2D, 2);

		
		m_listScoutTowns.push_back(newScoutTown);
		newScoutTown->getSprite()->setPosition(_touch->getLocation()
			+ camera->getPosition() - Director::getInstance()->getVisibleSize() / 2);
		//code duoc
		auto dotScoutTown = new dotMiniMap(_layerUI, 2);
		//code duoc
		dotScoutTown->getSprite()->setPosition((newScoutTown->getSprite()->getPositionX() / condinatorBigMap.x)*(m_miniMap->getContentSize().height) + condinatorMiniMap.x, (newScoutTown->getSprite()->getPositionY() / condinatorBigMap.y)*(m_miniMap->getContentSize().width) + condinatorMiniMap.y);

		dotScoutTown->VisiableDot(true);
		//
		newScoutTown->getSprite()->setCameraMask(2);
		postScountTower = _touch->getLocation() + camera->getPosition() - Director::getInstance()->getVisibleSize() / 2;
		this->getEventDispatcher()->removeEventListener(buildHouseListener);
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(buildHouseListener, this);

}

void GamePlayScene::AddEventForPopupMainHouse()
{
	//Add house copy
	auto copyMainHouse = Sprite::create("HouseMain.png");
	copyMainHouse->setOpacity(50);
	_layerUI->addChild(copyMainHouse);

	//Add event touch
	auto buildHouseListener = EventListenerTouchOneByOne::create();

	buildHouseListener->onTouchBegan = [=](Touch* _touch, Event* _event) {

		copyMainHouse->setPosition(_touch->getLocation());
		return true;
	};

	buildHouseListener->onTouchMoved = [=](Touch* _touch, Event* _event) {
		copyMainHouse->setPosition(_touch->getLocation());
	};

	buildHouseListener->onTouchEnded = [=](Touch* _touch, Event* _event) {
		copyMainHouse->setVisible(false);
		newMainHouse = new MainHouse(_layer2D, 2);
		newMainHouse->GetButton()->setPosition(_touch->getLocation()
			+ camera->getPosition() - Director::getInstance()->getVisibleSize() / 2);
		newMainHouse->GetButton()->setCameraMask(2);
		this->getEventDispatcher()->removeEventListener(buildHouseListener);
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(buildHouseListener, this);
}

void GamePlayScene::AddEventForPopupDecorateHouse()
{
	//Add house copy
	auto copyHouseDecorate = ui::Button::create("HouseDecorate.png");
	copyHouseDecorate->setOpacity(50);
	_layerUI->addChild(copyHouseDecorate);

	//Add event touch
	auto buildHouseListener = EventListenerTouchOneByOne::create();

	buildHouseListener->onTouchBegan = [=](Touch* _touch, Event* _event) {

		copyHouseDecorate->setPosition(_touch->getLocation());
		return true;
	};

	buildHouseListener->onTouchMoved = [=](Touch* _touch, Event* _event) {
		copyHouseDecorate->setPosition(_touch->getLocation());
	};

	buildHouseListener->onTouchEnded = [=](Touch* _touch, Event* _event) {
		copyHouseDecorate->setVisible(false);
		newDecorateHouse = new HouseDecorate(_layer2D, 2);
		newDecorateHouse->GetButton()->setPosition(_touch->getLocation()
			+ camera->getPosition() - Director::getInstance()->getVisibleSize() / 2);
		newDecorateHouse->GetButton()->setCameraMask(2);
		this->getEventDispatcher()->removeEventListener(buildHouseListener);
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(buildHouseListener, this);
}

void GamePlayScene::AddEventForPopupStoreHouse()
{

	//Add house copy
	auto copyStoreHouse = Sprite::create("StoreHouse.png");
	copyStoreHouse->setOpacity(50);
	_layerUI->addChild(copyStoreHouse);

	//Add event touch
	auto buildHouseListener = EventListenerTouchOneByOne::create();

	buildHouseListener->onTouchBegan = [=](Touch* _touch, Event* _event) {

		copyStoreHouse->setPosition(_touch->getLocation());
		return true;
	};

	buildHouseListener->onTouchMoved = [=](Touch* _touch, Event* _event) {
		copyStoreHouse->setPosition(_touch->getLocation());
	};

	buildHouseListener->onTouchEnded = [=](Touch* _touch, Event* _event) {
		copyStoreHouse->setVisible(false);
		static auto storeHouse = new StoreHouse(_layer2D, 2);
		storeHouse->GetButton()->setPosition(_touch->getLocation()
			+ camera->getPosition() - Director::getInstance()->getVisibleSize() / 2);
		storeHouse->GetButton()->setCameraMask(2);
		storeHouse->GetButton()->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
			{

				auto popup = UICustom::PopupShop::createAsConfirmDialogue(_layerUI, "", "", menuItem, [&]() {

				});
				_layer2D->addChild(popup);
			}
			break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				break;
			default:
				break;
			}
		});
		containerStoreHouse.push_back(storeHouse);
		this->getEventDispatcher()->removeEventListener(buildHouseListener);
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(buildHouseListener, this);
}

void GamePlayScene::CreateItem()
{
	Item *itemHp = new Item(ID_HP);
	itemHp->getButton()->retain();
	menuItem.push_back(itemHp);

	Item *itemMp = new Item(ID_MP);
	itemMp->getButton()->retain();
	menuItem.push_back(itemMp);

	Item *itemWepon = new Item(ID_WEAPON);
	itemWepon->getButton()->retain();
	menuItem.push_back(itemWepon);

	Item *itemHelmet = new Item(ID_HELMET);
	itemHelmet->getButton()->retain();
	menuItem.push_back(itemHelmet);

	Item *itemArmor = new Item(ID_ARMOR);
	itemArmor->getButton()->retain();
	menuItem.push_back(itemArmor);
}

void GamePlayScene::CreateKnight()
{

	auto createKnight = new Knight(_layer2D, TEAM_BLUE);
	//knight->getSprite()->setCameraMask(2);

	createKnight->SetPositionKnight(containerHallTown.at(0)->getSprite()->getPosition());
	createKnight->SetSelected(false);
	//createKnight->SetColor(BLUE);
	createKnight->getSprite()->getPhysicsBody()->setGroup(knight.size());
	knight.push_back(createKnight);
}

void GamePlayScene::CreateLayerUI()

{
	_layerUI = Layer::create();
	_layerUI->setPosition(Vec2(2 , 2));
	//log("layerUI contentsize : %f , %f", _layerUI->getContentSize().width, _layerUI->getContentSize().height);
	
	this->addChild(_layerUI, 10);
	_layerUI->setCameraMask((unsigned short)CameraFlag::USER2);

	//Add feature for UI;
	this->AddSpriteUI();
	this->CreateChooseKnight();
	this->AddJoystick();
	this->AddButtonPopUpHero();
	this->AddButtonPopUpHouse();
	this->AddHudGoldMessage();
}

void GamePlayScene::CreateChooseKnight()
{
	auto button = ui::Button::create("itemKnight.png", "itemKnight.png");
	button->setScale(0.5);
	button->setPosition(Vec2(screenSize.width * 0.935, screenSize.height * 0.85));
	button->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			this->CreatePopupChooseKnight();

			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	_layerUI->addChild(button, 10);
}

void GamePlayScene::CreatePopupChooseKnight()
{
	labelChooseKnight = Label::create();
	labelChooseKnight->setString(stringChooseKnight);
	labelSumKnight = Label::create();
	labelSumKnight->setString(std::to_string(knight.size()));

	auto labelSum = Label::createWithTTF("Sum: ", "fonts/arial.ttf", 13);
	auto labelChoose = Label::createWithTTF("Choose: ", "fonts/arial.ttf", 30);
	auto popupChooseKnight = UICustom::PopupChooseKnight::create("Choose knight", "", labelSumKnight, labelSum
		,labelChoose ,labelChooseKnight,
		CC_CALLBACK_0(GamePlayScene::AddToChooseKnight, this),
		CC_CALLBACK_0(GamePlayScene::SubToChooseKnight, this),
		CC_CALLBACK_0(GamePlayScene::ChooseKnight, this)
	);
	_layerUI->addChild(popupChooseKnight);

}

void GamePlayScene::AddToChooseKnight()
{
	int chooseKnight = std::stoi(stringChooseKnight) + 1;
	if (chooseKnight <= knight.size())
	{
		stringChooseKnight = std::to_string(chooseKnight);
		labelChooseKnight->setString(stringChooseKnight);
		for (int i = 0; i < chooseKnight; i++)
		{
			knight.at(i)->SetSelected(true);
		}
	}

}

void GamePlayScene::SubToChooseKnight()
{
	int chooseKnight = std::stoi(stringChooseKnight) - 1;
	if (chooseKnight >= 0)
	{
		stringChooseKnight = std::to_string(chooseKnight);
		labelChooseKnight->setString(stringChooseKnight);
		for (int i = chooseKnight; i < knight.size(); i++)
		{
			knight.at(i)->SetSelected(false);
		}
	}
}
void GamePlayScene::ChooseKnight()
{
}

void GamePlayScene::update(float dt)
{

	if (newScoutTown != nullptr)
	{
		newScoutTown->Update(dt);

	}
	if (newMainHouse != nullptr)
	{
		newMainHouse->Update(dt);
	}
	if (newDecorateHouse != nullptr)
	{
		newDecorateHouse->Update(dt);
	}
	if (containerStoreHouse.size() > 0)
	{
		for (int i = 0; i < containerStoreHouse.size(); i++)
		{
			if (containerStoreHouse.at(i) != nullptr)
			{
				containerStoreHouse.at(i)->Update(dt);
			}
		}
	}
	if (containerHallTown.size() > 0)
	{
		for (int i = 0; i < containerHallTown.size(); i++)
		{
			if (containerHallTown.at(i) != nullptr)
			{
				containerHallTown.at(i)->Update(dt);
			}
		}
	}	

	// Check Knight
	this->MoveAttack(m_knightRed, knight);

	// code duoc
	count_dragon += dt;
	count_dragon_fire += dt;
	if (count_dragon>7) {
		dragon->dragonMove(hero->getDirect());
		dragon->createFire(_layer2D);
		if (count_dragon_fire>7) {
			dragon->dragonFire(hero->getDirect());
			if (abs(dragon->getSprite()->getPositionX() - hero->getSprite()->getPositionX()) < 200 &&
				abs(dragon->getSprite()->getPositionY() - hero->getSprite()->getPositionY()) < 200) {
				hero->getBlood()->reduceBlood(dragon->getDamage()->getDamageNormal());
				hero->handleBloodBar();
				//	dragon->handleBloodBar();
				
			}
			count_dragon_fire = 0;
	}
		count_dragon = 0;
	}

	if (hero->getState()) {
		handleJoystick();
	}


	//dragon->updatePositionloodBar();
	
	joystickBase->updatePositions(dt);


	//	spriteFocus->setPosition(gameSprite->getPosition().x , gameSprite->getPosition().y +50);
	count_attack += dt;
	if (count_attack > 1.0 && hero->getState() == true) {
		heroAttack(hero->getDirect());
		count_attack = 0.0;
	}
	dotHero->VisiableDot(true);
//	dot->setPosition(hero->getPositionHero().x-100, hero->getPositionHero().y+200);
	HandleMinimap();
	count_bullet += dt;
	
	if (count_bullet>0.4 && m_listScoutTowns.size()>0 && m_knightRed.size()>0) {
		for (auto a : m_listScoutTowns) {
			for (auto b: m_knightRed) {
				if (abs(a->getSprite()->getPositionX() - b->getSprite()->getPositionX())<200 &&
					abs(a->getSprite()->getPositionY() - b->getSprite()->getPositionY())<200
					) {
					a->Update(count_bullet, b);

					b->getBlood()->reduceBlood(a->getDamage()->getDamageNormal());
					if (b->getBlood()->isDie()) {
						b->getSprite()->setVisible(false);
						b->getSprite()->setPosition(0,2000);
					}
					a->getBlood()->reduceBlood(b->getDamage()->getDamageNormal());
					if (a->getBlood()->isDie()) {
						a->getSprite()->setVisible(false);
						a->getSprite()->setPosition(2000,0);
					}
				}
			}
			
		}
		
		count_bullet = 0;
	}
	//hero->setBlood(-dt);

	if (hero->getBlood()->getBlood()<10 && hero->getState() == true) {
		hero->diedHero(hero->getDirect());
		hero->setState(false);
		countRebirth = 0;
	}
	countRebirth += dt;
	if (countRebirth >10 && hero->getState()==false) {
		hero->getBlood()->setBlood(1000);
		hero->handleBloodBar();
	
		hero->getSprite()->setPosition(200,200);
		hero->getAttack(1);
		hero->setState(true);
	}
}

void GamePlayScene::heroAttack(int STATE_ATTACK) {
	if (mButtonAttack->getBoundingBox().containsPoint(mCurrentTouch)) {
		hero->getAttack(STATE_ATTACK);
		if (abs(dragon->getSprite()->getPositionX() - hero->getSprite()->getPositionX()) < 200 &&
			abs(dragon->getSprite()->getPositionY() - hero->getSprite()->getPositionY()) < 200) {
			dragon->getBlood()->reduceBlood(hero->getDamage()->getDamageNormal());
			handleDragonVsHero();
		//	dragon->handleBloodBar();
		}

		for (auto b : m_knightRed)
		{
			if (abs(b->getSprite()->getPositionX() - hero->getSprite()->getPositionX()) < 100 &&
				abs(b->getSprite()->getPositionY() - hero->getSprite()->getPositionY()) < 100) {
				b->getBlood()->reduceBlood(hero->getDamage()->getDamageNormal());
		
			}
		}
		mCurrentTouch.x+=100;
	}
	if (mButtonSkill_2->getBoundingBox().containsPoint(mCurrentTouch)) {
		hero->skillAnimation(_layer2D,1);
		if (abs(dragon->getSprite()->getPositionX() - hero->getSprite()->getPositionX()) < 200 &&
			abs(dragon->getSprite()->getPositionY() - hero->getSprite()->getPositionY()) < 200) {
			dragon->getBlood()->reduceBlood(hero->getDamage()->getDamageSkill_1());

			handleDragonVsHero();
			//	dragon->handleBloodBar();
		}
		handleDragonVsHero();

		mCurrentTouch.x += 200;
	}
	if (mButtonSkill_1->getBoundingBox().containsPoint(mCurrentTouch)) {
		hero->skillAnimation(_layer2D, 2);
		if (abs(dragon->getSprite()->getPositionX() - hero->getSprite()->getPositionX()) < 200 &&
			abs(dragon->getSprite()->getPositionY() - hero->getSprite()->getPositionY()) < 200) {
			dragon->getBlood()->reduceBlood(hero->getDamage()->getDamageSkill_2());
			handleDragonVsHero();
			//	dragon->handleBloodBar();
		}
		handleDragonVsHero();
		mCurrentTouch.x += 200;
	}
	
	if (dragon->getBlood()->isDie()==true) {
		dragon->getSprite()->setVisible(false);
		dragon->getSprite()->setPosition(Vec2(2000,0));
	}
}



void GamePlayScene::createButtonAttack()
{
	//code duoc
	mButtonAttack = Sprite::create("attack.png");
	mButtonAttack->setScale(0.5);
	mButtonAttack->setPosition(screenSize.width *0.92  , screenSize.height * 0.18  );
	_layerUI->addChild(mButtonAttack,10);


}

void GamePlayScene::createButton_Skill_1()
{
	mButtonSkill_1 = Sprite::create("skill_1.png");
	mButtonSkill_1->setScale(0.3);
	mButtonSkill_1->setPosition(screenSize.width *0.87, screenSize.height * 0.35);
	_layerUI->addChild(mButtonSkill_1, 10);

}


void GamePlayScene::createButton_Skill_2()
{
	mButtonSkill_2 = Sprite::create("skill_2.png");
	mButtonSkill_2->setScale(0.3);
	mButtonSkill_2->setPosition(screenSize.width *0.82, screenSize.height * 0.18);
	_layerUI->addChild(mButtonSkill_2, 10);

}
void GamePlayScene::miniMap()
{

	m_miniMap = Sprite::create("miniMap.png");
	//Sprite*  minimapSprite = Sprite::create("minimap.png");
	//m_miniMap->setScale(0.7);
	//minimapSprite->setScale(0.3);
	//minimapSprite->setPosition(50*screenSize.width / (2 * 256), 820*screenSize.height  / (2*512));
	m_miniMap->setAnchorPoint(Vec2(0, 0));
	m_miniMap->setPosition(condinatorMiniMap);
	//_layerUI->addChild(minimapSprite,11);
	_layerUI->addChild(m_miniMap, 12);

	map_1 = Sprite::create("map1.png");
	//Sprite*  minimapSprite = Sprite::create("minimap.png");
	//map_1->setScaleX(0.66);
	//map_1->setScaleY(0.65);
	map_1->setAnchorPoint(Vec2(0, 0));
	//minimapSprite->setScale(0.3);
	//minimapSprite->setPosition(50*screenSize.width / (2 * 256), 820*screenSize.height  / (2*512));
	map_1->setPosition(m_miniMap->getPositionX()+10, m_miniMap->getPositionY() + 10);


	//_layerUI->addChild(minimapSprite,11);
	_layerUI->addChild(map_1, 11);

	dotHero = new dotMiniMap(_layerUI, 0);


}

void GamePlayScene::HandleMinimap()
{
	dotHero->getSprite()->setPosition( (hero->getPositionHero().x/condinatorBigMap.x)*(map_1->getContentSize().height) + condinatorMiniMap.x, ( hero->getPositionHero().y / condinatorBigMap.y)*(m_miniMap->getContentSize().width) + condinatorMiniMap.y);
	
}


void GamePlayScene::AddKnightRed()
{
	for (int i = 0; i < 10; i++)
	{

		Knight *knightRed = new Knight(_layer2D, TEAM_RED);
		knightRed->getSprite()->setCameraMask(2);
		//this->getContentSize()
		knightRed->SetPositionKnight((Vec2)mapTop->getContentSize() *2 / 3 + mapTop->getPosition());
		knightRed->getSprite()->getPhysicsBody()->setGroup(i);
		m_knightRed.push_back(knightRed);
		//log("%f %f", _layer2D->getContentSize().width, _layer2D->getContentSize().height);
	}
}

Vec2 GamePlayScene::CheckRangerAttack(std::vector<Knight*> red, std::vector<Knight*> blue)
{
	Point positionKnightRed, positionKnightBlue;
	for (auto knightRed : red)
	{
		positionKnightRed = knightRed->GetPositionKnight();
		for (auto knightBlue : blue)
		{
			positionKnightBlue = knightBlue->GetPositionKnight();
			float _distance = positionKnightRed.distance(positionKnightBlue);
			if (_distance <= RANGER_ATTACK)
			{
				return positionKnightBlue;
				if (knightBlue->GetCurrentDirect() != knightBlue->GetLastDirect()) 
				{
					return Vec2((positionKnightBlue.x + positionKnightRed.x) / 2,
						(positionKnightBlue.y + positionKnightRed.y) / 2);
				}
				return Vec2::ZERO;
			}
		}
	}
	return Vec2::ZERO;
}

void GamePlayScene::MoveAttack(std::vector<Knight*> red, std::vector<Knight*> blue)
{
	if (CheckRangerAttack(red, blue) != Vec2::ZERO)
	{
		Vec2 vec = CheckRangerAttack(red, blue);

		for (auto red : red)
		{
			red->MoveRed(vec);
		}
	}
}

	


//	if (leftJoystick->getVelocity().x > 0) {
//		everboyBody->setVelocity(Vect(200, 0));
//	}
//	if (leftJoystick->getVelocity().x < 0) {
//		everboyBody->setVelocity(Vect(-200, 0));
//	}
//	if (leftJoystick->getVelocity().x == 0) {
//		everboyBody->setVelocity(Vect(0, everboyBody->getWorld()->getGravity().y));
//	}
//	if (jumpBtn->getValue()) {
//		everboyBody->applyImpulse(Vec2(0, 200));
//		everboyBody->setVelocity(Vec2(0, 100));
//	}
//	joystickBase->updatePositions(dt);


void GamePlayScene::handleJoystick()
{
	if (leftJoystick->getVelocity().x > 0.866 && leftJoystick->getVelocity().y > -0.5 && leftJoystick->getVelocity().y < 0.5) {
		if (count[0] == 0) {

			hero->moveR(1, SPEED, 0);
			hero->setDirect(1);

		//	dragon->dragonMove(1);
		}
		count[0]++;
		if (count[0] > 50) {
			count[0] = 0;

			//log("JOYSTIK %f %f", leftJoystick->getVelocity().x, leftJoystick->getVelocity().y);
		}

	}

	if (leftJoystick->getVelocity().x > 0.6 && leftJoystick->getVelocity().x <= 0.8 && leftJoystick->getVelocity().y > 0.5 && leftJoystick->getVelocity().y <= 0.8666) {



		if (count[1] == 0) {
			hero->moveR(2, SPEED, SPEED);
			hero->setDirect(2);
		//	dragon->dragonMove(2);
		}
		count[1]++;
		if (count[1]>50) {
			count[1] = 0;

		}

	}

	if (leftJoystick->getVelocity().y > 0.866 && leftJoystick->getVelocity().x > -0.5 && leftJoystick->getVelocity().x < 0.5) {

		if (count[2] == 0) {


			hero->moveR(3, 0, SPEED);
			hero->setDirect(3);
			//dragon->dragonMove(3);
		}
		count[2]++;
		if (count[2]>50) {
			count[2] = 0;

		}

	}

	if (leftJoystick->getVelocity().x < -0.6 && leftJoystick->getVelocity().x >= -0.8 && leftJoystick->getVelocity().y > 0.5 && leftJoystick->getVelocity().y <= 0.8666) {


		if (count[3] == 0) {
			hero->moveR(4, -SPEED, SPEED);
			hero->setDirect(4);
			//dragon->dragonMove(4);
		}
		count[3]++;
		if (count[3]>50) {
			count[3] = 0;

		}
	}

	if (leftJoystick->getVelocity().x < -0.866 && leftJoystick->getVelocity().y > -0.5 && leftJoystick->getVelocity().y < 0.5) {




		if (count[4] == 0) {
			hero->moveR(5, -SPEED, 0);
			hero->setDirect(5);
		//	dragon->dragonMove(5);
		}
		count[4]++;
		if (count[4]>50) {
			count[4] = 0;
		}

	}

	if (leftJoystick->getVelocity().x <= -0.6 && leftJoystick->getVelocity().x >= -0.8 && leftJoystick->getVelocity().y < -0.5 && leftJoystick->getVelocity().y >= -0.8666) {


		if (count[5] == 0) {
			hero->moveR(6, -SPEED, -SPEED);
			hero->setDirect(6);
		//	dragon->dragonMove(6);
		}
		count[5]++;
		if (count[5]>50) {
			count[5] = 0;

		}

	}


	if (leftJoystick->getVelocity().y < -0.866 && leftJoystick->getVelocity().x > -0.5 && leftJoystick->getVelocity().x < 0.5) {

		if (count[6] == 0) {


			hero->moveR(7, 0, -SPEED);
			hero->setDirect(7);
		//	dragon->dragonMove(7);
		}
		count[6]++;
		if (count[6]>50) {
			count[6] = 0;
		}
	}


	if (leftJoystick->getVelocity().x >= 0.6 && leftJoystick->getVelocity().x <= 0.8 && leftJoystick->getVelocity().y < -0.5 && leftJoystick->getVelocity().y >= -0.8666) {

		if (count[7] == 0) {

			hero->moveR(0, SPEED, -SPEED);
			hero->setDirect(0);
		}
		count[7]++;
		if (count[7]>50) {
			count[7] = 0;

		}
	}

	if (leftJoystick->getVelocity().x == 0.0 && leftJoystick->getVelocity().y == 0.0) {
		hero->getSprite()->stopAllActionsByTag(0);
		for (int i = 0; i < 8; i++) {
			count[i] = 0;
		}
	}

}

void GamePlayScene::handleDragonVsHero()
{
	if (dragon->getBlood()->isDie() == true) { return; }
	switch (hero->getDirect())
	{
	case 0:
		dragon->dragonMove(4);
		dragon->dragonFire(4);
		break;
	case 1:
		dragon->dragonMove(5);
		dragon->dragonFire(5);
		break;
	case 2:
		dragon->dragonMove(6);
		dragon->dragonFire(6);
		break;
	case 3:
		dragon->dragonMove(7);
		dragon->dragonFire(7);
		break;
	case 4:
		dragon->dragonMove(0);
		dragon->dragonFire(7);
		break;
	case 5:
		dragon->dragonMove(1);
		dragon->dragonFire(7);
		break;
	case 6:
		dragon->dragonMove(2);
		dragon->dragonFire(7);
		break;
	case 7:
		dragon->dragonMove(3);
		dragon->dragonFire(7);
		break;
	default:
		break;
	}
}



	




