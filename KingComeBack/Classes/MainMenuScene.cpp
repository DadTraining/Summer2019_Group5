#include "ResourceManager.h"
#include "GameSetting.h"
#include <iostream>
#include "MenuScene.h"
#include "GamePlayScene.h"
#include "MainMenuScene.h"

MainMenuScene::~MainMenuScene()
{
}

Scene * MainMenuScene::createScene()
{
	return MainMenuScene::create();
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

	logo = Sprite::create("Sprites/Logo/cooltext.png");
	logo->setPosition(origin.x + (logo->getContentSize().height*1.5), visibleSize.height - (logo->getContentSize().height / 3));
	logo->setScale(0.5);
	this->addChild(logo, 2);

	//add label for hero 
	lbHero = Label::createWithTTF("General marksmanship is a general type with the ability to fight fights and normal battles", "fonts/arial.ttf", 20);
	lbHero->setPosition(Vec2(visibleSize.width / 2, 6 * visibleSize.height / 7));
	lbHero->setVisible(false);
	this->addChild(lbHero, 5);

	//add itemMarksman
	itemMarksman = ui::Button::create("Sprites/Hero/Assasin.png","Sprites/Hero/Assasin.png");
	itemMarksman->setPosition(Vec2(visibleSize.width / 4, 2*visibleSize.height / 3 - lbHero->getContentSize().height * 2));
	itemMarksman->setAnchorPoint(Point(0.5f,0.5f));
	itemMarksman->setScale(0.5, 0.5);
	itemMarksman->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			//itemMarksman->runAction(scaleTo);
			break;
		case ui::Widget::TouchEventType::ENDED:
			itemMarksman->setScale(0.7, 0.7);
			lbHero->setVisible(true);
			lbWitch->setVisible(false);
			lbStrength->setVisible(false);
			itemWitch->setScale(1.5, 2);
			itemStrength->setScale(1.5, 1.5);
			break;
		default:
			break;
		}
	});
	this->addChild(itemMarksman, 10);

	//add itemWitch
	itemWitch = ui::Button::create("Sprites/Hero/Leona.png", "Sprites/Hero/Leona.png");
	itemWitch->setPosition(Vec2(visibleSize.width / 2, 2*visibleSize.height / 3 - lbHero->getContentSize().height * 2));
	itemWitch->setAnchorPoint(Point(0.5f, 0.5f));
	itemWitch->setScale(1.5, 2);
	itemWitch->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			//itemMarksman->runAction(scaleTo);
			break;
		case ui::Widget::TouchEventType::ENDED:
			//itemMarksman->stopAllActions();	break;
			itemWitch->setScale(2, 2.5);
			lbHero->setVisible(false);
			lbWitch->setVisible(true);
			lbStrength->setVisible(false);
			itemMarksman->setScale(0.5, 0.5);
			itemStrength->setScale(1.5, 1.5);
		default:
			break;
		}
	});
	this->addChild(itemWitch, 10);

	//add label for lbWitch 
	lbWitch = Label::createWithTTF("Power generals with the ability to often dominate", "fonts/arial.ttf", 20);
	lbWitch->setPosition(Vec2(visibleSize.width / 2, 6 * visibleSize.height / 7));
	lbWitch->setVisible(false);
	this->addChild(lbWitch, 6);

	//add lbStrength
	itemStrength = ui::Button::create("Sprites/Hero/Knight.png", "Sprites/Hero/Knight.png");
	itemStrength->setPosition(Vec2(3*visibleSize.width / 4, 2*visibleSize.height / 3 - lbHero ->getContentSize().height*2));
	itemStrength->setAnchorPoint(Point(0.5f, 0.5f));
	itemStrength->setScale(1.5, 1.5);
	itemStrength->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			//itemMarksman->runAction(scaleTo);
			break;
		case ui::Widget::TouchEventType::ENDED:
			//itemMarksman->stopAllActions();	break;
			itemWitch->setScale(1.5, 2);
			itemMarksman->setScale(0.5, 0.5);
			itemStrength->setScale(2, 2);
			lbHero->setVisible(false);
			lbWitch->setVisible(false);
			lbStrength->setVisible(true);
		default:
			break;
		}
	});
	this->addChild(itemStrength, 10);

	//add label for lbStrength 
	lbStrength = Label::createWithTTF("Power generals with the ability to often dominate", "fonts/arial.ttf", 20);
	lbStrength->setPosition(Vec2(visibleSize.width / 2, 6 * visibleSize.height / 7));
	lbStrength->setVisible(false);
	this->addChild(lbStrength, 7);
	
	//add text file input name
	textName = ui::TextField::create("Enter Your Name", "fonts/arial.ttf", 30);
	textName->setPasswordEnabled(false);
	textName->setTouchEnabled(true);
	textName->setMaxLengthEnabled(true);
	textName->setMaxLength(10);
	textName->setAnchorPoint(Point(0.5f, 0.5f));
	textName->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
	textName->addEventListener([](Ref* node, ui::TextField::EventType event)
	{
		if (event == ui::TextField::EventType::INSERT_TEXT)
		{
			CCLOG("Hell breaks lose! Text was inserted!");
		}
	});
	
	this->addChild(textName, 10);

	//add button back menu
	/*btnBack = ui::Button::create("Buttons/pngguru.com-id-bixpo_04.png", "Buttons/pngguru.com-id-bixpo_08.png");
	btnBack->setPosition(Vec2(70,70));
	btnBack->setAnchorPoint(Point(0.5, 0.5));
	btnBack->setScale(0.5);
	btnBack->addClickEventListener([](Ref* event) {
		SimpleAudioEngine::getInstance()->playEffect("Sound/confirm.wav");

		Director::getInstance()->replaceScene(MenuScene::createScene());
	});
	addChild(btnBack);*/

	btnPlay = ui::Button::create("Buttons/play.png","Buttons/play_pro.png", "Buttons/play.png");

	btnPlay->setTitleText(" Play ");
	btnPlay->setTitleFontName("fonts/arial.ttf");
	btnPlay->setTitleFontSize(18);
	btnPlay->setScale(1, 2);
	btnPlay->setPosition(Vec2(visibleSize.width / 2, textName->getPosition().y-textName->getContentSize().height*2));
	btnPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			if (GameSetting::getIntance()->isEnableSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sound/confirm.wav");
			}
			if (textName->getMaxLength() != 0)
			{
				Director::getInstance()->replaceScene(GamePlayScene::createScene());
			}
			break;
		default:
			break;
		}
	});
	this->addChild(btnPlay,2);


	return true;
}



