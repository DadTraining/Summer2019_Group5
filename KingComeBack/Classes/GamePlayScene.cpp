#include"GamePlayScene.h"

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
	newHallTown = nullptr;
	screenSize = Director::getInstance()->getVisibleSize();
	sizeWall = Vec2(3.0f, 3.0f);

	this->setCameraMask((unsigned short)CameraFlag::DEFAULT, true);
	this->setCameraMask((unsigned short)CameraFlag::USER1, true);

	//Create Layer for map and camera
	this->createLayer2D();

	//add map
	this->AddMap();



	//code duoc
	hero = new Hero(_layer2D);

	//add knight
	AddKnight();
	// add camera
	this->AddCameraUSER1();



	//Add listener
	this->AddListener();

	//Add camera User 2
	this->AddCameraUSER2();

	// add layer 
	this->createLayerUI();

	//code duoc
	createButtonAttack();

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
	knight->Move(touchCurrenPositon);

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

bool GamePlayScene::OnContactBegin(PhysicsContact & contact)
{
	auto spriteA = contact.getShapeA()->getBody();
	auto spriteB = contact.getShapeB()->getBody();

	// camera with map
	auto body = (spriteA->getCategoryBitmask() == 0x04 || spriteA->getCategoryBitmask() == 0x08) ? spriteA : spriteB;
	CC_ASSERT(body->getCategoryBitmask() == 0x04 || body->getCategoryBitmask() == 0x08);

	return true;
}

void GamePlayScene::AddMap()
{
	map = TMXTiledMap::create("map.tmx");
	map->setAnchorPoint(Vec2(0, 0));
	map->setPosition(this->getPosition());
	_layer2D->addChild(map);

	// Map top
	auto mapTop = TMXTiledMap::create("mapTop.tmx");
	mapTop->setAnchorPoint(Vec2(0, 0));
	mapTop->setPositionY(map->getContentSize().height);
	_layer2D->addChild(mapTop);

	auto sizeMapHeight = Size(10, map->getContentSize().height + mapTop->getContentSize().height);
	auto sizeMapUp = Size(map->getContentSize().width, 10);
	// add physic for map left


	auto nodeLeft = Node::create();
	auto physicLeft = PhysicsBody::createBox(sizeMapHeight,
		PHYSICSBODY_MATERIAL_DEFAULT);
	physicLeft->setDynamic(false);
	physicLeft->setCategoryBitmask(1);
	physicLeft->setCollisionBitmask(2);
	nodeLeft->setPhysicsBody(physicLeft);
	nodeLeft->setPosition(map->getPositionX() - 10, sizeMapHeight.height / 2);
	_layer2D->addChild(nodeLeft);


	// add physic for map up

	auto nodeUP = Node::create();
	auto physicUp = PhysicsBody::createBox(sizeMapUp,
		PHYSICSBODY_MATERIAL_DEFAULT);
	physicUp->setDynamic(false);
	physicUp->setCategoryBitmask(1);
	physicUp->setCollisionBitmask(2);
	nodeUP->setPhysicsBody(physicUp);
	nodeUP->setPosition(map->getContentSize().width /2 , sizeMapHeight.height + 5);
	_layer2D->addChild(nodeUP);

	// add physic for map right

	auto nodeRight = Node::create();
	auto physicRight = PhysicsBody::createBox(sizeMapHeight,
		PHYSICSBODY_MATERIAL_DEFAULT);
	physicRight->setDynamic(false);
	physicRight->setCategoryBitmask(1);
	physicRight->setCollisionBitmask(2);
	nodeRight->setPhysicsBody(physicRight);
	nodeRight->setPosition(map->getContentSize().width + 10, sizeMapHeight.height / 2);
	_layer2D->addChild(nodeRight);

	// add physic for map down

	auto nodeDown = Node::create();
	auto physicDown = PhysicsBody::createBox(sizeMapUp,
		PHYSICSBODY_MATERIAL_DEFAULT);
	physicDown->setDynamic(false);
	physicDown->setCategoryBitmask(1);
	physicDown->setCollisionBitmask(2);
	nodeDown->setPhysicsBody(physicDown);
	nodeDown->setPosition(map->getContentSize().width / 2, map->getPosition().y - 5);
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

	/*auto listenerMouse = EventListenerMouse::create();
	listenerMouse->onMouseScroll = CC_CALLBACK_1(GamePlayScene::OnContactBegin, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this);*/

	// add listen contact
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GamePlayScene::OnContactBegin, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}
void GamePlayScene::AddJoystick()
{
	Size s = Director::getInstance()->getWinSize();
	Rect joystickBaseDimensions;
	joystickBaseDimensions = Rect(0, 0, 160.0f, 160.0f);

	Point joystickBasePosition;
	joystickBasePosition = Point(screenSize.width / 9, screenSize.height / 7);

	joystickBase = new SneakyJoystickSkinnedBase();
	joystickBase->init();
	joystickBase->setPosition(joystickBasePosition);

	joystickBack = Sprite::create("res/joystick-back.png");
	joystick = Sprite::create("res/stick.png");

	joystickBase->setBackgroundSprite(joystickBack);
	joystickBase->setThumbSprite(joystick);

	aJoystick = new SneakyJoystick();
	aJoystick->initWithRect(joystickBaseDimensions);

	aJoystick->autorelease();
	joystickBase->setJoystick(aJoystick);
	joystickBase->setPosition(joystickBasePosition);

	leftJoystick = joystickBase->getJoystick();
	leftJoystick->retain();
	_layerUI->addChild(joystickBase, 10);
}

