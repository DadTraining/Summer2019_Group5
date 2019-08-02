#include "LoadingScene.h"
#include "MenuScene.h"
#include "GameSetting.h"

LoadingScene::LoadingScene()
{

}

LoadingScene::~LoadingScene()
{

}

bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Add background
	background = Sprite::create("Loading/backgroundLoading.png");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	background->setScale(visibleSize.width / background->getContentSize().width,
		visibleSize.height / background->getContentSize().height);
	background->removeFromParent();
	this->addChild(background, -10);

	// Add Label
	/*lbNameGame = Label::createWithTTF(" KING COMEBACK ", "Fonts/arial.ttf", 100);
	lbNameGame->setPosition(Vec2(origin.x + visibleSize.width / 2,2*visibleSize.height/3));
	lbNameGame->setBMFontSize(60);
	lbNameGame->setColor(Color3B::RED);
	//lbNameGame->setOpacity(1);
	// add the label as a child to this scene
	this->addChild(lbNameGame, 10);*/

	// add loading bar 
	//add loading bar nomal
	loadingBar = Sprite::create("Sprites/Loading/loading.png");
	loadingBar->setPosition(visibleSize.width / 2, visibleSize.height / 7);
	loadingBar->setScaleX(3);
	loadingBar->setScaleY(0.1);
	loadingBar->setColor(Color3B::WHITE);
	loadingBar->setOpacity(60);
	this->addChild(loadingBar, 1);

	// add loading press
	loadingPress = Sprite::create("Sprites/Loading/progress1.png");
	loadingPress->setAnchorPoint(Vec2(0, 0.5));
	loadingPress->setPosition(visibleSize.width / 2 - loadingPress->getContentSize().width / 2 -loadingPress->getContentSize().width,  visibleSize.height / 7);
		this -> addChild(loadingPress, 1);
		//loadingPress->setOpacity(10);

	/*lbLoading = Label::createWithTTF("loading...", "fonts/Marker Felt.ttf", 20);
	lbLoading->setAnchorPoint(Vec2(0.5, 0.5));
	lbLoading->setPosition(Vec2(visibleSize.width / 2 - lbLoading->getContentSize().width/2,
		visibleSize.height / 7));
	//lbLoading->setScaleX(2);
	this->addChild(lbLoading, 1);*/

	this->scheduleUpdate();

	if (GameSetting::getIntance()->isEnableMusic())
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/EpicLegend-AuracleMusic_bds5.mp3", true);
	}

	return true;
}

Scene* LoadingScene::createScene()
{
	return LoadingScene::create();
}

void LoadingScene::update(float detaTime)
{
	scale += 0.01;
	loadingPress->setScale(scale, 0.1);
	if (scale >= 3)
	{
		this->unscheduleUpdate();
		Director::getInstance()->replaceScene(MenuScene::createScene());
	}
}