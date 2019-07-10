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
	//this->createLayerUI();

	//Add joystick
	this->AddJoystick();

	// add camera
	this->AddCamera();


	return true;
}

bool GamePlayScene::OnTouchBegan(Touch * touch, Event * unused_event)
{
	if (map->getBoundingBox().containsPoint(touch->getLocation()))
	{
		return true;
	}
	return false;
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
	}

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
	map->setPosition(0, 0);

	// add physic for map

	auto sizeMap = map->getContentSize();

	auto physicBody = PhysicsBody::createEdgeBox(sizeMap,
		PHYSICSBODY_MATERIAL_DEFAULT, 2);
	physicBody->setDynamic(false);
	physicBody->setCollisionBitmask(BITMASK_MAP);
	physicBody->setContactTestBitmask(true);

	map->setPhysicsBody(physicBody);

	this->addChild(map, indexMap);
}

void GamePlayScene::AddCamera()
{
	this->setCameraMask((unsigned short)CameraFlag::DEFAULT, false);
	this->setCameraMask((unsigned short)CameraFlag::USER1, true);

	camera = Camera::create();
	camera->setPosition(map->getContentSize().width / 2, map->getContentSize().height / 2);
	camera->setAnchorPoint(Vec2(0.5, 0.5));
	camera->setCameraFlag(CameraFlag::USER1);
	
	int a = this->getCameras().size();
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
	joystickBasePosition = Vec2(screenSize.width * 0.2f, screenSize.height*0.2f);

	SneakyJoystickSkinnedBase *joystickBase = new SneakyJoystickSkinnedBase();
	joystickBase->init();
	joystickBase->setPosition(joystickBasePosition);

	joystickBase->setBackgroundSprite(Sprite::create("res/joystick-back.png"));
	joystickBase->setThumbSprite(Sprite::create("res/stick.png"));

	SneakyJoystick *aJoystick = new SneakyJoystick();
	aJoystick->initWithRect(joystickBaseDimensions);

	aJoystick->autorelease();
	joystickBase->setJoystick(aJoystick);
	joystickBase->setPosition(joystickBasePosition);

	leftJoystick = joystickBase->getJoystick();
	leftJoystick->retain();
	this->addChild(joystickBase, indexJoystick);
}

void GamePlayScene::AddButton()
{

}

void GamePlayScene::createLayerUI()
{

}

//void GamePlayScene::update(float dt)
//{
//	
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
//}


