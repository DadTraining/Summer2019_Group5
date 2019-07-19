//
//  Popup.cpp
//  dreamWeek
//
//  Created by Bilal Mirza on 07/08/2017.
//
//

#include "Popup.h"
//#include "PopupRepo.h"

USING_NS_CC;

using namespace ui;

namespace {
	cocos2d::Size CONFIRM_DIALOGUE_SIZE_OFFSET = Size(100, 150);
	const float ANIMATION_TIME = 0.15f;
	const float FADE_RATIO = 200;
}

namespace FONT {
	const float LABEL_OFFSET = 50;
	const float DESCRIPTION_TEXT_SIZE = 45;
	const float TITLE_TEXT_SIZE = 30;
	const char *GAME_FONT = "fonts/Marker Felt.ttf";
	const float LABEL_STROKE = 4;
}
namespace IMAGEPATH {
	const char *OK_BUTTON = "CloseNormal.png";
	const char *OK_BUTTON_PRESSED = "CloseNormal.png";
	const char *CANCEL_BUTTON = "x.png";
	const char *CANCEL_BUTTON_PRESSED = "x_press.png";
	const char *CLOSE_BUTTON = "CloseNormal.png";
	const char *BACKGROUND_IMAGE_HERO = "m_PopupHero1.png";
	const char *BACKGROUND_IMAGE_HOUSE = "PopupHouse.png";
	const char *BACKGROUND_IMAGE_TOWNHALL = "UI_of_ScoutTown.png";
	const char *TOWN_HALL_BUTTON = "HallTownButton.png";
	const char *TOWN_HALL_BUTTON_PRESS = "HallTownButton_press.png";
	const char *SCOUT_TOWN_BUTTON = "ScoutTown2D_button.png";
	const char *SCOUT_TOWN_BUTTON_PRESS = "ScoutTown2D_button_press.png";

}
namespace UICustom {

	PopupDelegates *PopupDelegates::create()
	{
		PopupDelegates *node = new (std::nothrow)PopupDelegates();
		if (node && node->init())
		{
			node->autorelease();
			return node;
		}
		CC_SAFE_DELETE(node);
		return nullptr;
	}

	bool PopupDelegates::init()
	{
		Size winSize = Director::getInstance()->getWinSize();

		if (!LayerRadialGradient::initWithColor(Color4B(0, 0, 0, 0), Color4B(0, 0, 0, FADE_RATIO), winSize.width / 1.7f, winSize / 2, 0.075f))
		{
			return false;
		}
		this->setOpacity(0);
		show(true);
		this->setUpTouches();


		return true;
	}

	void PopupDelegates::show(const bool animated)
	{
		if (animated) {
			this->runAction(FadeTo::create(ANIMATION_TIME, FADE_RATIO));
		}
		else {
			this->setOpacity(FADE_RATIO);
		}
	}
	void PopupDelegates::dismiss(const bool animated)
	{
		if (animated) {
			this->runAction(Sequence::create(FadeTo::create(ANIMATION_TIME, 0), RemoveSelf::create(), NULL));
		}
		else {
			this->removeFromParentAndCleanup(true);
		}
	}

