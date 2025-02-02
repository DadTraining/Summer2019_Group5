#include "GamePlayScene.h"
#include <string.h>

int GamePlayScene::m_gold = 10000;

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

	menuLabelHp = nullptr;
	menuLabelDamage = nullptr;
	menuLabelArmor = nullptr;
	menuLabelStrength = nullptr;
	//newHallTown = nullptr;

	screenSize = Director::getInstance()->getVisibleSize();
	sizeWall = Vec2(3.0f, 3.0f);

	condinatorMiniMap = Vec2(screenSize.width * 1 / 20, screenSize.height * 7 / 10);

	pause = DelayTime::create(20);
	

	this->setCameraMask((unsigned short)CameraFlag::USER1, true);
	
	// create item
	this->CreateItem();

	//Create Layer for map and camera
	this->createLayer2D();

	//add map
	this->AddMap();


	//code duoc
	hero = new Hero(_layer2D);

	

	AddHouseDragon();

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
	//createButtonAttack();
	AddButtonAttack();
//	createButton_Skill_1();
//	createButton_Skill_2();


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

	//mCurrentTouch.x = touch->getLocation().x;
	//mCurrentTouch.y = touch->getLocation().y;

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
	//	hero->handleBloodBar();
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

	auto mapPhysicLayer = map->getLayer("Water");
	map->setAnchorPoint(Vec2(0, 0));
	map->setPosition(this->getPosition());
	Size layerSize = mapPhysicLayer->getLayerSize();
	for (int i = 0; i < layerSize.width; i++)
	{
		for (int j = 0; j < layerSize.height; j++)
		{
			auto tileSet = mapPhysicLayer->getTileAt(Vec2(i, j));
			if (tileSet != NULL)
			{
				auto physics = PhysicsBody::createBox(tileSet->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
				physics->setCategoryBitmask(1);
				physics->setCollisionBitmask(60);
				physics->setDynamic(false);
				tileSet->setPhysicsBody(physics);
				tileSet->setCameraMask(2);
			}
		}
	}
	_layer2D->addChild(map);

	//get contensize big map



	// Map top
	mapTop = TMXTiledMap::create("mapTop.tmx");
	auto mapTopPhysicLayer = mapTop->getLayer("water");
	mapTop->setAnchorPoint(Vec2(0, 0));
	mapTop->setPositionY(mapTop->getContentSize().height);
	Size layerSizeTop = mapTopPhysicLayer->getLayerSize();
	for (int i = 0; i < layerSizeTop.width; i++)
	{
		for (int j = 0; j < layerSizeTop.height; j++)
		{
			auto tileSet = mapTopPhysicLayer->getTileAt(Vec2(i, j));
			if (tileSet != NULL)
			{
				auto physics = PhysicsBody::createBox(tileSet->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
				physics->setCategoryBitmask(1);
				physics->setCollisionBitmask(60);
				physics->setDynamic(false);
				tileSet->setPhysicsBody(physics);
				tileSet->setCameraMask(2);
			}
		} 
	}

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
	//physicLeft->getShape(0)->setRestitution()
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
	this->addChild(camera, 1);	
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
	_layerUI->addChild(joystickBase);
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

	_layerUI->addChild(button, 1);
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
	_layerUI->addChild(button, 1);
}

void GamePlayScene::AddButtonAttack()
{
	auto button = ui::Button::create("attack.png", "attack.png");
	//button->setTitleText("Hero");
	button->setScale(m_scaleX * 0.3, m_scaleX * 0.3);
	button->setPosition(Vec2(screenSize.width *0.92, screenSize.height * 0.18));
//	button->setPosition(Vec2(screenSize.width / 1.5, screenSize.height / 9.5));
	button->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			//this->AddPopupHouse();
			if ( hero->getState() == true && countNormal >1.0) {
				heroAttack(hero->getDirect(), 0);
				countNormal = 0.0;
			}	
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	_layerUI->addChild(button);

	auto button1 = ui::Button::create("skill_1.png", "skill_1.png");
	//button->setTitleText("Hero");
	button1->setScale(m_scaleX * 0.3, m_scaleX * 0.3);
	button1->setPosition(Vec2(screenSize.width *0.87, screenSize.height * 0.35));
	//	button->setPosition(Vec2(screenSize.width / 1.5, screenSize.height / 9.5));
	button1->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			//this->AddPopupHouse();
			if (countSkill_1 > 4.0 && hero->getState() == true) {
				heroAttack(hero->getDirect(), 1);
				countSkill_1 = 0.0;

			}
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	_layerUI->addChild(button1);

	auto button2 = ui::Button::create("skill_2.png", "skill_2.png");
	//button->setTitleText("Hero");
	button2->setScale(m_scaleX * 0.3, m_scaleX * 0.3);
	button2->setPosition(Vec2(screenSize.width *0.82, screenSize.height * 0.18));
	//	button->setPosition(Vec2(screenSize.width / 1.5, screenSize.height / 9.5));
	button2->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			//this->AddPopupHouse();
			if (countSkill_2 > 6.0 && hero->getState() == true) {
				heroAttack(hero->getDirect(), 2);
				countSkill_2 = 0.0;
			}
			
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	_layerUI->addChild(button2);
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

	_layerUI->addChild(containerForSpriteUI);
}

void GamePlayScene::AddPopupHero()
{
	auto labelHp = Label::createWithTTF(std::to_string((int)hero->GetMaxBlood()), "fonts/arial.ttf", 15);
	auto labelDamage = Label::createWithTTF(std::to_string((int)hero->getDamage()->getDamageNormal()), "fonts/arial.ttf", 15);
	auto labelArmor = Label::createWithTTF(std::to_string((int)hero->GetAmor()), "fonts/arial.ttf", 15);
	auto labelStrength = Label::createWithTTF(std::to_string((int)hero->getStrength()), "fonts/arial.ttf", 15);

	menuLabelHp = MenuItemLabel::create(labelHp);
	menuLabelHp->retain();
	menuLabelDamage = MenuItemLabel::create(labelDamage);
	menuLabelDamage->retain();
	menuLabelArmor = MenuItemLabel::create(labelArmor);
	menuLabelArmor->retain();
	menuLabelStrength = MenuItemLabel::create(labelStrength);
	menuLabelStrength->retain();
	auto popUpHero = UICustom::PopupHero::createAsConfirmDialogue("", "", menuItem, NULL, menuLabelHp,
		menuLabelDamage, menuLabelArmor, menuLabelStrength);
	_layerUI->addChild(popUpHero, 1);
}

void GamePlayScene::AddPopupHouse()
{
	auto popupHouse = UICustom::PopupHouse::createAsConfirmDialogue("", "",
		CC_CALLBACK_0(GamePlayScene::AddEventForPopupMainHouse, this),
		CC_CALLBACK_0(GamePlayScene::AddEventForPopupTownHall, this),
		CC_CALLBACK_0(GamePlayScene::AddEventForPopupStoreHouse, this),
		CC_CALLBACK_0(GamePlayScene::AddEventForPopupScoutTown, this),
		CC_CALLBACK_0(GamePlayScene::AddEventForPopupDecorateHouse, this),
		NULL, NULL
		);
	_layerUI->addChild(popupHouse, 1);
}

void GamePlayScene::AddEventForPopupTownHall()
{
	if (m_gold >= 2000)
	{
		m_gold -= 2000;
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

			copyHallTown->removeFromParentAndCleanup(true);

			auto hallTown = new TownHall(_layer2D, TEAM_BLUE);
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
			hallTown->GetButton()->setTag(tagButton);
			hallTown->GetButton()->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
				switch (type)
				{
				case cocos2d::ui::Widget::TouchEventType::BEGAN:
				{
					auto button = dynamic_cast<ui::Button *>(sender);


					auto popup = UICustom::PopupTownHall::createAsConfirmDialogue("", "", [&]() {
						if (knight.size() <= 20 && m_gold >= 1000)
						{
							m_gold -= 1000;
							auto createKnight = new Knight(_layer2D, TEAM_BLUE);
							createKnight->SetPositionKnight(containerHallTown.at(0)->GetButton()->getPosition() - createKnight->GetConTentSize() * 2 + Vec2(rand() % (10 - 4) + 5, (rand() % (10 - 4) + 5)));
							knight.push_back(createKnight);
						}
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

}

void GamePlayScene::AddEventForPopupScoutTown()
{
	if (m_gold >= 500)
	{
		m_gold -= 500;
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
		newScoutTown = new ScoutTown(_layer2D, TEAM_BLUE);




			m_listScoutTowns.push_back(newScoutTown);
			newScoutTown->getSprite()->setPosition(_touch->getLocation()
				+ camera->getPosition() - Director::getInstance()->getVisibleSize() / 2);
			//code duoc
			auto dotScoutTown = new dotMiniMap(_layerUI, 2);
			newScoutTown->setDotMiniMap(dotScoutTown);
			//d = dotScoutTown;
			//code duoc
			newScoutTown->getDotMiniMap()->getSprite()->setPosition((newScoutTown->getSprite()->getPositionX() / condinatorBigMap.x)*(m_miniMap->getContentSize().height) + condinatorMiniMap.x, (newScoutTown->getSprite()->getPositionY() / condinatorBigMap.y)*(m_miniMap->getContentSize().width) + condinatorMiniMap.y);

			newScoutTown->getDotMiniMap()->getSprite()->setVisible(true);
			//
			newScoutTown->getSprite()->setCameraMask(2);
			postScountTower = _touch->getLocation() + camera->getPosition() - Director::getInstance()->getVisibleSize() / 2;
			this->getEventDispatcher()->removeEventListener(buildHouseListener);
		};
		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(buildHouseListener, this);

	}

}

void GamePlayScene::AddEventForPopupMainHouse()
{
	if (m_gold >= 5000)
	{
		m_gold -= 5000;
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
}

void GamePlayScene::AddEventForPopupDecorateHouse()
{

	if (m_gold >= 1000)
	{
		m_gold -= 1000;
		//Add house copy
		auto copyHouseDecorate = Sprite::create("gold_mine.png");
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
			auto decorateHouse = new HouseDecorate(_layer2D, 2);
			decorateHouse->GetButton()->setPosition(_touch->getLocation()
				+ camera->getPosition() - Director::getInstance()->getVisibleSize() / 2);
			decorateHouse->GetButton()->setCameraMask(2);
			this->getEventDispatcher()->removeEventListener(buildHouseListener);
			containerDecorateHouse.push_back(decorateHouse);
		};
		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(buildHouseListener, this);
	}

}

void GamePlayScene::AddEventForPopupStoreHouse()
{
	if (m_gold >= 1500)
	{
		m_gold -= 1500;
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
			auto storeHouse = new StoreHouse(_layer2D, 2);
			storeHouse->GetButton()->setPosition(_touch->getLocation()
				+ camera->getPosition() - Director::getInstance()->getVisibleSize() / 2);
			storeHouse->GetButton()->setCameraMask(2);
			storeHouse->GetButton()->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
				switch (type)
				{
				case cocos2d::ui::Widget::TouchEventType::BEGAN:
				{
					auto popup = UICustom::PopupShop::createAsConfirmDialogue(m_gold, "", "", menuItem, menuItemShop, [&]() {

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
	
}

void GamePlayScene::CreateItem()
{

	Item *itemHp = new Item(ID_HP, ID_STATE_HOME);
	itemHp->getButton()->retain();
	menuItem.push_back(itemHp);

	//Item *itemMp = new Item(ID_MP, ID_STATE_HOME);
	//itemMp->getButton()->retain();
	//menuItem.push_back(itemMp);


	// item shop
	Item *itemHpShop = new Item(ID_HP, ID_STATE_SHOP);
	itemHpShop->getButton()->retain();
	itemHpShop->getButton()->setTitleText("100$");
	menuItemShop.push_back(itemHpShop);

	Item *itemWeponShop = new Item(ID_WEAPON, ID_STATE_SHOP);
	itemWeponShop->getButton()->retain();
	itemWeponShop->getButton()->setTitleText("2000$");
	menuItemShop.push_back(itemWeponShop);

	Item *itemHelmetShop = new Item(ID_HELMET, ID_STATE_SHOP);
	itemHelmetShop->getButton()->retain();
	itemHelmetShop->getButton()->setTitleText("1000$");
	menuItemShop.push_back(itemHelmetShop);

	Item *itemArmorShop = new Item(ID_ARMOR, ID_STATE_SHOP);
	itemArmorShop->getButton()->retain();
	itemArmorShop->getButton()->setTitleText("700$");
	menuItemShop.push_back(itemArmorShop);
	 
	Item *itemShieldShop = new Item(ID_SHIELD, ID_STATE_SHOP);
	itemShieldShop->getButton()->retain();
	itemShieldShop->getButton()->setTitleText("1500$");
	menuItemShop.push_back(itemShieldShop);

	// upg item
	Item *itemUpgWeponShop = new Item(ID_UPG_WEAPON, ID_STATE_SHOP);
	itemUpgWeponShop->getButton()->retain();
	itemUpgWeponShop->getButton()->setTitleText("4000$");
	menuItemShop.push_back(itemUpgWeponShop);

	Item *itemUpgHelmetShop = new Item(ID_UPG_HELMET, ID_STATE_SHOP);
	itemUpgHelmetShop->getButton()->retain();
	itemUpgHelmetShop->getButton()->setTitleText("2000$");
	menuItemShop.push_back(itemUpgHelmetShop);

	Item *itemUpgArmorShop = new Item(ID_UPG_ARMOR, ID_STATE_SHOP);
	itemUpgArmorShop->getButton()->retain();
	itemUpgArmorShop->getButton()->setTitleText("1500$");
	menuItemShop.push_back(itemUpgArmorShop);

	Item *itemUpgShieldShop = new Item(ID_UPG_SHIELD, ID_STATE_SHOP);
	itemUpgShieldShop->getButton()->retain();
	itemUpgShieldShop->getButton()->setTitleText("3000$");
	menuItemShop.push_back(itemUpgShieldShop);
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
	this->AddGold();
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
	_layerUI->addChild(button, 1);
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
		NULL
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

void GamePlayScene::AddGold()

{
	auto spriteGold = Sprite::create("Item/coin.png");
	spriteGold->setPosition(Vec2(screenSize.width / 2.5, screenSize.height - spriteGold->getContentSize().height / 2));
	_layerUI->addChild(spriteGold, 2);
	
	labelGold = Label::createWithTTF(std::to_string(m_gold), "fonts/MarkerFelt.ttf", 18);
	labelGold->setPosition(spriteGold->getPosition().x + spriteGold->getContentSize().width, spriteGold->getPosition().y);
	_layerUI->addChild(labelGold, 2);
}

void GamePlayScene::update(float dt)
{

	// Remove Knight Death
	for (auto k : knight)
	{
		if (k->GetBlood() <= 0)
		{
			k->SetSelected(false);
			RemoveKnightBlue(k);
			break;
		}
	}

	if (!m_knightRed.empty())
	{
		for (auto k : m_knightRed)
		{
			if (k->GetBlood() <= 0)
			{
				RemoveKnightRed(k);
				break;
			}
		}
	}
	if (!m_knightRedMove.empty())
	{
		for (auto k : m_knightRedMove)
		{
			if (k->GetBlood() <= 0)
			{
				RemoveKnightRedMove(k);
				break;
			}
		}
	}

	if (m_houseDragon->GetBlood() < m_houseDragon->GetMaxBlood())
	{
		if (dragon == nullptr)
		{
			dragon = new Dragon(_layer2D, TEAM_RED);
			dragon->getSprite()->setPosition(m_houseDragon->GetPosition());
		}
		
	}

	labelGold->setString(std::to_string(m_gold));

	countSkill_1 += dt;
	countSkill_2 += dt;
	countNormal += dt;
	if (newScoutTown != nullptr)
	{
		newScoutTown->Update(dt);
	}
	if (newMainHouse != nullptr)
	{
		newMainHouse->Update(dt);
	}
	if (containerDecorateHouse.size() > 0)
	{
		for (int i = 0; i < containerDecorateHouse.size(); i++)
		{
			if (containerDecorateHouse.at(i) != nullptr)
			{
				containerDecorateHouse.at(i)->Update(dt);
				m_gold++;
				labelGold->setString(std::to_string(m_gold));
			}
		}
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
	for (int i = 0; i < menuItem.size(); i++)
	{
		if (menuItem.at(i)->GetId() == ID_HP)
		{
			if (menuItem.at(i)->GetState() == ID_STATE_EQUIPMENT);
			{
				hero->getBlood()->setBlood(menuItem.at(i)->getHp());
			}
		}
		if (menuLabelHp != nullptr && menuItem.at(i)->GetState() == ID_STATE_EQUIPMENT)
		{
			if (menuItem.at(i)->GetId() == ID_WEAPON)
			{
				menuLabelDamage->setString(std::to_string((int)hero->getDamage()->getDamageNormal() + (int)menuItem.at(i)->getDame()));
				//menuLabelStrength->setString(std::to_string((int)hero->getStrength() + (int)menuItem.at(i)->getStrength()));
		
				hero->SetDame((int)hero->getDamage()->getDamageNormal() + (int)menuItem.at(i)->getDame());
				hero->setStrength((int)hero->getStrength() + (int)menuItem.at(i)->getStrength());

			}
			else if (menuItem.at(i)->GetId() == ID_HELMET)
			{
				menuLabelHp->setString(std::to_string((int)hero->GetMaxBlood() + (int)menuItem.at(i)->getHp()));

				hero->SetMaxBlood((int)hero->GetMaxBlood() + (int)menuItem.at(i)->getHp());

			}
			else if (menuItem.at(i)->GetId() == ID_ARMOR)
			{
				menuLabelArmor->setString(std::to_string((int)hero->GetAmor() + (int)menuItem.at(i)->getArmor()));
				hero->SetAmor((int)hero->GetAmor() + (int)menuItem.at(i)->getArmor());
			}
			else if (menuItem.at(i)->GetId() == ID_SHIELD)
			{
				menuLabelArmor->setString(std::to_string((int)hero->GetAmor() + (int)menuItem.at(i)->getArmor()));
				hero->SetAmor((int)hero->GetAmor() + (int)menuItem.at(i)->getArmor());
			}
			else if (menuItem.at(i)->GetId() == ID_UPG_WEAPON)
			{
				menuLabelDamage->setString(std::to_string((int)hero->getDamage()->getDamageNormal() + (int)menuItem.at(i)->getDame()));
				menuLabelStrength->setString(std::to_string((int)hero->getStrength() + (int)menuItem.at(i)->getStrength()));

				hero->SetDame((int)hero->getDamage()->getDamageNormal() + (int)menuItem.at(i)->getDame());
				hero->setStrength((int)hero->getStrength() + (int)menuItem.at(i)->getStrength());
			}
			else if (menuItem.at(i)->GetId() == ID_UPG_HELMET)
			{
				menuLabelHp->setString(std::to_string((int)hero->GetMaxBlood() + (int)menuItem.at(i)->getHp()));

				hero->SetMaxBlood((int)hero->GetMaxBlood() + (int)menuItem.at(i)->getHp());
			}
			else if (menuItem.at(i)->GetId() == ID_UPG_ARMOR)
			{
				menuLabelArmor->setString(std::to_string((int)hero->GetAmor() + (int)menuItem.at(i)->getArmor()));

				hero->SetAmor((int)hero->GetAmor() + (int)menuItem.at(i)->getArmor());
			}
			else if (menuItem.at(i)->GetId() == ID_UPG_SHIELD)
			{
				menuLabelArmor->setString(std::to_string((int)hero->GetAmor() + (int)menuItem.at(i)->getArmor()));

				hero->SetAmor((int)hero->GetAmor() + (int)menuItem.at(i)->getArmor());
			}
		}
		if (menuLabelHp != nullptr && menuItem.at(i)->GetState() == ID_STATE_HOME)
		{
			if (menuItem.at(i)->GetId() == ID_WEAPON || menuItem.at(i)->GetId() == ID_UPG_WEAPON)
			{
				menuLabelDamage->setString(std::to_string((int)hero->getDamage()->getDamageNormal()));
				menuLabelStrength->setString(std::to_string((int)hero->getStrength()));

				hero->SetDame((int)hero->getDamage()->getDamageNormal());
				hero->setStrength((int)hero->getStrength());
			}
			else if (menuItem.at(i)->GetId() == ID_HELMET || menuItem.at(i)->GetId() == ID_UPG_HELMET)
			{
				menuLabelHp->setString(std::to_string((int)hero->getBlood()->getBlood()));

				hero->SetMaxBlood((int)hero->GetMaxBlood());
			}
			else if (menuItem.at(i)->GetId() == ID_ARMOR || menuItem.at(i)->GetId() == ID_UPG_ARMOR)
			{
				menuLabelArmor->setString(std::to_string((int)hero->GetAmor()));
				hero->SetAmor((int)hero->GetAmor());

			}
			else if (menuItem.at(i)->GetId() == ID_SHIELD || menuItem.at(i)->GetId() == ID_UPG_SHIELD)
			{
				menuLabelHp->setString(std::to_string((int)hero->GetAmor()));
				hero->SetAmor((int)hero->GetAmor());

			}

		}
	}

	// Check Knight
	//this->RemoveKnight(m_knightRed, knight);

	this->MoveAttack(m_knightRed, knight);


	labelGold->setString(std::to_string(m_gold));



	this->ChekAttackKnight(m_knightRed, knight, dragon, dt);


	if (hero->getState()) {
		handleJoystick();
	}
	//dragon->updatePositionloodBar();
	
	joystickBase->updatePositions(dt);


	//	spriteFocus->setPosition(gameSprite->getPosition().x , gameSprite->getPosition().y +50);
	count_attack += dt;
	if (count_attack > 1.0 && hero->getState() == true) {
		//heroAttack(hero->getDirect());
		count_attack = 0.0;
	}
	dotHero->VisiableDot(true);
//	dot->setPosition(hero->getPositionHero().x-100, hero->getPositionHero().y+200);
	HandleMinimap();
	
	//-----Scout Town Attack--------------
	ScoutAttack(m_listScoutTowns, m_knightRed, m_knightRedMove, dt);

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
	
		hero->getSprite()->setPosition(512,256);
		hero->getAttack(1);
		hero->setState(true);
	}

	//Dragon Check Ranger

	static float count_dragonAttack = 1.5;
	if (dragon)
	{
		if (m_dragonState == DRAGON_STATE_FIND)
		{
			DragonCheck(m_listScoutTowns, containerHallTown, containerStoreHouse, knight, hero);
		}
		if (m_humanDragonAttack && count_dragonAttack >= 2.0)
		{
			DragonAttack(m_humanDragonAttack, dt);
			count_dragonAttack = 0;
		}
		if (count_dragonAttack > 1.0 && dragon->GetSpriteFire())
		{
			dragon->GetSpriteFire()->setVisible(false);
		}
	}
	
	count_dragonAttack += dt;

	if (m_stateReduce)
	{
		this->RedurceBloodBlueTeam(m_listScoutTowns, containerHallTown,
			containerStoreHouse, knight, hero, m_vecPosition);
	}

	//-----Create knight red attack-----
	static float c = 0;
	if (c >= 10 && (m_knightRed.size() + m_knightRedMove.size() < 15))
	{
		for (int i = 0; i < 3; i++)
		{
			Knight *k = new Knight(_layer2D, TEAM_RED);
			int dir = rand() % (50 - 10 + 1) + 10;
			k->SetPositionKnight(Vec2(m_houseDragon->GetPosition().x + dir,
				m_houseDragon->GetPosition().y - m_houseDragon->getSprite()->getContentSize().height + dir));
			m_knightRedMove.push_back(k);
		}
		c = 0;
	}
	c += dt;
	if (!m_knightRedMove.empty() && m_stateKnightRedMove == DRAGON_STATE_FIND)
	{
		KnightRedMoveAttack(dt);
	}
	if (m_stateKnightRedMove == DRAGON_STATE_FIND)
	{
		KnightRedMoveAttack(dt);
	}
	else
	{
		KnightRedMoveAttackHuman(m_humanKnightRedAttack,dt);
	}

	//-------Knight blue---------
	KnightBlueCheckAttack(dragon, m_knightRed, m_knightRedMove,dt);
}

void GamePlayScene::heroAttack(int STATE_ATTACK, int type) {
	if (hero->GetPosition().distance(m_houseDragon->GetPosition()) <= 500)
	{
		m_houseDragon->SetScaleBlood(hero->GetDame());
	}
	if (type == 0) {
		hero->getAttack(STATE_ATTACK);
		bool v = false;
		if (dragon)
		{
			
			if (hero->GetPosition().distance(dragon->GetPosition()) <= 100)
			{
				dragon->SetScaleBlood((hero->getDamage()->getDamageNormal() - dragon->GetAmor()));
				v = true;

			}
		}
		
		if (v == false)
		{
			bool p = false;
			for (auto b : m_knightRed)
			{
				if (hero->GetPosition().distance(b->GetPosition())) {
					b->SetScaleBlood(hero->getDamage()->getDamageNormal() - b->GetAmor());
					p = true;
					//b->SetScaleBlood(hero->getDamage()->getDamageNormal() - b->GetAmor());
					break;
				}
			}
			if (p == false)
			for (auto c : m_knightRedMove)
			{
				if (hero->GetPosition().distance(c->GetPosition())) {
					c->SetScaleBlood(hero->getDamage()->getDamageNormal() - c->GetAmor());
					break;
				}
			}
		}

	}
	if (type == 1) {

		hero->skillAnimation(_layer2D, 1);
		bool c = false;
		if (dragon)
		{
			if (hero->GetPosition().distance(dragon->GetPosition()) <= 400) {
				//dragon->getBlood()->reduceBlood(hero->getDamage()->getDamageSkill_1());
				dragon->SetScaleBlood(hero->getDamage()->getDamageNormal() - dragon->GetAmor());
				if (hero->GetPosition().distance(dragon->GetPosition()) <= 200)
				{
					dragon->SetScaleBlood((hero->getDamage()->getDamageSkill_1() - dragon->GetAmor()));

				}
		}
		
			
			/*	
				for (auto b : m_knightRed)
				{
					if (abs(b->getSprite()->getPositionX() - hero->getSprite()->getPositionX()) < 200 &&
						abs(b->getSprite()->getPositionY() - hero->getSprite()->getPositionY()) < 200) {
						b->SetScaleBlood(hero->getDamage()->getDamageNormal() - b->GetAmor());
						
						break;
					}
				}
		
				for (auto c : m_knightRedMove)
				{
					if (abs(c->getSprite()->getPositionX() - hero->getSprite()->getPositionX()) < 100 &&
						abs(c->getSprite()->getPositionY() - hero->getSprite()->getPositionY()) < 100) {
						c->SetScaleBlood(hero->getDamage()->getDamageNormal() - c->GetAmor());
						break;
					}
				}*/
		}
	}
	if (type == 2) {

		hero->skillAnimation(_layer2D, 2);
		if (dragon)
		{
			if (hero->GetPosition().distance(dragon->GetPosition()) <= 200)
			{
				dragon->SetScaleBlood((hero->getDamage()->getDamageSkill_2() - dragon->GetAmor()));
			}
		}


		for (auto b : m_knightRed)
		{
			if (hero->GetPosition().distance(b->GetPosition()) <= 200)
			{
				b->SetScaleBlood(hero->getDamage()->getDamageNormal() - b->GetAmor());
				break;
			}
		}

		for (auto c : m_knightRedMove)
		{
			if (hero->GetPosition().distance(c->GetPosition()) <= 200) {
				c->SetScaleBlood(hero->getDamage()->getDamageNormal() - c->GetAmor());
				break;
			}
		}

	}
		
}

void GamePlayScene::miniMap()
{

	m_miniMap = Sprite::create("miniMap.png");

	m_miniMap->setAnchorPoint(Vec2(0, 0));
	m_miniMap->setPosition(condinatorMiniMap);
	//_layerUI->addChild(minimapSprite,11);
	_layerUI->addChild(m_miniMap);

	map_1 = Sprite::create("map1.png");
	
	map_1->setAnchorPoint(Vec2(0, 0));
	
	map_1->setPosition(m_miniMap->getPositionX()+5, m_miniMap->getPositionY() + 5);


	//_layerUI->addChild(minimapSprite,11);
	_layerUI->addChild(map_1);

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
		int dir = rand() % (50 - 10 + 1) + 10;
		float x = mapTopRight->getPosition().x + mapTopRight->getContentSize().width * 7 / 9 + dir;
		float y = mapTopRight->getPosition().y + mapTopRight->getContentSize().height * 7 / 9 + dir;
		knightRed->SetPositionKnight(Vec2(x, y));
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
			if (_distance <= RANGER_ATTACK && _distance > knightBlue->GetConTentSize().width + 1)
			{
				return positionKnightBlue;
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
			if (red->GetBlood() > 0)
			{
				red->MoveRed(vec);
			}		
		}
	}
}


void GamePlayScene::ChekAttackKnight(std::vector<Knight*> red, std::vector<Knight*> blue, Dragon *dra, float dt)
{
	Point positionKnightRed, positionKnightBlue;
	for (auto knightBlue : blue)
	{
		positionKnightBlue = knightBlue->GetPositionKnight();
		for (auto knightRed : red)
		{
			positionKnightRed = knightRed->GetPositionKnight();
			float _distance = positionKnightRed.distance(positionKnightBlue);
			if (_distance <= knightBlue->GetConTentSize().width)
			{
				knightRed->Attack(knightBlue,dt);

			}
		}
	}
}

void GamePlayScene::ReduceBloodKnight(Knight * red, Knight * blue)
{
	
}

void GamePlayScene::RemoveKnightBlue(Knight * blue)
{
	if (!knight.empty())
	{
		for (auto it = knight.begin(); it != knight.end(); )
		{
			if ((*it) == blue)
			{
				blue->SetSelected(false);
				knight.erase(it);
				break;
			}
			++it;
		}
	}
}

void GamePlayScene::RemoveKnightRedMove(Knight * k)
{
	if (!knight.empty())
	{
		for (auto it = m_knightRedMove.begin(); it != m_knightRedMove.end(); )
		{
			if ((*it) == k)
			{
				m_knightRedMove.erase(it);
				break;
			}
			++it;
		}
	}
}

void GamePlayScene::RemoveKnightRed(Knight* red)
{
	if (!m_knightRed.empty())
	{
		for (auto it = m_knightRed.begin(); it != m_knightRed.end(); )
		{
			if ((*it) == red)
			{
				m_knightRed.erase(it);
				break;
			}
		}
	}
}

void GamePlayScene::DragonCheck(std::vector<ScoutTown*> scoutTown, std::vector<TownHall*> townHall, 
	std::vector<StoreHouse*> storeHouse, std::vector<Knight*> knight, Hero* heo)
{
	float dis = 100000;
	Vec2 vec = Vec2::ZERO;
	for (auto st : scoutTown)
	{
		float d = st->GetPosition().distance(dragon->GetPosition());
		if (d < dis && d > 200)
		{
			dis = d;
			vec = st->GetPosition();
			m_humanDragonAttack = st;
		}
	}
	for (auto st : townHall)
	{
		float d = st->GetPosition().distance(dragon->GetPosition());
		if (d < dis && d > 200)
		{
			dis = d;
			vec = st->GetPosition();
			m_humanDragonAttack = st;
		}
	}
	for (auto st : storeHouse)
	{
		float d = st->GetPosition().distance(dragon->GetPosition());
		if (d < dis && d > 200)
		{
			dis = d;
			vec = st->GetPosition();
			m_humanDragonAttack = st;
		}
	}
	for (auto st : knight)
	{
		float d = st->GetPosition().distance(dragon->GetPosition());
		if (d < dis && d > 200)
		{
			dis = d;
			vec = st->GetPosition();
			m_humanDragonAttack = st;
		}
	}
	if (heo->GetPosition().distance(dragon->GetPosition()) < dis)
	{
		dis = heo->GetPosition().distance(dragon->GetPosition());
		vec = heo->GetPosition();
		m_humanDragonAttack = heo;
	}
	dragon->Move(vec);
}

void GamePlayScene::DragonAttack(Human * hm, float dt)
{
	if (dragon->GetPosition().distance(hm->GetPosition()) <= 400)
	{
		m_dragonState = DRAGON_STATE_ATTACK;	
		m_vecPosition = hm->GetPosition();
		m_stateReduce = true;
		dragon->Attack(hm, dt);
		if (hm->GetBlood() <= 0)
		{
			m_dragonState = DRAGON_STATE_FIND;
		}
	}
	else 
	{
		m_dragonState = DRAGON_STATE_FIND;
	}
}

void GamePlayScene::RedurceBloodBlueTeam(std::vector<ScoutTown*> scoutTown, std::vector<TownHall*> townHall,
	std::vector<StoreHouse*> storeHouse, std::vector<Knight*> knight, Hero* heo, Vec2 vec)
{
	float dame = dragon->GetDame();
	for (auto st : scoutTown)
	{
		float d = st->GetPosition().distance(vec);
		if (d <= (DRAGON_RANGER_DAME + st->getSprite()->getContentSize().width / 2))
		{
			st->SetScaleBlood(dame - st->GetAmor());
			
		}
	}
	for (auto st : townHall)
	{
		float d = st->GetPosition().distance(vec);
		if (d <= (DRAGON_RANGER_DAME + st->GetButton()->getContentSize().width / 2))
		{
			st->SetScaleBlood(dame - st->GetAmor());
		}
	}
	for (auto st : storeHouse)
	{
		float d = st->GetPosition().distance(vec);
		if (d <= (DRAGON_RANGER_DAME + st->GetButton()->getContentSize().width / 2))
		{
			st->SetScaleBlood(dame - st->GetAmor());
		}
	}
	for (auto st : knight)
	{
		float d = st->GetPosition().distance(vec);
		if (d <= DRAGON_RANGER_DAME)
		{
			st->SetScaleBlood(dame - st->GetAmor());
		}
	}
	if (heo->GetPosition().distance(vec) <= DRAGON_RANGER_DAME)
	{
	
		heo->getBlood()->reduceBlood(dame - heo->GetAmor());
		hero->handleBloodBar();
	}
	m_stateReduce = false;
}

void GamePlayScene::AddHouseDragon()
{
	m_houseDragon = new HouseDragon(_layer2D, TEAM_RED);
	m_houseDragon->SetPosition(mapTopRight->getPosition() + mapTopRight->getContentSize() * 8 / 9);

	auto houseKnightRed = Sprite::create("KnightHouse.png");
	houseKnightRed->setPosition(m_houseDragon->GetPosition().x - houseKnightRed->getContentSize().width * 1.5, m_houseDragon->GetPosition().y);
	auto physicKnightRed = PhysicsBody::createBox(houseKnightRed->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	physicKnightRed->setGravityEnable(false);
	physicKnightRed->setRotationEnable(false);
	physicKnightRed->setCategoryBitmask(4);
	physicKnightRed->setCollisionBitmask(125);
	houseKnightRed->setPhysicsBody(physicKnightRed);
	_layer2D->addChild(houseKnightRed);

	auto houseKnightRed2 = Sprite::create("KnightHouse.png");
	houseKnightRed2->setPosition(m_houseDragon->GetPosition().x, m_houseDragon->GetPosition().y - houseKnightRed->getContentSize().height * 1.5);
	auto physicKnightRed2 = PhysicsBody::createBox(houseKnightRed->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	physicKnightRed2->setGravityEnable(false);
	physicKnightRed2->setRotationEnable(false);
	physicKnightRed2->setCategoryBitmask(4);
	physicKnightRed2->setCollisionBitmask(125);
	houseKnightRed2->setPhysicsBody(physicKnightRed2);
	_layer2D->addChild(houseKnightRed2);
}

Human* GamePlayScene::KnightRedMoveCheck(std::vector<ScoutTown*> scoutTown, std::vector<TownHall*> townHall,
	std::vector<StoreHouse*> storeHouse, std::vector<Knight*> knight, Hero* heo)
{
	//float dis = 200;
	for (auto k : m_knightRedMove)
	{
		if (m_stateKnightRedMove == DRAGON_STATE_FIND)
		{
			for (auto st : scoutTown)
			{
				float d = st->GetPosition().distance(k->GetPosition());
				if (d <= 200)
				{
					m_stateKnightRedMove = DRAGON_STATE_ATTACK;
					return st;
				}
			}
		}
		if (m_stateKnightRedMove == DRAGON_STATE_FIND)
		{
			for (auto st : townHall)
			{
				float d = st->GetPosition().distance(k->GetPosition());
				if (d <= 200)
				{
					m_stateKnightRedMove = DRAGON_STATE_ATTACK;
					return st;
				}
			}
		}
		if (m_stateKnightRedMove == DRAGON_STATE_FIND)
		{
			for (auto st : storeHouse)
			{
				float d = st->GetPosition().distance(k->GetPosition());
				if (d <= 200)
				{
					m_stateKnightRedMove = DRAGON_STATE_ATTACK;
					return st;
				}
			}
		}
		if (m_stateKnightRedMove == DRAGON_STATE_FIND)
		{
			for (auto st : knight)
			{
				float d = st->GetPosition().distance(k->GetPosition());
				if (d <= 200)
				{
					m_stateKnightRedMove = DRAGON_STATE_ATTACK;
					return st;
				}
			}
		}
		if (m_stateKnightRedMove == DRAGON_STATE_FIND)
		{
			float d = heo->GetPosition().distance(k->GetPosition());
			if (d <= 200)
			{
				m_stateKnightRedMove = DRAGON_STATE_ATTACK;
				return heo;
			}
		}
		
	}
	return nullptr;
}

void GamePlayScene::KnightRedMoveAttack(float dt)
{
	m_humanKnightRedAttack = KnightRedMoveCheck(m_listScoutTowns, containerHallTown, containerStoreHouse, knight, hero);
	if (m_humanKnightRedAttack != nullptr)
	{		
		if (!m_humanKnightRedAttack->IsDie())
		{
			for (auto k : m_knightRedMove)
			{
				k->MoveRed(m_humanKnightRedAttack->GetPosition());
			}
		}
		else
		{
			m_stateKnightRedMove = DRAGON_STATE_FIND;
		}	
	}
	else
	{
		m_stateKnightRedMove = DRAGON_STATE_FIND;
	}
	
}

void GamePlayScene::KnightRedMoveAttackHuman(Human * hm, float dt)
{
	for (auto k : m_knightRedMove)
	{
		float _dis = k->GetPosition().distance(hm->GetPosition());
		if (_dis <= k->GetConTentSize().width)
		{
			k->Attack(hm, dt);
			if (hm->IsDie())
			{
				m_stateKnightRedMove = DRAGON_STATE_FIND;
			}
		}
	}
	m_stateKnightRedMove = DRAGON_STATE_FIND;
}

void GamePlayScene::KnightBlueCheckAttack(Dragon * dra, std::vector<Knight*> red, std::vector<Knight*> redMove,float dt)
{
	for (auto k : knight)
	{
		m_checkKnight = KNIGHT_STATE_FIND;
		if (m_checkKnight == KNIGHT_STATE_FIND)
		{
			for (auto st : red)
			{
				float d = st->GetPosition().distance(k->GetPosition());
				if (d <= k->GetConTentSize().width)
				{
					k->Attack(st, dt);
					m_checkKnight = KNIGHT_STATE_ATTACK;
				}
			}
		}

		if (m_checkKnight == KNIGHT_STATE_FIND)
		{
			for (auto st : redMove)
			{
				float d = st->GetPosition().distance(k->GetPosition());
				if (d <= k->GetConTentSize().width)
				{
					k->Attack(st, dt);
					m_checkKnight = KNIGHT_STATE_ATTACK;
				}
			}
		}
		else
		{
			continue;
		}
		if (dra != nullptr)
		{
			if (m_checkKnight == KNIGHT_STATE_FIND)
			{
				float d = dra->getSprite()->getPosition().distance(k->GetPosition());
				if (d <= k->GetConTentSize().width)
				{
					k->Attack(dra, dt);
				}
			}
		}
	}
}

void GamePlayScene::ScoutAttack(std::vector<ScoutTown*> m_listScoutTowns, std::vector<Knight*> m_knightRed, std::vector<Knight*> m_knightRedMove, float dt)
{
	count_bullet += dt;
	if (count_bullet>0.4 && !m_listScoutTowns.empty())
	{
		for (auto a : m_listScoutTowns)
		{

			bool cur = false;
			if (dragon)
			{
				if (a->GetPosition().distance(dragon->GetPosition()) <= RANGER_ATTACK_SCOUT)
				{
					a->Update(count_bullet, dragon);
					dragon->SetScaleBlood(a->getDamage()->getDamageNormal() - dragon->GetAmor());
				}
				else
				{					
					if (!m_knightRedMove.empty())
					{
						for (auto b : m_knightRedMove)
						{
							if (a->GetPosition().distance(b->GetPosition()) <= RANGER_ATTACK_SCOUT)
							{
								a->Update(count_bullet, b);

								b->SetScaleBlood(a->getDamage()->getDamageNormal() - b->GetAmor());
								cur = true;
								break;
							}
						}
					}
					if (!cur)
					{
						if (!m_knightRed.empty())
						{
							for (auto b : m_knightRed)
							{
								if (a->GetPosition().distance(b->GetPosition()) <= RANGER_ATTACK_SCOUT)
								{
									a->Update(count_bullet, b);

									b->SetScaleBlood(a->getDamage()->getDamageNormal() - b->GetAmor());
									break;
								}
							}
						}
					}			
				}
				
			}
			else
			{
				if (!m_knightRedMove.empty())
				{
					for (auto b : m_knightRedMove)
					{
						if (a->GetPosition().distance(b->GetPosition()) <= RANGER_ATTACK_SCOUT)
						{
							a->Update(count_bullet, b);

							b->SetScaleBlood(a->getDamage()->getDamageNormal() - b->GetAmor());
							cur = true;
							break;
						}
					}
				}
				if (!cur)
				{
					if (!m_knightRed.empty())
					{
						for (auto b : m_knightRed)
						{
							if (a->GetPosition().distance(b->GetPosition()) <= RANGER_ATTACK_SCOUT)
							{
								a->Update(count_bullet, b);
								b->SetScaleBlood(a->getDamage()->getDamageNormal() - b->GetAmor());
								break;
							}
						}
					}
				}				
			}
			
		}
		count_bullet = 0;
	}
}

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

void GamePlayScene::handleDragonVsScout()
{
	
}

void GamePlayScene::handleDragonVsHero()
{
	////if (dragon->getBlood()->isDie() == true) { return; }
	//switch (hero->getDirect())
	//{
	//case 0:
	//	dragon->dragonMove(4);
	//	dragon->dragonFire(4);
	//	break;
	//case 1:
	//	dragon->dragonMove(5);
	//	dragon->dragonFire(5);
	//	break;
	//case 2:
	//	dragon->dragonMove(6);
	//	dragon->dragonFire(6);
	//	break;
	//case 3:
	//	dragon->dragonMove(7);
	//	dragon->dragonFire(7);
	//	break;
	//case 4:
	//	dragon->dragonMove(0);
	//	dragon->dragonFire(7);
	//	break;
	//case 5:
	//	dragon->dragonMove(1);
	//	dragon->dragonFire(7);
	//	break;
	//case 6:
	//	dragon->dragonMove(2);
	//	dragon->dragonFire(7);
	//	break;
	//case 7:
	//	dragon->dragonMove(3);
	//	dragon->dragonFire(7);
	//	break;
	//default:
	//	break;
	//}
}
