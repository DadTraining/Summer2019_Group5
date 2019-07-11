#include"GamePlayScene.h"


GamePlayScene::GamePlayScene()
{
}

GamePlayScene::~GamePlayScene()
{
}

Scene * GamePlayScene::createScene()
{
	//auto scene = GamePlayScene::create();
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
	screenSize = Director::getInstance()->getVisibleSize();
	sizeWall = Vec2(3.0f, 3.0f);
	//add map
	this->AddMap();

	//Add listener
	this->AddListener();

	// add layer 
	this->createLayerUI();

	//Add joystick
	this->AddJoystick();

	MyGLView = Director::getInstance()->getOpenGLView();


	// add camera
	this->AddCamera();

	//this->scheduleUpdate();

	return true;
}

bool GamePlayScene::OnTouchBegan(Touch * touch, Event * unused_event)
{
	//if (camera->getPositionX() >= screenSize.width / 2 + map->getPositionX()
	//	&& camera->getPositionY() >= screenSize.height / 2 + map->getPositionY()
	//	&& camera->getPositionX() <= map->getContentSize().width - screenSize.width / 2
	//	&& camera->getPositionY() <= map->getContentSize().height - screenSize.height / 2)
	//{
	//	Vec2 moveCamera = touch->getLocation() - touch->getPreviousLocation() + camera->getPosition();
	//	camera->setPosition(moveCamera);
	//	layerUI->setPosition(camera->getPosition());//camera->getPosition() - (map->getContentSize() - screenSize) / 2);
	//}

	return true;
}

void GamePlayScene::OnTouchMove(Touch * touch, Event * unused_event)
{
	if (camera->getPositionX() >= screenSize.width / 2 + map->getPositionX()
		&& camera->getPositionY() >= screenSize.height / 2 + map->getPositionY()
		&& camera->getPositionX() <= map->getContentSize().width - screenSize.width / 2
		&& camera->getPositionY() <= map->getContentSize().height - screenSize.height / 2)
	{
		Vec2 moveCamera = touch->getLocation() - touch->getPreviousLocation() + camera->getPosition();
		camera->setPosition(moveCamera);

		layerUI->setPosition(camera->getPosition()); //(map->getContentSize() - screenSize) / 2);
	}
	// 
	//-touch->getPreviousLocation() + Director::getInstance()->getRunningScene()->getDefaultCamera()->getPosition()

	//Director::getInstance()->getRunningScene()->getDefaultCamera()->setPosition(touch->getLocation());
}

void GamePlayScene::OnTouchEnd(Touch * touch, Event * unused_event)
{

}

bool GamePlayScene::OnContactBegin(PhysicsContact & contact)
{
	auto spriteA = contact.getShapeA()->getBody();
	auto spriteB = contact.getShapeB()->getBody();

	// camera with map
	if ((spriteA->getCollisionBitmask() == BITMASK_MAP && spriteB->getCollisionBitmask() == BITMASK_CAMERA)
		|| (spriteA->getCollisionBitmask() == BITMASK_CAMERA && spriteB->getCollisionBitmask() == BITMASK_MAP))
	{

	}
	return true;
}

void GamePlayScene::AddMap()
{
	map = TMXTiledMap::create("map.tmx");

	map->setAnchorPoint(Vec2(0, 0));
	map->setVisible(false);

	map->setPosition(0, 0);

	// add physic for map

	auto sizeMap = map->getContentSize();

	auto physicBody = PhysicsBody::createEdgeBox(sizeMap,
		PHYSICSBODY_MATERIAL_DEFAULT, 2);
	physicBody->setDynamic(false);
	physicBody->setCollisionBitmask(101);
	physicBody->setContactTestBitmask(true);

	map->setPhysicsBody(physicBody);

	this->addChild(map, indexMap);
}

void GamePlayScene::AddCamera()
{
	this->setCameraMask((unsigned short)CameraFlag::DEFAULT, false);
	this->setCameraMask((unsigned short)CameraFlag::USER1, true);

	camera = Camera::create();
	camera->setPosition(map->getPosition() + screenSize / 2);
	camera->setAnchorPoint(Vec2(0.5, 0.5));
	camera->setCameraFlag(CameraFlag::USER1);

	Size size = Director::getInstance()->getOpenGLView()->getVisibleSize();

	auto physicBody = PhysicsBody::createBox(screenSize,
		PHYSICSBODY_MATERIAL_DEFAULT);

	physicBody->setCollisionBitmask(BITMASK_CAMERA);
	physicBody->setContactTestBitmask(true);
	physicBody->setGravityEnable(false);
	physicBody->setRotationEnable(false);
	physicBody->setDynamic(true);

	camera->setPhysicsBody(physicBody);

	this->addChild(camera, indexCamera);
}

void GamePlayScene::AddListener()
{
	// add listen touch
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GamePlayScene::OnTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GamePlayScene::OnTouchMove, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// add listen contact
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GamePlayScene::OnContactBegin, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}
void GamePlayScene::AddJoystick()
{
	Rect joystickBaseDimensions;
	joystickBaseDimensions = Rect(0, 0, 160.0f, 160.0f);

	Point joystickBasePosition;
	joystickBasePosition = Point(screenSize.width / 9, screenSize.height / 6);

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
	layerUI->addChild(joystickBase, indexJoystick);
}

void GamePlayScene::AddButton()
{

}

void GamePlayScene::createLayerUI()
{
	layerUI = Layer::create();
	Size size = layerUI->getContentSize();

	//layerUI->setScale(0.5);
	layerUI->setAnchorPoint(Vec2::ZERO);
	//layerUI->setPosition(map->getPosition());
	this->addChild(layerUI, indexLayerUI);

	auto sprite = Sprite::create("UI.png");
	sprite->setAnchorPoint(Vec2(0 , 0));
	sprite->setPosition(layerUI->getPosition());
	layerUI->addChild(sprite, 3);
}

void GamePlayScene::update(float dt)
{
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
	//joystickBase->updatePositions(dt);
}


