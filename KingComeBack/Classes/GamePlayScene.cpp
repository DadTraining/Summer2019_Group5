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

	//Add move camera
	this->MoveCamera();

	return true;
}

bool GamePlayScene::OnTouchBegan(Touch * touch, Event * unused_event)
{
	return true;
}

void GamePlayScene::OnTouchMove(Touch * touch, Event * unused_event)
{
	touchLocation = touch->getLocation();

	camera->setPosition(touchLocation);
}

void GamePlayScene::AddMap()
{
	map = TMXTiledMap::create("map.tmx");

	map->setAnchorPoint(Vec2(0, 0));
	map->setPosition(0, 0);
	this->addChild(map);

	// add physic for map

	auto sizeMap = map->getContentSize();

	auto physicBody = PhysicsBody::createEdgeBox(sizeMap,
		PHYSICSBODY_MATERIAL_DEFAULT, 3);
	physicBody->setCollisionBitmask(100);
	physicBody->setContactTestBitmask(true);
	physicBody->getShape(0)->setRestitution(5);
	physicBody->getShape(0)->setDensity(50.0f);

	auto node = Node::create();
	node->setPosition(Vec2(sizeMap.width /2, sizeMap.height / 2));
	node->setPhysicsBody(physicBody);
	this->addChild(node);
}

void GamePlayScene::AddCamera()
{
	this->setCameraMask((unsigned short)CameraFlag::USER1, true);

	camera = Camera::create();
	camera->setPosition(map->getContentSize().width / 2, map->getContentSize().height / 2);

	camera->setCameraFlag(CameraFlag::USER1);

	auto physicBody = PhysicsBody::createBox(screenSize, 
		PHYSICSBODY_MATERIAL_DEFAULT);
	physicBody->setCollisionBitmask(101);
	physicBody->setContactTestBitmask(true);
	physicBody->setGravityEnable(false);
	physicBody->setRotationEnable(false);
	physicBody->setMass(50);

	camera->setPhysicsBody(physicBody);

	this->addChild(camera);
}

void GamePlayScene::AddPhysicWall(float _positionX, float _positionY,
	const float &_width, const float &_height)
{
	Size sizeBox = Size(ccp(_width, _height));

	auto spWall = Sprite::create();
	spWall->setPosition(Vec2(_positionX, _positionY));
	auto bodyMap = PhysicsBody::createBox(sizeBox, PHYSICSBODY_MATERIAL_DEFAULT);
	bodyMap->getShape(0)->setRestitution(1.0f);
	bodyMap->getShape(0)->setFriction(0.0f);
	bodyMap->getShape(0)->setDensity(1.0f);
	bodyMap->setGravityEnable(false);
	bodyMap->setDynamic(false);

	spWall->setPhysicsBody(bodyMap);
	spWall->addChild(spWall);
}

void GamePlayScene::AddPhysicCamera()
{
	auto bodyCamera = PhysicsBody::createEdgeBox(screenSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

	camera->addComponent(bodyCamera);

	this->addChild(camera, 3);

}

void GamePlayScene::MoveCamera()
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(GamePlayScene::OnTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GamePlayScene::OnTouchMove, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
