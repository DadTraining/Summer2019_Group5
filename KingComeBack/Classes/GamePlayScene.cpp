#include"GamePlayScene.h"
GamePlayScene::GamePlayScene()
{
}

GamePlayScene::~GamePlayScene()
{
}

Scene * GamePlayScene::createScene()
{

	return GamePlayScene::create();
}

bool GamePlayScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto screenSize = Director::getInstance()->getVisibleSize();
	//add map
	map = TMXTiledMap::create("map.tmx");

	map->setAnchorPoint(Vec2(0, 0));
	map->setPosition(0, 0);

	this->addChild(map, 0);

	// add physic for camera
	// add camera
	this->setCameraMask((unsigned short)CameraFlag::USER1, true);

	camera = Camera::create();
	camera->setPosition(map->getContentSize().width / 2, map->getContentSize().height / 2);

	camera->setCameraFlag(CameraFlag::USER1);
	this->addChild(camera, 1);
	// move camera
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(GamePlayScene::OnTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GamePlayScene::OnTouchMove, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

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