void GamePlayScene::AddButtonPopUpHero()
{
	auto button = ui::Button::create("backpack.png", "backpack_press.png");
	button->setTitleText("Hero");
	button->setScale(0.3);
	button->setPosition(Vec2(screenSize.width / 1.65, screenSize.height / 9.2));
	button->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type){
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
	button->setTitleText("House");
	button->setScale(0.3);
	button->setPosition(Vec2(screenSize.width / 1.5, screenSize.height / 9));
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
	containerForSpriteUI->addChild(sprite);
	_layerUI->addChild(containerForSpriteUI, 10);
}

void GamePlayScene::AddPopupHero()
{
	auto popUpHero = UICustom::Popup::createAsConfirmDialogue("hero", "",[=]() {

	});
	_layerUI->addChild(popUpHero, 10);
}

void GamePlayScene::AddPopupHouse()
{
	auto popupHouse = UICustom::PopupHouse::createAsConfirmDialogue("House", "",
		CC_CALLBACK_0(GamePlayScene::AddEventForPopupTownHall, this),
		CC_CALLBACK_0(GamePlayScene::AddEventForPopupScoutTown, this)
		);
	_layerUI->addChild(popupHouse, 10);
}
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
			newHallTown = new TownHall(_layer2D, 2);
			newHallTown->getSprite()->setPosition(_touch->getLocation()
				+ camera->getPosition() - Director::getInstance()->getVisibleSize() / 2);
			newHallTown->getSprite()->setCameraMask(2);
			this->getEventDispatcher()->removeEventListener(buildHouseListener);

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
		newScoutTown->getSprite()->setPosition(_touch->getLocation()
			+ camera->getPosition() - Director::getInstance()->getVisibleSize() / 2);
		newScoutTown->getSprite()->setCameraMask(2);
		this->getEventDispatcher()->removeEventListener(buildHouseListener);
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(buildHouseListener, this);
}

void GamePlayScene::createLayerUI()
{
	_layerUI = Layer::create();
	_layerUI->setPosition(Vec2(2 , 2));
	log("layerUI contentsize : %f , %f", _layerUI->getContentSize().width, _layerUI->getContentSize().height);
	
	this->addChild(_layerUI, 10);
	_layerUI->setCameraMask((unsigned short)CameraFlag::USER2);

	//Add sprite UI;
	this->AddSpriteUI();

	//Add joystick
	this->AddJoystick();
}

