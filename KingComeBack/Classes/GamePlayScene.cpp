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
	this->setCameraMask((unsigned short)CameraFlag::DEFAULT, true);
	this->setCameraMask((unsigned short)CameraFlag::USER1, true);
	//winSize = Director::getInstance()->getWinSize();

	//Create Layer for map and camera
	this->createLayer2D();

	// add camera
	this->AddCameraUSER1();

	//add map
	this->AddMap();

	//Add listener
	this->AddListener();

	//Add camera User 2
	this->AddCameraUSER2();

	// add layer 
	this->createLayerUI();

	_layer2D->setCameraMask(2);

	//this->scheduleUpdate();
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
	//if (camera->getPositionX() >= screenSize.width / 2 + map->getPositionX()
	//	&& camera->getPositionY() >= screenSize.height / 2 + map->getPositionY()
	//	&& camera->getPositionX() <= map->getContentSize().width - screenSize.width / 2
	//	&& camera->getPositionY() <= map->getContentSize().height - screenSize.height / 2)
	//{
	//	Vec2 moveCamera = touch->getLocation() - touch->getPreviousLocation() + camera->getPosition();
	//	camera->setPosition(moveCamera);
	//	layerUI->setPosition(camera->getPosition());//camera->getPosition() - (map->getContentSize() - screenSize) / 2);
	//}
	//if (moveOutBackground)
	log("touch position : %f, %f", touch->getLocation().x, touch->getLocation().y);
	return true;
}

void GamePlayScene::OnTouchMove(Touch * touch, Event * unused_event)
{

	Vec2 touchLocation = touch->getLocation();
	Point newPos = touch->getPreviousLocation() - touch->getLocation();

	Vec3 cameraForward;
	Vec3 cameraDownDir;
	Vec3 cameraRightDir;

	camera->getNodeToWorldTransform().getForwardVector(&cameraForward);
	cameraForward.normalize();
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

	//layerUI->setPosition3D(cameraPos);
	
	/*	if (camera->getPositionX() >= screenSize.width / 2 + map->getPositionX()
		&& camera->getPositionY() >= screenSize.height / 2 + map->getPositionY()
		&& camera->getPositionX() <= map->getContentSize().width - screenSize.width / 2
		&& camera->getPositionY() <= map->getContentSize().height - screenSize.height / 2*/
	/*{
		Vec2 moveCamera = touch->getLocation() - touch->getPreviousLocation() + camera->getPosition();

		layerUI->setPosition(touch->getLocation() - touch->getPreviousLocation() + layerUI->getPosition());
		
		log("Layer Position : %f, %f", layerUI->getPosition().x, layerUI->getPosition().y);
		log("Camera Position: %f, %f", camera->getPosition().x, camera->getPosition().y);
		log("joystick position: %f, %f", leftJoystick->getPositionX(), leftJoystick->getPositionY());
		log("joystickBase postion: %f, %f", joystickBase->getPositionX(), joystickBase->getPositionY());
	}*/
	
}

void GamePlayScene::OnTouchEnd(Touch * touch, Event * unused_event)
{
	moveOutBackground = true;
}

bool GamePlayScene::OnContactBegin(PhysicsContact & contact)
{
	auto spriteA = contact.getShapeA()->getBody();
	auto spriteB = contact.getShapeB()->getBody();

	int a = spriteA->getCollisionBitmask();
	int b = spriteB->getCollisionBitmask();
	// camera with map
	if ((spriteA->getCollisionBitmask() == BITMASK_MAP && spriteB->getCollisionBitmask() == BITMASK_LAYER_UI)
		|| (spriteA->getCollisionBitmask() == BITMASK_LAYER_UI && spriteB->getCollisionBitmask() == BITMASK_MAP))
	{
		//moveOutBackground = false;
	}
	return true;
}

void GamePlayScene::AddMap()
{
	map = TMXTiledMap::create("map.tmx");

	map->setAnchorPoint(Vec2(0, 0));
	//map->setVisible(false);

	map->setPosition(this->getPosition());

	// add physic for map

	auto sizeMap = map->getContentSize();

	auto physicBody = PhysicsBody::createEdgeBox(sizeMap,
		PHYSICSBODY_MATERIAL_DEFAULT, 2);
	physicBody->setDynamic(false);
	physicBody->setCollisionBitmask(BITMASK_MAP);
	physicBody->setContactTestBitmask(true);

	map->setPhysicsBody(physicBody);

	_layer2D->addChild(map);
}

void GamePlayScene::AddCameraUSER1()
{
	camera = Camera::create();

	//camera->setPosition();
	camera->setCameraFlag(CameraFlag::USER1);

	_layer2D->addChild(camera);
	
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

	// add listen contact
	//auto contactListener = EventListenerPhysicsContact::create();
	//contactListener->onContactBegin = CC_CALLBACK_1(GamePlayScene::OnContactBegin, this);
	//this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}
void GamePlayScene::AddJoystick()
{
	Size s = Director::getInstance()->getWinSize();
	Rect joystickBaseDimensions;
	joystickBaseDimensions = Rect(0, 0, 160.0f, 160.0f);

	Point joystickBasePosition;
	joystickBasePosition = Point(screenSize.width / 9, screenSize.height / 7);//Point(layerUI->getPosition() - screenSize * 3 / 8);

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
	this->addChild(joystickBase, 10);
}

void GamePlayScene::AddButton()
{

}

void GamePlayScene::AddSpriteUI()
{
	auto containerForSpriteUI = Node::create();
	auto sprite = Sprite::create("UI.png");
	sprite->setPosition(screenSize / 2);
	containerForSpriteUI->addChild(sprite);
	layerUI->addChild(containerForSpriteUI, 10);
	//containerForSpriteUI->setCameraMask(4);
}

void GamePlayScene::createLayerUI()
{
	layerUI = Layer::create();
	layerUI->setPosition(Vec2(0 , 0));
	log("Layer Position : %f, %f", layerUI->getPosition().x, layerUI->getPosition().y);
	log("Layer ContentSize: %f, %f", layerUI->getContentSize().width, layerUI->getContentSize().height);
	auto physicBody = PhysicsBody::createBox(screenSize,
		PHYSICSBODY_MATERIAL_DEFAULT);

	physicBody->setCollisionBitmask(BITMASK_LAYER_UI);
	physicBody->setContactTestBitmask(true);
	physicBody->setGravityEnable(false);
	physicBody->setRotationEnable(false);
	physicBody->setDynamic(true);

	//layerUI->setPhysicsBody(physicBody);

	this->addChild(layerUI, 10);

	//Add sprite UI;
	this->AddSpriteUI();

	//Add joystick
	this->AddJoystick();
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

//void CollisionMapCamera()
//{
//
//	if ()
//}
