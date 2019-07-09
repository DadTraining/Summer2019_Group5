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
	auto map = TMXTiledMap::create("map.tmx");

	map->setAnchorPoint(Vec2(0, 0));
	map->setVisible(true);
	map->setPosition(0, 0);
	map->setScale(1.2);
	this->addChild(map, 5);
	//add camera
	//auto camera = Camera::create();
	//camera->setPosition(map->getContentSize().;
	//this->addChild(camera, 1);

	return true;
}