void GamePlayScene::update(float dt)
{
	if (newScoutTown != nullptr)
	{
		newScoutTown->Update(dt);
	}
	if (newHallTown != nullptr)
	{
		newHallTown->Update(dt);
	}
	if (newHallTown != nullptr && newHallTown->loadingBar == nullptr && createListenerForTownHall == true)
	{
		createListenerForTownHall = false;
		auto listenerTownHall = EventListenerTouchOneByOne::create();
		listenerTownHall->onTouchBegan = [=](Touch *touch, Event *_event)
		{
			if (newHallTown->getSprite()->getBoundingBox().containsPoint(touch->getLocation()
				+ camera->getPosition() - Director::getInstance()->getVisibleSize() / 2))
			{
				auto popup = UICustom::PopupTownHall::createAsConfirmDialogue("Town hall", "", [=]()
				{
					// event
				});
				_layer2D->addChild(popup);
				return true;
			}
			return false;
		};
		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTownHall, this);


		

	}


	// code duoc

	//gameSprite->runAction(mListAction[0]);
	log("JOYSTIK %f %f", leftJoystick->getVelocity().x, leftJoystick->getVelocity().y);

	if (leftJoystick->getVelocity().x > 0 && leftJoystick->getVelocity().y > -0.2 && leftJoystick->getVelocity().y < 0.2) {
		if (count<5) {
			if (count == 1) {

				log("ok");
			}

			hero->moveRight0();
			hero->setDirect(0);
			count++;
			if (count == 5) {
				count = 0;
			}
		}
	}
	if (leftJoystick->getVelocity().x > 0 && leftJoystick->getVelocity().y > 0.2 && leftJoystick->getVelocity().y < 0.8) {
		if (count<5) {

			count++;
			hero->moveRight1();
			hero->setDirect(1);
			log("ok");
			if (count == 5) {
				count = 0;
			}
		}

	}

	if (leftJoystick->getVelocity().y > 0 && leftJoystick->getVelocity().x > -0.2 && leftJoystick->getVelocity().x < 0.2) {
		if (count<5) {

			count++;
			log("ok");
			hero->upTo();
			hero->setDirect(2);
			if (count == 5) {
				count = 0;
			}
		}

	}
	if (leftJoystick->getVelocity().y > 0 && leftJoystick->getVelocity().x <= -0.2 && leftJoystick->getVelocity().x >= -0.8) {
		if (count<5) {
			log("ok");
			count++;
			hero->moveLeft1();
			hero->setDirect(3);
			if (count == 5) {
				count = 0;
			}
		}
	}

	if (leftJoystick->getVelocity().x < 0 && leftJoystick->getVelocity().y > -0.2 && leftJoystick->getVelocity().y < 0.2) {
		if (count<5) {
			//gameSprite->setFlippedX(true);

			count++;

			hero->moveLeft0();
			hero->setDirect(4);

			if (count == 5) {
				count = 0;
			}
		}

	}
	if (leftJoystick->getVelocity().x < 0 && leftJoystick->getVelocity().y <= -0.2 && leftJoystick->getVelocity().y >= -0.8) {
		if (count<5) {
			log("ok");
			count++;
			hero->moveLeft_1();
			hero->setDirect(5);
			if (count == 5) {
				count = 0;
			}
		}

	}

	if (leftJoystick->getVelocity().y < 0 && leftJoystick->getVelocity().x <= 0.2 && leftJoystick->getVelocity().x >= -0.2) {
		if (count<5) {
			log("ok");
			count++;
			hero->downTo();
			hero->setDirect(6);
			if (count == 5) {
				count = 0;
			}
		}

	}

	if (leftJoystick->getVelocity().y < 0 && leftJoystick->getVelocity().x <= 0.8 && leftJoystick->getVelocity().x >= 0.2) {
		if (count<5) {
			log("ok");
			count++;
			hero->moveRight_1();
			hero->setDirect(7);
			if (count == 5) {
				count = 0;
			}
		}
	}

	if (leftJoystick->getVelocity().x == 0.0 && leftJoystick->getVelocity().y == 0.0) {
		//gameSprite->stopAllActions();
	}

	joystickBase->updatePositions(dt);

	//	spriteFocus->setPosition(gameSprite->getPosition().x , gameSprite->getPosition().y +50);

	heroAttack(hero->getDirect());

}

void GamePlayScene::heroAttack(int STATE_ATTACK) {
	if (mButtonAttack->getBoundingBox().containsPoint(mCurrentTouch)) {
		hero->getAttack(STATE_ATTACK);
		mCurrentTouch.x++;
	}

}

void GamePlayScene::createButtonAttack()
{
	//code duoc
	mButtonAttack = Sprite::create("focus.png");
	mButtonAttack->setScale(0.25);
	mButtonAttack->setPosition(screenSize.width *5/6  , screenSize.height * 1 / 4  );
	_layerUI->addChild(mButtonAttack,10);

}

void GamePlayScene::AddKnight()
{
	knight = new Knight(_layer2D, 0);
	knight->SetPositionKnight(Vec2(screenSize.width / 2, screenSize.height / 2));
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


