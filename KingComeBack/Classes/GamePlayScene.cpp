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
	//newHallTown = nullptr;
	screenSize = Director::getInstance()->getVisibleSize();
	sizeWall = Vec2(3.0f, 3.0f);


	condinatorMiniMap = Vec2(screenSize.width*1/20, screenSize.height*8/10);

	condinatorMiniMap = Vec2(screenSize.width * 1 / 20, screenSize.height * 8 / 10);

	pause = DelayTime::create(20);
	

	this->setCameraMask((unsigned short)CameraFlag::DEFAULT, true);
	this->setCameraMask((unsigned short)CameraFlag::USER1, true);

	//Create Layer for map and camera
	this->createLayer2D();

	//add map
	this->AddMap();



	//code duoc
	hero = new Hero(_layer2D);



	dragon = new Dragon(_layer2D);


	// add camera
	this->AddCameraUSER1();



	//Add listener
	this->AddListener();

	//Add camera User 2
	this->AddCameraUSER2();

	// add layer 
	this->createLayerUI();

	//Add Knight Red
	AddKnightRed();

	//code duoc
	createButtonAttack();
	createButton_Skill_1();

	createButton_Skill_2();

	miniMap();

	//bullet = new Bullet(_layerUI,Vec2(300,300));

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

	log("Touch %f %f", touch->getLocation().x , touch->getLocation().y);
	log("Hero position %f %f", hero->getPositionHero().x , hero->getPositionHero().y);
	log("camera %f %f", camera -> getPosition().x + touch->getLocation().x ,  camera->getPosition().y + touch->getLocation().y);

	log("dot %f %f", dot->getPosition().x, dot->getPosition().y);

	log("touch Location: %f, %f", touch->getLocation().x, touch->getLocation().y);

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
		if (k != nullptr)
		{
			k->Move(touchCurrenPositon);
		}
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
	//map->setScale(m_scale);
	_layer2D->addChild(map);

	//get contensize big map
	condinatorBigMap = Vec2(map->getContentSize().height, map->getContentSize().width);
	


	// Map top
	mapTop = TMXTiledMap::create("mapTop.tmx");
	mapTop->setAnchorPoint(Vec2(0, 0));
	mapTop->setPositionY(map->getContentSize().height);
	//mapTop->setScale(m_scale);
	_layer2D->addChild(mapTop);

	auto sizeMapHeight = Size(10, map->getContentSize().height + mapTop->getContentSize().height);
	auto sizeMapUp = Size(map->getContentSize().width, 10);
	// add physic for map left


	auto nodeLeft = Node::create();
	auto physicLeft = PhysicsBody::createBox(sizeMapHeight,
		PHYSICSBODY_MATERIAL_DEFAULT);
	physicLeft->setDynamic(false);
	physicLeft->setCategoryBitmask(1);
	physicLeft->setCollisionBitmask(31);
	nodeLeft->setPhysicsBody(physicLeft);
	nodeLeft->setPosition(map->getPositionX() - 10, sizeMapHeight.height / 2);
	_layer2D->addChild(nodeLeft);


	// add physic for map up

	auto nodeUP = Node::create();
	auto physicUp = PhysicsBody::createBox(sizeMapUp,
		PHYSICSBODY_MATERIAL_DEFAULT);
	physicUp->setDynamic(false);
	physicUp->setCategoryBitmask(1);
	physicUp->setCollisionBitmask(31);
	nodeUP->setPhysicsBody(physicUp);
	nodeUP->setPosition(map->getContentSize().width /2 , sizeMapHeight.height + 5);
	_layer2D->addChild(nodeUP);

	// add physic for map right

	auto nodeRight = Node::create();
	auto physicRight = PhysicsBody::createBox(sizeMapHeight,
		PHYSICSBODY_MATERIAL_DEFAULT);
	physicRight->setDynamic(false);
	physicRight->setCategoryBitmask(1);
	physicRight->setCollisionBitmask(31);
	nodeRight->setPhysicsBody(physicRight);
	nodeRight->setPosition(map->getContentSize().width + 10, sizeMapHeight.height / 2);
	_layer2D->addChild(nodeRight);

	// add physic for map down

	auto nodeDown = Node::create();
	auto physicDown = PhysicsBody::createBox(sizeMapUp,
		PHYSICSBODY_MATERIAL_DEFAULT);
	physicDown->setDynamic(false);
	physicDown->setCategoryBitmask(1);
	physicDown->setCollisionBitmask(31);
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
	joystickBasePosition = Point(screenSize.width / 9, screenSize.height * 2 / 7);

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
	joystickBase->setScale(m_scaleX, m_scaleY);
	_layerUI->addChild(joystickBase, 10);
}

