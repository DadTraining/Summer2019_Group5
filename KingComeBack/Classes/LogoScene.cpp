#include "LogoScene.h"
#include "LoadingScene.h"

LogoScene::LogoScene()
{
}

LogoScene::~LogoScene()
{
}

Scene * LogoScene::createScene()
{
	return LogoScene::create();
}

bool LogoScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	logoScene = Sprite::create("Loading/logo.png");
	logoScene->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	logoScene->setScale( visibleSize.width / logoScene->getContentSize().width,
		visibleSize.height / logoScene->getContentSize().height );
	logoScene->removeFromParent();
	this->addChild(logoScene, -1);

	auto lbLoadingLogo = Label::createWithTTF("Loading ...", "Fonts/arial.ttf", 36);

		
	auto gotoNext = CallFunc::create([]() {

		Director::getInstance()->replaceScene(LoadingScene::createScene());

	});

	auto sequence = Sequence::create(DelayTime::create(3), gotoNext,
		nullptr);

	runAction(sequence);
	return true;
}
