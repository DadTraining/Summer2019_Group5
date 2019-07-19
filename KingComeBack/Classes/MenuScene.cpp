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
	background = Sprite::create("/Sprites/Background/Untitled.png");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	background->setScale( background->getContentSize().width/ visibleSize.width ,
		 background->getContentSize().height / visibleSize.height );
	background->removeFromParent();
	this->addChild(background, -10);

	// add buton Play
	btnPlay = ui::Button::create("/Buttons/king_buton.png","/Buttons/king_buton.png");

	btnPlay->setTitleText(" New Game ");
	btnPlay->setTitleFontName("/Fonts/arial.ttf");
	btnPlay->setTitleFontSize(20);
	btnPlay->setScale(2,1.5);
	btnPlay->setPosition(Vec2(3*visibleSize.width / 4, 3* visibleSize.height / 4+ 64));
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
			btnSetting->setOpacity(100);
			Director::getInstance()->replaceScene(GamePlayScene::createScene());
			break;
		default:
			break;
		}
	});

	this->addChild(btnPlay,1);

	// add buton restart
	btnAgainPlay = ui::Button::create("/Buttons/king_buton.png", "/Buttons/king_buton.png");

	btnAgainPlay->setTitleText(" Restart ");
	btnAgainPlay->setTitleFontName("/Fonts/arial.ttf");
	btnAgainPlay->setTitleFontSize(20);
	btnAgainPlay->setScale(2,1.5);
	btnAgainPlay->setPosition(Vec2(3*visibleSize.width / 4, btnPlay->getPositionY() - btnPlay->getContentSize().height - 32));
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
	btnSetting = ui::Button::create("/Buttons/king_buton.png", "/Buttons/king_buton.png");

	btnSetting->setTitleText(" Setting ");
	btnSetting->setTitleFontName("/Fonts/arial.ttf");
	btnSetting->setTitleFontSize(20);
	btnSetting->setScale(2,1.5);
	btnSetting->setPosition(Vec2(3*visibleSize.width / 4, btnAgainPlay->getPositionY()-btnAgainPlay->getContentSize().height - 32));
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
	btnExit = ui::Button::create("/Buttons/king_buton.png", "/Buttons/king_buton.png");

	btnExit->setTitleText(" Exit ");
	btnExit->setTitleFontName("/Fonts/arial.ttf");
	btnExit->setTitleFontSize(20);
	btnExit->setScale(2,1.5);
	btnExit->setPosition(Vec2(3*visibleSize.width / 4, btnSetting->getPositionY() - btnSetting->getContentSize().height - 32));
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
