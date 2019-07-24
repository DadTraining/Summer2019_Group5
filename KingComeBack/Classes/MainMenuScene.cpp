#include "MainMenuScene.h"
#include "ResourceManager.h"
#include "GameSetting.h"

MainMenuScene::~MainMenuScene()
{
}

MainMenuScene::MainMenuScene()
{
}

bool MainMenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//add back ground 
	background = Sprite::create("Loading/rsz_background_bb.png");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	background->setScale(visibleSize.width / background->getContentSize().width,
		visibleSize.height / background->getContentSize().height);
	background->removeFromParent();
	this->addChild(background, -10);

	//add logo game

	logo = Sprite::create("Loading/logoName.png");
	logo->setPosition(origin.x + (logo->getContentSize().height / 1.2), visibleSize.height - (logo->getContentSize().height / 3));
	logo->setScale(0.5);
	this->addChild(logo, 2);

	//add label for hero 
	lbHero = Label::createWithTTF("", "Fonts/arial.ttf", 20);
	lbHero->setVisible(false);
	this->addChild(lbHero, 1);

	AddListener();

	//add button hero thiện xạ
	itemMarksman = Sprite::create("Loading/walk_70000.png");
	itemMarksman->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	itemMarksman->setScale(2);
	this->addChild(itemMarksman,2);

	scheduleUpdate();
	return true;
}
void MainMenuScene::update(float dt)
{
	heroAnimation(1);
}
bool MainMenuScene::OnTouchBegan(Touch * touch, Event * unused_event)
{
	mCurrentTouch.x = touch->getLocation().x;
	mCurrentTouch.y = touch->getLocation().y;
	return true;
}
void MainMenuScene::OnTouchMove(Touch * touch, Event * unused_event)
{
}
void MainMenuScene::OnTouchEnd(Touch * touch, Event * unused_event)
{
	
}
void MainMenuScene::AddListener()
{
	// add listen touch
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MainMenuScene::OnTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MainMenuScene::OnTouchMove, this);
	listener->onTouchEnded = CC_CALLBACK_2(MainMenuScene::OnTouchEnd, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void MainMenuScene::heroAnimation(int)
{
	if (itemMarksman->getBoundingBox().containsPoint(mCurrentTouch)) {
		createani();
		mCurrentTouch.x++;
		
	}
}
void MainMenuScene::createani()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Loading/menuHero1.plist", "Loading/menuHero1.png");

	//lbHero->setVisible(true);
	const int numberSprite = 8;
	const int maxWord = 50;

	Vector<SpriteFrame*> animFrames;
	//animFrames.reserve(numberSprite);
	
	

	for (int index = 0; index < numberSprite; index++)
	{
		std::string str = "walk_7000";
		char spritesFramByName[maxWord] = { 0 };
		sprintf(spritesFramByName, "%d.png", index);
		str = str + spritesFramByName;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);

		animFrames.pushBack(frame);
	}


	animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
	Animate* animate = Animate::create(animation);
	itemMarksman->runAction(RepeatForever::create(animate));
}
Scene * MainMenuScene::createScene()
{
	return MainMenuScene::create();
}
