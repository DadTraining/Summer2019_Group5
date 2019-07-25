#include "MenuScene.h"
#include "SettingScene.h"
#include "MainMenuScene.h"
#include "GameSetting.h"
#include "GamePlayScene.h"

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}

Scene * MenuScene::createScene()
{
	return MenuScene::create();
}

bool MenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//add back ground 
	background = Sprite::create("Loading/backgroupMenu.png");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	background->setScale( visibleSize.width / background->getContentSize().width,
		 visibleSize.height /background->getContentSize().height );
	background->removeFromParent();
	this->addChild(background, -10);

	//add logo game

	logo = Sprite::create("Loading/logoName.png");
	logo->setPosition(origin.x +(logo->getContentSize().height/1.2),visibleSize.height -(logo->getContentSize().height/3));
	logo->setScale(0.5);
	this->addChild(logo, 2);

	// add menu
	btnMenu = ui::Button::create("Loading/menuMain.png", "Loading/menuMain.png");

	btnMenu->setTitleText(" Menu ");
	btnMenu->setTitleFontName("Fonts/arial.ttf");
	btnMenu->setTitleFontSize(50);
	btnMenu->setScale(1,0.5);
	btnMenu->setPosition(Vec2(3 * visibleSize.width / 4,  visibleSize.height - btnMenu->getContentSize().height/4));
	this->addChild(btnMenu, 1);

	// add buton Play
	btnPlay = ui::Button::create("Buttons/king_buton.png","Buttons/king_buton.png");

	btnPlay->setTitleText(" New Game ");
	btnPlay->setTitleFontName("Fonts/arial.ttf");
	btnPlay->setTitleFontSize(20);
	btnPlay->setScale(1.5,1.5);
	btnPlay->setPosition(Vec2(3*visibleSize.width / 4, 2* visibleSize.height / 3- btnPlay ->getContentSize().height/2));
	btnPlay->addTouchEventListener([&](Ref* sender,ui::Widget::TouchEventType type)
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
			btnPlay->setOpacity(100);
			Director::getInstance()->replaceScene(GamePlayScene::createScene());
			break;
		default:
			break;
		}
	});

	this->addChild(btnPlay,1);

	// add buton restart
	btnAgainPlay = ui::Button::create("Buttons/king_buton.png", "Buttons/king_buton.png");

	btnAgainPlay->setTitleText(" Restart ");
	btnAgainPlay->setTitleFontName("Fonts/arial.ttf");
	btnAgainPlay->setTitleFontSize(20);
	btnAgainPlay->setScale(1.5,1.5);
	btnAgainPlay->setPosition(Vec2(3*visibleSize.width / 4, btnPlay->getPositionY() - btnPlay->getContentSize().height - btnPlay->getContentSize().height/1.5));
	btnAgainPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			// chuyen sang trang dang nhap
			if (GameSetting::getIntance()->isEnableSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sound/confirm.wav");
			}
			break;
		default:
			break;
		}
	});

	this->addChild(btnAgainPlay, 1);

	//add button setting
	btnSetting = ui::Button::create("Buttons/king_buton.png", "Buttons/king_buton.png");

	btnSetting->setTitleText(" Setting ");
	btnSetting->setTitleFontName("Fonts/arial.ttf");
	btnSetting->setTitleFontSize(20);
	btnSetting->setScale(1.5,1.5);
	btnSetting->setPosition(Vec2(3*visibleSize.width / 4, btnAgainPlay->getPositionY()-btnAgainPlay->getContentSize().height - btnSetting->getContentSize().height/1.5));
	btnSetting->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			//auto fadeOut = FadeOut::create(2.0f);
			if (GameSetting::getIntance()->isEnableSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sound/confirm.wav");
			}
			btnSetting->setOpacity(100);
			Director::getInstance()->replaceScene(SettingScene::createScene());
			break;
		
		}
	});

	this->addChild(btnSetting, 1);

	//add button exit
	btnExit = ui::Button::create("Buttons/king_buton.png", "Buttons/king_buton.png");

	btnExit->setTitleText(" Exit ");
	btnExit->setTitleFontName("Fonts/arial.ttf");
	btnExit->setTitleFontSize(20);
	btnExit->setScale(1.5,1.5);
	btnExit->setPosition(Vec2(3*visibleSize.width / 4, btnSetting->getPositionY() - btnSetting->getContentSize().height - btnExit->getContentSize().height/1.5));
	btnExit->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
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
			Director::getInstance()->end();
			break;
		default:
			break;
		}
	});

	this->addChild(btnExit, 1);

	if (GameSetting::getIntance()->isEnableMusic())
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/CallForHeroes-ShockwaveSound_w9ht.mp3", true);
	}

	return true;
}