	void PopupDelegates::setUpTouches()
	{

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [=](Touch* touch, Event* event) {
			if (_bg) {
				if (!_bg->getBoundingBox().containsPoint(this->convertToNodeSpace(touch->getLocation())))
				{
					this->dismiss(true);
				}
			}
			else {
				this->dismiss(true);
			}
			return true;
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}

	// popup

	Popup *Popup::createAsMessage(const std::string &title ,const std::string &msg)
	{
		return createAsConfirmDialogue(title, msg, NULL);
	}

	Popup *Popup::createAsConfirmDialogue(const std::string &title, const std::string &msg,const std::function<void()> &YesFunc)
	{
		return create(title, msg, NULL, YesFunc);
	}

	Popup *Popup::create(const std::string &title, const std::string &msg, cocos2d::Label *lbl, const std::function<void()> &YesFunc)
	{
		Popup *node = new (std::nothrow)Popup();
		Size winSize = Director::getInstance()->getWinSize();
		if (node && node->init())
		{
			if (!lbl) {
				lbl = Label::createWithTTF(msg, FONT::GAME_FONT, FONT::DESCRIPTION_TEXT_SIZE);
			}
			lbl->setPosition(winSize.width / 2, winSize.height / 2 - FONT::LABEL_OFFSET / 2);
			lbl->enableOutline(Color4B::BLACK, FONT::LABEL_STROKE);
			lbl->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
			lbl->enableShadow(Color4B::BLACK, Size(0, -2));

			if (YesFunc) {
				MenuItemImage *yesButton = MenuItemImage::create(IMAGEPATH::OK_BUTTON, IMAGEPATH::OK_BUTTON_PRESSED, [=](Ref *sender) {

					YesFunc();
					node->dismiss(true);
				});

				MenuItemImage *noButton = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node](Ref *sender) {
					node->dismiss(true);
				});

				Menu *menu = Menu::create(noButton, NULL);
				node->addChild(menu, 2);
				menu->setPosition(winSize.width / 2, winSize.height / 2 - lbl->getContentSize().height / 2 - 75);
				menu->alignItemsHorizontallyWithPadding(FONT::LABEL_OFFSET / 2);

				lbl->setPosition(winSize / 2);
				CONFIRM_DIALOGUE_SIZE_OFFSET = Size(CONFIRM_DIALOGUE_SIZE_OFFSET.width, 300);
			}
			node->addChild(lbl, 10);
			node->initBg(lbl->getContentSize() + CONFIRM_DIALOGUE_SIZE_OFFSET, title);
			node->autorelease();
			return node;
		}

