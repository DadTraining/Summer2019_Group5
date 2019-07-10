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

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = GamePlayScene::create();
	scene->addChild(layer, 0);
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

	// add camera
	this->AddCamera();

	//Add listener
	this->AddListener();

	return true;
}

bool GamePlayScene::OnTouchBegan(Touch * touch, Event * unused_event)
{
	touchLocation[0] = touch->getLocation();
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

	this->addChild(map);
}

void GamePlayScene::AddCamera()
{
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

	this->addChild(camera);
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



