#include "MainMenuScene.h"
#include "ResourceManager.h"

int MainMenuScene::id = 0;

MainMenuScene::~MainMenuScene()
{
}

MainMenuScene::MainMenuScene()
{
}

bool MainMenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto frames1 = Sprite::create("/Buttons/hero/pngguru.com-id-nafyj_01.png");
	frames1->setScale(0.5);

	heroLeft = ui::Button::create("/Buttons/hero/Assasin_01.png", "/Buttons/hero/Assasin_01.png");
	//heroLeft->setScale(0.5);
	heroLeft->setSize(Size(heroLeft->getContentSize().width/10, heroLeft->getContentSize().height/10));
	heroLeft->setPosition(Vec2( visibleSize.width / 3, 2*visibleSize.height/3));
	heroLeft->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			//auto fadeOut = FadeOut::create(2.0f);
			heroLeft->setOpacity(100);
			MainMenuScene::id = 1;
			break;

		}
	});
	frames1->setPosition(heroLeft->getPosition());
	addChild(frames1,1);
	addChild(heroLeft,5);

	//add hero center

	auto frames2 = Sprite::create("/Buttons/hero/pngguru.com-id-nafyj_01.png");
	frames2->setScale(0.5);

	heroCenter = ui::Button::create("/Buttons/hero/Leona_01.png", "/Buttons/hero/Leona_01.png");
	heroCenter->setContentSize(Size(145, 221));
	//heroLeft->setTitleText(" Setting ");
	//heroLeft->setScale(2, 1.5);
	heroCenter->setPosition(Vec2(heroLeft->getPositionX() + heroLeft->getContentSize().width + 32,2* visibleSize.height / 3));
	heroCenter->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			auto fadeOut = FadeOut::create(2.0f);
			heroCenter->setOpacity(100);
			MainMenuScene::id = 2;
			break;

		}
	});
	frames2->setPosition(heroCenter->getPosition());
	addChild(frames2, 1);
	addChild(heroCenter,5);

	//add hero right

	auto frames3 = Sprite::create("/Buttons/hero/pngguru.com-id-nafyj_01.png");
	frames3->setScale(0.5);

	heroRight = ui::Button::create("/Buttons/hero/Knight.png", "/Buttons/hero/Knight.png");
	//heroRight->setSize(Size(145, 221));
	//heroLeft->setTitleText(" Setting ");
	//heroLeft->setScale(2, 1.5);
	heroRight->setSize(Size(heroRight->getContentSize().width*4.0f, heroRight->getContentSize().height*1.2f));
	heroRight->setPosition(Vec2(heroCenter->getPositionX() + heroCenter->getContentSize().width + 32,2* visibleSize.height / 3));
	heroRight->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			auto fadeOut = FadeOut::create(2.0f);
			heroRight->setOpacity(100);
			MainMenuScene::id = 3;
			break;

		}
	});
	frames3->setPosition(heroRight->getPosition());
	addChild(frames3, 1);
	addChild(heroRight,5);

	return true;
}

cocos2d::Scene * MainMenuScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MainMenuScene::create();

	scene->addChild(layer);

	return scene;
}
