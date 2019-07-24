#include "SettingScene.h"
#include "MenuScene.h"
#include "GameSetting.h"
#include "SimpleAudioEngine.h"

ui::CheckBox* cbMusic;
ui::CheckBox* cbSound;
ui::Slider* slVolume;

SettingScene::SettingScene()
{
}

SettingScene::~SettingScene()
{
}

bool SettingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	
	//ad title
	auto title = Label::createWithTTF("SETTING GAME", "Fonts/arial.ttf", 60);
	title->setPosition(visibleSize.width / 2, 3 * visibleSize.height / 4);
	addChild(title);
	
	//add checkbox music
	cbMusic = ui::CheckBox::create("Sprites/Checkbox/checkbox_normal.png", "Sprites/Checkbox/checkbox_pressed.png", "/Sprites/Checkbox/checkbox_checked.png", "/Sprites/Checkbox/checkbox_normal_disable.png", "/Sprites/Checkbox/checkbox_checked_disable.png");
	cbMusic->setScale(0.5f);
	cbMusic -> setAnchorPoint(Vec2(0, 0.5));
	cbMusic->setSelected(GameSetting::getIntance()->isEnableMusic());
	cbMusic->addClickEventListener([&](Ref* event)
	{
		GameSetting::getIntance()->setEnableMusic(cbMusic->isSelected());
		if (!cbMusic->isSelected() && !cbSound->isSelected())
		{
			slVolume->setEnabled(false);
		}
		else
		{
			slVolume->setEnabled(true);
		}
	});
	cbMusic->setPosition(Vec2(visibleSize.width / 2 - 128, visibleSize.height / 2 +64));
	addChild(cbMusic);

	//add label music
	auto cbMusicTitle = Label::createWithTTF("Music", "Fonts/arial.ttf", 30);
	cbMusicTitle->setPosition(cbMusic->getPosition() + Vec2(100, 0));
	addChild(cbMusicTitle);

	//add checkbox sound
	cbSound = ui::CheckBox::create("Sprites/Checkbox/checkbox_normal.png", "Sprites/Checkbox/checkbox_pressed.png", "/Sprites/Checkbox/checkbox_checked.png", "/Sprites/Checkbox/checkbox_normal_disable.png", "/Sprites/Checkbox/checkbox_checked_disable.png");
	cbSound->setScale(0.5f);
	cbSound->setAnchorPoint(Vec2(0, 0.5));
	cbSound->setSelected(GameSetting::getIntance()->isEnableSound());
	cbSound->addClickEventListener([&](Ref* event) {
		GameSetting::getIntance()->setEnableSound(cbSound->isSelected());
		if (!cbMusic->isSelected() && !cbSound->isSelected())
		{
			slVolume->setEnabled(false);
		}
		else
		{
			slVolume->setEnabled(true);
		}
	});
	cbSound->setPosition(Vec2(cbMusic->getPosition().x, cbMusic->getPosition().y-64));
	addChild(cbSound);

	//add label sound
	auto cbSoundcTitle = Label::createWithTTF("Sound", "Fonts/arial.ttf", 30);
	cbSoundcTitle->setPosition(cbSound->getPosition() + Vec2(100, 0));
	addChild(cbSoundcTitle);

	//add label volume
	auto volumeTitle = Label::createWithTTF("Volume", "Fonts/arial.ttf", 30);
	volumeTitle->setAnchorPoint(Vec2(0, 0.5));
	volumeTitle->setPosition(cbMusic->getPosition().x, cbSound->getPosition().y - 64);
	addChild(volumeTitle);

	//add slider volume
	slVolume = ui::Slider::create();
	slVolume->setAnchorPoint(Vec2(0, 0.5));
	slVolume->loadBarTexture("Sprites/Loading/slider_bar_bg.png");
	slVolume->loadSlidBallTextures("Sprites/Loading/slider_ball_normal.png", "Sprites/Loading/slider_ball_pressed.png", "/Sprites/Loading/slider_ball_disable.png");
	slVolume->loadProgressBarTexture("Sprites/Loading/slider_bar_pressed.png");
	slVolume->setPosition(Vec2(cbMusic->getPosition().x, visibleSize.height - 360));
	slVolume->setPercent(GameSetting::getIntance()->getVolume());
	slVolume->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			break;
		case ui::Widget::TouchEventType::ENDED:
			GameSetting::getIntance()->setVolume(slVolume->getPercent());
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(GameSetting::getIntance()->getVolume());
			SimpleAudioEngine::getInstance()->setEffectsVolume(GameSetting::getIntance()->getVolume());
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}
	});

	if (!cbMusic->isSelected() && !cbSound->isSelected())
	{
		slVolume->setEnabled(false);
	}

	addChild(slVolume);

	auto paricleEffect = ParticleSystemQuad::create("Sprites/particles/menu.plist");
	paricleEffect->setPosition(Vec2(visibleSize.width / 2, 0));
	addChild(paricleEffect);

	//add button back menu
	auto btnBack = ui::Button::create("Buttons/pngguru.com-id-bixpo_04.png", "Buttons/pngguru.com-id-bixpo_08.png");
	btnBack->setPosition(Vec2(70, 70));
	btnBack->setScale(0.5);
	btnBack->addClickEventListener([](Ref* event) {
		if (GameSetting::getIntance()->isEnableSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("Sound/confirm.wav");
		}
		Director::getInstance()->replaceScene(MenuScene::createScene());
	});
	addChild(btnBack);

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	return true;
}