		CC_SAFE_DELETE(node);
		return nullptr;
	}


	void Popup::initBg(Size size, const std::string &title)
	{

		Size winSize = Director::getInstance()->getWinSize();

		_bg = ui::ImageView::create(IMAGEPATH::BACKGROUND_IMAGE_HERO);
		this->addChild(_bg);

		_bg->setPosition(Point(winSize.width / 2, winSize.height / 2));
		_bg->setScale9Enabled(true);
		//_bg->setContentSize(size);

		ui::ImageView *fill = ui::ImageView::create(IMAGEPATH::BACKGROUND_IMAGE_HERO);
		//_bg->addChild(fill);
		fill->setColor(Color3B(210, 210, 210));
		fill->setScale9Enabled(true);
		fill->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
		fill->setPosition(Point(FONT::LABEL_OFFSET / 4, FONT::LABEL_OFFSET / 4));
		//fill->setContentSize(Size(size.width - FONT::LABEL_OFFSET / 2, size.height - FONT::LABEL_OFFSET * 2));
		

		Label *heading = Label::createWithTTF(title, FONT::GAME_FONT, FONT::TITLE_TEXT_SIZE);
		heading->setPosition(_bg->getContentSize().width / 2, _bg->getContentSize().height - FONT::LABEL_OFFSET / 2.3);
		_bg->addChild(heading);
		heading->enableOutline(Color4B::BLACK, FONT::LABEL_STROKE);
		heading->enableShadow(Color4B::BLACK, Size(0, -3));
	}

	//---------------Popup of house--------------------------------

	PopupHouse * PopupHouse::createAsMessage(const std::string & title, const std::string & msg)
	{
		//return createAsConfirmDialogue(title, msg, nullptr);
		return nullptr;
	}
	PopupHouse *PopupHouse::createAsConfirmDialogue(const std::string &title, const std::string & msg, const std::function<void()> &YesFunc, const std::function<void()> &YesFunc1)
	{
		return create(title, msg, NULL, YesFunc, YesFunc1);
	}

	PopupHouse *PopupHouse::create(const std::string &title, const std::string &msg, cocos2d::Label *lbl, 
		const std::function<void()> &YesFunc, const std::function<void()> &YesFunc1)
	{
		PopupHouse *node = new (std::nothrow)PopupHouse();
		Size winSize = Director::getInstance()->getWinSize();
		if (node && node->init())
		{
			if (!lbl) {
				lbl = Label::createWithTTF(msg, FONT::GAME_FONT, FONT::DESCRIPTION_TEXT_SIZE);
			}
			lbl->setPosition(winSize.width / 2, winSize.height / 2 - FONT::LABEL_OFFSET / 2);
			lbl->enableOutline(Color4B::BLACK, FONT::LABEL_STROKE);
			lbl->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
			lbl->enableShadow(Color4B::BLACK, Size(0, -2));

			
			if (YesFunc) {
				//MenuItemImage *hallTownImage = MenuItemImage::create(IMAGEPATH::TOWN_HALL_BUTTON, IMAGEPATH::TOWN_HALL_BUTTON_PRESS, [=](Ref *sender) {
				//	YesFunc();
				//	node->dismiss(true);
				//});
				MenuItemImage *hallTownImage = MenuItemImage::create(IMAGEPATH::TOWN_HALL_BUTTON, IMAGEPATH::TOWN_HALL_BUTTON_PRESS, [=](Ref *sender) {
					YesFunc();
					node->dismiss(true);
				});
				MenuItemImage *scoutTownImage = MenuItemImage::create(IMAGEPATH::SCOUT_TOWN_BUTTON, IMAGEPATH::SCOUT_TOWN_BUTTON_PRESS, [=](Ref *sender) {
					YesFunc1();
					node->dismiss(true);
				});
				MenuItemImage *noButton = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node](Ref *sender) {
					node->dismiss(true);
				});

				Menu *menu = Menu::create(hallTownImage, scoutTownImage , NULL);
				node->addChild(menu, 2);
				menu->setPosition(winSize.width / 2, winSize.height / 1.5 - lbl->getContentSize().height / 2 - 75);
				menu->alignItemsHorizontallyWithPadding(FONT::LABEL_OFFSET / 2);

				lbl->setPosition(winSize / 2);
				CONFIRM_DIALOGUE_SIZE_OFFSET = Size(CONFIRM_DIALOGUE_SIZE_OFFSET.width, 300);
			}
			node->addChild(lbl, 10);
			node->initBg(lbl->getContentSize() + CONFIRM_DIALOGUE_SIZE_OFFSET, title);
			node->autorelease();
			return node;
		}

		CC_SAFE_DELETE(node);
		return nullptr;
	}


	void PopupHouse::initBg(Size size, const std::string &title)
	{

		Size winSize = Director::getInstance()->getWinSize();

		_bg = ui::ImageView::create(IMAGEPATH::BACKGROUND_IMAGE_HOUSE);
		this->addChild(_bg);

		_bg->setPosition(Point(winSize.width / 2, winSize.height / 2));
		//_bg->setScale9Enabled(true);
		//_bg->setContentSize(size);

		ui::ImageView *fill = ui::ImageView::create(IMAGEPATH::BACKGROUND_IMAGE_HOUSE);
		//_bg->addChild(fill);
		fill->setColor(Color3B(210, 210, 210));
		fill->setScale9Enabled(true);
		fill->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
		fill->setPosition(Point(FONT::LABEL_OFFSET / 4, FONT::LABEL_OFFSET / 4));
		//fill->setContentSize(Size(size.width - FONT::LABEL_OFFSET / 2, size.height - FONT::LABEL_OFFSET * 2));

		Label *heading = Label::createWithTTF(title, FONT::GAME_FONT, FONT::TITLE_TEXT_SIZE);
		heading->setPosition(_bg->getContentSize().width / 2, _bg->getContentSize().height / 1.5 - FONT::LABEL_OFFSET / 2.3);
		_bg->addChild(heading);
		heading->enableOutline(Color4B::BLACK, FONT::LABEL_STROKE);
		heading->enableShadow(Color4B::BLACK, Size(0, -3));
	}

	// popup hero
	PopupHero * PopupHero::createAsMessage(const std::string & title, const std::string & msg)
	{
		return nullptr;
	}
	PopupHero * PopupHero::createAsConfirmDialogue(const std::string & title, const std::string & msg, const std::function<void()>& YesFunc)
	{
		return create(title, msg, NULL, YesFunc);
	}
	PopupHero * PopupHero::create(const std::string & title, const std::string & msg, cocos2d::Label * lbl, const std::function<void()>& YesFunc)
	{
		PopupHero *node = new (std::nothrow)PopupHero();
		Size winSize = Director::getInstance()->getWinSize();
		if (node && node->init())
		{
			if (!lbl) {
				lbl = Label::createWithTTF(msg, FONT::GAME_FONT, FONT::DESCRIPTION_TEXT_SIZE);
			}
			lbl->setPosition(winSize.width / 2, winSize.height / 2 - FONT::LABEL_OFFSET / 2);
			lbl->enableOutline(Color4B::BLACK, FONT::LABEL_STROKE);
			lbl->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
			lbl->enableShadow(Color4B::BLACK, Size(0, -2));

			if (YesFunc) {
				MenuItemImage *yesButton = MenuItemImage::create(IMAGEPATH::OK_BUTTON, IMAGEPATH::OK_BUTTON_PRESSED, [=](Ref *sender) {

					YesFunc();
					node->dismiss(true);
				});

				MenuItemImage *noButton = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node](Ref *sender) {
					node->dismiss(true);
				});

				Menu *menu = Menu::create(NULL);
				node->addChild(menu, 2);
				menu->setPosition(winSize.width / 2, winSize.height / 2 - lbl->getContentSize().height / 2 - 75);
				menu->alignItemsHorizontallyWithPadding(FONT::LABEL_OFFSET / 2);

				lbl->setPosition(winSize / 2);
				CONFIRM_DIALOGUE_SIZE_OFFSET = Size(CONFIRM_DIALOGUE_SIZE_OFFSET.width, 300);
			}
			node->addChild(lbl, 10);
			node->initBg(lbl->getContentSize() + CONFIRM_DIALOGUE_SIZE_OFFSET, title);
			node->autorelease();
			return node;
		}

		CC_SAFE_DELETE(node);
		return nullptr;
	}
	void PopupHero::initBg(const cocos2d::Size size, const std::string & title)
	{
		Size winSize = Director::getInstance()->getWinSize();

		_bg = ui::ImageView::create(IMAGEPATH::BACKGROUND_IMAGE_HERO);
		this->addChild(_bg);

		_bg->setPosition(Point(winSize.width / 2, winSize.height / 2));
		_bg->setScale9Enabled(true);
		//_bg->setContentSize(size);

		ui::ImageView *fill = ui::ImageView::create(IMAGEPATH::BACKGROUND_IMAGE_HERO);
		//_bg->addChild(fill);
		fill->setColor(Color3B(210, 210, 210));
		fill->setScale9Enabled(true);
		fill->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
		fill->setPosition(Point(FONT::LABEL_OFFSET / 4, FONT::LABEL_OFFSET / 4));
		//fill->setContentSize(Size(size.width - FONT::LABEL_OFFSET / 2, size.height - FONT::LABEL_OFFSET * 2));


		Label *heading = Label::createWithTTF(title, FONT::GAME_FONT, FONT::TITLE_TEXT_SIZE);
		heading->setPosition(_bg->getContentSize().width / 2, _bg->getContentSize().height - FONT::LABEL_OFFSET / 2.3);
		_bg->addChild(heading);
		heading->enableOutline(Color4B::BLACK, FONT::LABEL_STROKE);
		heading->enableShadow(Color4B::BLACK, Size(0, -3));
	}\
	// popup town hall
	PopupTownHall * PopupTownHall::createAsMessage(const std::string & title, const std::string & msg)
	{
		return nullptr;
	}
	PopupTownHall * PopupTownHall::createAsConfirmDialogue(const std::string & title, const std::string & msg, const std::function<void()>& YesFunc)
	{
		return create(title, msg, NULL, YesFunc);
	}
	PopupTownHall * PopupTownHall::create(const std::string & title, const std::string & msg, cocos2d::Label * lbl, const std::function<void()>& YesFunc)
	{
		PopupTownHall *node = new (std::nothrow)PopupTownHall();
		Size winSize = Director::getInstance()->getWinSize();
		if (node && node->init())
		{
			if (!lbl) {
				lbl = Label::createWithTTF(msg, FONT::GAME_FONT, FONT::DESCRIPTION_TEXT_SIZE);
			}
			lbl->setPosition(winSize.width / 2, winSize.height / 2 - FONT::LABEL_OFFSET / 2);
			lbl->enableOutline(Color4B::BLACK, FONT::LABEL_STROKE);
			lbl->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
			lbl->enableShadow(Color4B::BLACK, Size(0, -2));

			if (YesFunc) {
				MenuItemImage *yesButton = MenuItemImage::create(IMAGEPATH::OK_BUTTON, IMAGEPATH::OK_BUTTON_PRESSED, [=](Ref *sender) {

					YesFunc();
					node->dismiss(true);
				});

				MenuItemImage *noButton = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node](Ref *sender) {
					node->dismiss(true);
				});

				Menu *menu = Menu::create(NULL);
				node->addChild(menu, 2);
				menu->setPosition(winSize.width / 2, winSize.height / 2 - lbl->getContentSize().height / 2 - 75);
				menu->alignItemsHorizontallyWithPadding(FONT::LABEL_OFFSET / 2);

				lbl->setPosition(winSize / 2);
				CONFIRM_DIALOGUE_SIZE_OFFSET = Size(CONFIRM_DIALOGUE_SIZE_OFFSET.width, 300);
			}
			node->addChild(lbl, 10);
			node->initBg(lbl->getContentSize() + CONFIRM_DIALOGUE_SIZE_OFFSET, title);
			node->autorelease();
			return node;
		}

		CC_SAFE_DELETE(node);
		return nullptr;
	}
	void PopupTownHall::initBg(const cocos2d::Size size, const std::string & title)
	{
		Size winSize = Director::getInstance()->getWinSize();

		_bg = ui::ImageView::create(IMAGEPATH::BACKGROUND_IMAGE_TOWNHALL);
		this->addChild(_bg);

		_bg->setPosition(Point(winSize.width / 2, winSize.height / 2));
		_bg->setScale9Enabled(true);
		//_bg->setContentSize(size);

		ui::ImageView *fill = ui::ImageView::create(IMAGEPATH::BACKGROUND_IMAGE_TOWNHALL);
		//_bg->addChild(fill);
		fill->setColor(Color3B(210, 210, 210));
		fill->setScale9Enabled(true);
		fill->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
		fill->setPosition(Point(FONT::LABEL_OFFSET / 4, FONT::LABEL_OFFSET / 4));
		//fill->setContentSize(Size(size.width - FONT::LABEL_OFFSET / 2, size.height - FONT::LABEL_OFFSET * 2));


		Label *heading = Label::createWithTTF(title, FONT::GAME_FONT, FONT::TITLE_TEXT_SIZE);
		heading->setPosition(_bg->getContentSize().width / 2, _bg->getContentSize().height - FONT::LABEL_OFFSET / 2.3);
		_bg->addChild(heading);
		heading->enableOutline(Color4B::BLACK, FONT::LABEL_STROKE);
		heading->enableShadow(Color4B::BLACK, Size(0, -3));
	}
}
