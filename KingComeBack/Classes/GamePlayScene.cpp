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
	screenSize = Director::getInstance()->getVisibleSize();
	sizeWall = Vec2(3.0f, 3.0f);

	this->setCameraMask((unsigned short)CameraFlag::DEFAULT, true);
	this->setCameraMask((unsigned short)CameraFlag::USER1, true);

	//Create Layer for map and camera
	this->createLayer2D();

	//add map
	this->AddMap();

	// add camera
	this->AddCameraUSER1();

	//Add listener
	this->AddListener();

	//Add camera User 2
	this->AddCameraUSER2();

	// add layer 
	this->createLayerUI();

	this->AddButtonPopUpHero();

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

	map->setPosition(this->getPosition());

	// add physic for map

	auto sizeMap = map->getContentSize();

	auto physicBody = PhysicsBody::createEdgeBox(sizeMap,
		PHYSICSBODY_MATERIAL_DEFAULT, 1);
	physicBody->setDynamic(false);
	physicBody->setCollisionBitmask(BITMASK_MAP);
	physicBody->setContactTestBitmask(true);

	map->setPhysicsBody(physicBody);

	_layer2D->addChild(map);
}

void GamePlayScene::AddCameraUSER1()
{
	camera = Camera::create();
	camera->setCameraFlag(CameraFlag::USER1);

	auto physicBody = PhysicsBody::createBox(screenSize,
		PHYSICSBODY_MATERIAL_DEFAULT);

	physicBody->setCollisionBitmask(BITMASK_LAYER_UI);
	physicBody->setContactTestBitmask(true);
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
	auto button = ui::Button::create("CloseNormal.png", "CloseSelected.png");
	//button->setTitleText("Button text");
	button->setPosition(Vec2(screenSize.width / 1.6, screenSize.height / 9));
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
	auto popUpHero = UICustom::Popup::createAsConfirmDialogue("", "", [=]() {
		auto sprite = Sprite::create("Popup.png");
		sprite->setScale(1.5);
		sprite->setPosition(screenSize / 2);
		sprite->setCameraMask((unsigned short)CameraFlag::USER2);
		_layerUI->addChild(sprite, 10);
	});
	_layerUI->addChild(popUpHero, 10);
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
//	joystickBase->updatePositions(dt);
//}