Scene * SettingScene::createScene()
{
	auto scene = Scene::create();

	auto layer = SettingScene::create();

	scene->addChild(layer);

	return scene;
}
//#include "SettingScene.h"
//#include "MenuScene.h"
//#include "GameSetting.h"
//#include "SimpleAudioEngine.h"
//
//ui::CheckBox* cbMusic;
//ui::CheckBox* cbSound;
//ui::Slider* slVolume;
//
//SettingScene::SettingScene()
//{
//}
//
//SettingScene::~SettingScene()
//{
//}
//
//bool SettingScene::init()
//{
//	if (!Layer::init())
//	{
//		return false;
//	}
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	
//	//ad title
//	auto title = Label::createWithTTF("SETTING GAME", "Fonts/arial.ttf", 60);
//	title->setPosition(visibleSize.width / 2, 3 * visibleSize.height / 4);
//	addChild(title);
//	
//	//add checkbox music
//	cbMusic = ui::CheckBox::create("/Sprites/Checkbox/checkbox_normal.png", "/Sprites/Checkbox/checkbox_pressed.png", "/Sprites/Checkbox/checkbox_checked.png", "/Sprites/Checkbox/checkbox_normal_disable.png", "/Sprites/Checkbox/checkbox_checked_disable.png");
//	cbMusic->setScale(0.5f);
//	cbMusic -> setAnchorPoint(Vec2(0, 0.5));
//	cbMusic->setSelected(GameSetting::getIntance()->isEnableMusic());
//	cbMusic->addClickEventListener([&](Ref* event)
//	{
//		GameSetting::getIntance()->setEnableMusic(cbMusic->isSelected());
//		if (!cbMusic->isSelected() && !cbSound->isSelected())
//		{
//			slVolume->setEnabled(false);
//		}
//		else
//		{
//			slVolume->setEnabled(true);
//		}
//	});
//	cbMusic->setPosition(Vec2(visibleSize.width / 2 - 128, visibleSize.height / 2 +64));
//	addChild(cbMusic);
//
//	//add label music
//	auto cbMusicTitle = Label::createWithTTF("Music", "Fonts/arial.ttf", 30);
//	cbMusicTitle->setPosition(cbMusic->getPosition() + Vec2(100, 0));
//	addChild(cbMusicTitle);
//
//	//add checkbox sound
//	cbSound = ui::CheckBox::create("/Sprites/Checkbox/checkbox_normal.png", "/Sprites/Checkbox/checkbox_pressed.png", "/Sprites/Checkbox/checkbox_checked.png", "/Sprites/Checkbox/checkbox_normal_disable.png", "/Sprites/Checkbox/checkbox_checked_disable.png");
//	cbSound->setScale(0.5f);
//	cbSound->setAnchorPoint(Vec2(0, 0.5));
//	cbSound->setSelected(GameSetting::getIntance()->isEnableSound());
//	cbSound->addClickEventListener([&](Ref* event) {
//		GameSetting::getIntance()->setEnableSound(cbSound->isSelected());
//		if (!cbMusic->isSelected() && !cbSound->isSelected())
//		{
//			slVolume->setEnabled(false);
//		}
//		else
//		{
//			slVolume->setEnabled(true);
//		}
//	});
//	cbSound->setPosition(Vec2(cbMusic->getPosition().x, cbMusic->getPosition().y-64));
//	addChild(cbSound);
//
//	//add label sound
//	auto cbSoundcTitle = Label::createWithTTF("Sound", "Fonts/arial.ttf", 30);
//	cbSoundcTitle->setPosition(cbSound->getPosition() + Vec2(100, 0));
//	addChild(cbSoundcTitle);
//
//	//add label volume
//	auto volumeTitle = Label::createWithTTF("Volume", "Fonts/arial.ttf", 30);
//	volumeTitle->setAnchorPoint(Vec2(0, 0.5));
//	volumeTitle->setPosition(cbMusic->getPosition().x, cbSound->getPosition().y - 64);
//	addChild(volumeTitle);
//
//	//add slider volume
//	slVolume = ui::Slider::create();
//	slVolume->setAnchorPoint(Vec2(0, 0.5));
//	slVolume->loadBarTexture("/Sprites/Loading/slider_bar_bg.png");
//	slVolume->loadSlidBallTextures("/Sprites/Loading/slider_ball_normal.png", "/Sprites/Loading/slider_ball_pressed.png", "/Sprites/Loading/slider_ball_disable.png");
//	slVolume->loadProgressBarTexture("/Sprites/Loading/slider_bar_pressed.png");
//	slVolume->setPosition(Vec2(cbMusic->getPosition().x, visibleSize.height - 360));
//	slVolume->setPercent(GameSetting::getIntance()->getVolume());
//	slVolume->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
//	{
//		switch (type)
//		{
//		case cocos2d::ui::Widget::TouchEventType::BEGAN:
//			break;
//		case cocos2d::ui::Widget::TouchEventType::MOVED:
//			break;
//		case ui::Widget::TouchEventType::ENDED:
//			GameSetting::getIntance()->setVolume(slVolume->getPercent());
//			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(GameSetting::getIntance()->getVolume());
//			SimpleAudioEngine::getInstance()->setEffectsVolume(GameSetting::getIntance()->getVolume());
//			break;
//		case cocos2d::ui::Widget::TouchEventType::CANCELED:
//			break;
//		default:
//			break;
//		}
//	});
//
//	if (!cbMusic->isSelected() && !cbSound->isSelected())
//	{
//		slVolume->setEnabled(false);
//	}
//
//	addChild(slVolume);
//
//	auto paricleEffect = ParticleSystemQuad::create("/Sprites/particles/menu.plist");
//	paricleEffect->setPosition(Vec2(visibleSize.width / 2, 0));
//	addChild(paricleEffect);
//
//	//add button back menu
//	auto btnBack = ui::Button::create("/Buttons/pngguru.com-id-bixpo_04.png", "/Buttons/pngguru.com-id-bixpo_08.png");
//	btnBack->setPosition(Vec2(70, 70));
//	btnBack->setScale(0.5);
//	btnBack->addClickEventListener([](Ref* event) {
//		if (GameSetting::getIntance()->isEnableSound())
//		{
//			SimpleAudioEngine::getInstance()->playEffect("Sound/confirm.wav");
//		}
//		Director::getInstance()->replaceScene(MenuScene::createScene());
//	});
//	addChild(btnBack);
//
//	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
//
//	return true;
//}
//
//Scene * SettingScene::createScene()
//{
//	auto scene = Scene::create();
//
//	auto layer = SettingScene::create();
//
//	scene->addChild(layer);
//
//	return scene;
//}