void GamePlayScene::AddButtonPopUpHero()
{
	auto button = ui::Button::create("backpack.png", "backpack_press.png");
	button->setTitleText("Hero");
	button->setScale(m_scaleX * 0.3, m_scaleY * 0.3);
	button->setPosition(Vec2(screenSize.width / 1.65, screenSize.height / 9.5));
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

	sprite->setScale(1);


	sprite->setPosition(screenSize / 2);
	m_scaleX = screenSize.width / sprite->getContentSize().width;
	m_scaleY = screenSize.height / sprite->getContentSize().height;
	
	sprite->setScale(m_scaleX,m_scaleY);
	containerForSpriteUI->addChild(sprite);

	_layerUI->addChild(containerForSpriteUI, 10);
}

void GamePlayScene::AddPopupHero()
{
	auto popUpHero = UICustom::PopupHero::createAsConfirmDialogue(_layerUI ,"hero", "",[=]() {

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

			auto HallTown = new TownHall(_layer2D, 2);
			HallTown->getSprite()->setPosition(_touch->getLocation()
				+ camera->getPosition() - Director::getInstance()->getVisibleSize() / 2);
			HallTown->getSprite()->setCameraMask(2);
			newHallTown.push_back(HallTown);
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

		//bullet = new Bullet(_layerUI,);
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
		newScoutTown->getSprite()->setCameraMask(2);
		postScountTower = _touch->getLocation() + camera->getPosition() - Director::getInstance()->getVisibleSize() / 2;
		

		this->getEventDispatcher()->removeEventListener(buildHouseListener);
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(buildHouseListener, this);

}

void GamePlayScene::CreateKnight()
{
	auto createKnight = new Knight(_layer2D, 2);
	//knight->getSprite()->setCameraMask(2);

	createKnight->SetPositionKnight(newHallTown.at(0)->getSprite()->getPosition());
	knight.push_back(createKnight);
}

void GamePlayScene::createLayerUI()
{
	_layerUI = Layer::create();
	_layerUI->setPosition(Vec2(2 , 2));
	//log("layerUI contentsize : %f , %f", _layerUI->getContentSize().width, _layerUI->getContentSize().height);
	
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
	for (auto hallTown : newHallTown)
	{
		if (hallTown != nullptr)
		{
			hallTown->Update(dt);
		}
		if (hallTown != nullptr && hallTown->loadingBar == nullptr && createListenerForTownHall == true)
		{
			createListenerForTownHall = false;
			auto listenerTownHall = EventListenerTouchOneByOne::create();
			listenerTownHall->onTouchBegan = [=](Touch *touch, Event *_event)
			{
				if (hallTown->getSprite()->getBoundingBox().containsPoint(touch->getLocation()
					+ camera->getPosition() - Director::getInstance()->getVisibleSize() / 2))
				{
					auto popup = UICustom::PopupTownHall::createAsConfirmDialogue("Town hall", "",
						CC_CALLBACK_0(GamePlayScene::CreateKnight, this));
					_layer2D->addChild(popup);
					return true;
				}
				return false;
			};
			this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTownHall, this);
		}
	}


	// code duoc

	//gameSprite->runAction(mListAction[0]);

//	log("JOYSTIK %f %f", leftJoystick->getVelocity().x, leftJoystick->getVelocity().y);
	//log("velocity %f %f ", leftJoystick->getVelocity().x, leftJoystick->getVelocity().y);
	
	if (leftJoystick->getVelocity().x > 0.866 && leftJoystick->getVelocity().y > -0.5 && leftJoystick->getVelocity().y < 0.5) {
		if (count[0] == 0) {
		
			hero->moveR(1, SPEED, 0);
			hero->setDirect(1);
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

	if (leftJoystick->getVelocity().x == 0.0 && leftJoystick->getVelocity().y == 0.0 ) {
		for (int i = 0; i < 8; i++) {
			count[i] = 0;
		}
	}

	joystickBase->updatePositions(dt);

	//	spriteFocus->setPosition(gameSprite->getPosition().x , gameSprite->getPosition().y +50);
	count_attack += dt;
	if (count_attack > 1.0) {
		heroAttack(hero->getDirect());
		count_attack = 0.0;
	}
	

	
	dot->setVisible(true);
//	dot->setPosition(hero->getPositionHero().x-100, hero->getPositionHero().y+200);
	HandleMinimap();
	count_bullet += dt;
	
	if (count_bullet>0.4 && m_listScoutTowns.size()>0) {
		for (auto a : m_listScoutTowns) {
			if (abs(a->getSprite()->getPositionX() - hero->getSprite()->getPositionX())<200 &&
				abs(a->getSprite()->getPositionY() - hero->getSprite()->getPositionY())<200
				) {
				log("a %f %f", a->getSprite()->getPositionX(), a->getSprite()->getPositionY());
				log("hero %f %f", hero->getSprite()->getPositionX(), hero->getSprite()->getPositionY());
				a->Update(count_bullet, hero);
			}
			

			

		}
		

		count_bullet = 0;
	}
	
	
	
}

void GamePlayScene::heroAttack(int STATE_ATTACK) {
	if (mButtonAttack->getBoundingBox().containsPoint(mCurrentTouch)) {
		hero->getAttack(STATE_ATTACK);
		mCurrentTouch.x+=100;
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
	m_miniMap->setScale(0.7);
	//minimapSprite->setScale(0.3);
	//minimapSprite->setPosition(50*screenSize.width / (2 * 256), 820*screenSize.height  / (2*512));
	m_miniMap->setAnchorPoint(Vec2(0, 0));
	m_miniMap->setPosition(condinatorMiniMap);
	//_layerUI->addChild(minimapSprite,11);
	_layerUI->addChild(m_miniMap, 12);

	map_1 = Sprite::create("map1.png");
	//Sprite*  minimapSprite = Sprite::create("minimap.png");
	map_1->setScale(0.7);
	map_1->setAnchorPoint(Vec2(0, 0));
	//minimapSprite->setScale(0.3);
	//minimapSprite->setPosition(50*screenSize.width / (2 * 256), 820*screenSize.height  / (2*512));
	map_1->setPosition(m_miniMap->getPosition());

	//_layerUI->addChild(minimapSprite,11);
	_layerUI->addChild(map_1, 11);


	dot = Sprite::create("dot.png");
	//Sprite*  minimapSprite = Sprite::create("minimap.png");
	dot->setScale(0.002);
	//minimapSprite->setScale(0.3);
	//minimapSprite->setPosition(50*screenSize.width / (2 * 256), 820*screenSize.height  / (2*512));
	dot->setAnchorPoint(Vec2(0.5, 0.5));
	dot->setPosition(screenSize.width * 0.05 / 2.0, screenSize.height * 9 / 10);
	//_layerUI->addChild(minimapSprite,11);
	_layerUI->addChild(dot, 11);
	dot->setVisible(false);
}

void GamePlayScene::HandleMinimap()
{
	dot->setPosition( (hero->getPositionHero().x/condinatorBigMap.x)*(map_1->getContentSize().height) + condinatorMiniMap.x, ( hero->getPositionHero().y / condinatorBigMap.y)*(m_miniMap->getContentSize().width) + condinatorMiniMap.y);
	
}






void GamePlayScene::AddKnightRed()
{
	for (int i = 0; i < 10; i++)
	{
		Knight *knightRed = new Knight(_layer2D, 2);
		knightRed->getSprite()->setCameraMask(2);
		//this->getContentSize()
		knightRed->SetPositionKnight((Vec2)mapTop->getContentSize() + mapTop->getPosition());
		m_knightRead.push_back(knightRed);
		log("%f %f", _layer2D->getContentSize().width, _layer2D->getContentSize().height);
	}
}



	




