//
//  Popup.cpp
//  dreamWeek
//
//  Created by Bilal Mirza on 07/08/2017.
//
//

#include "Popup.h"

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
	const char *OK_BUTTON = "v.png";
	const char *OK_BUTTON_PRESSED = "v.png";
	const char *CANCEL_BUTTON = "x.png";
	const char *CANCEL_BUTTON_PRESSED = "x_press.png";
	const char *ADD_BUTTON = "AddKnight_button.png";
	const char *ADD_BUTTON_PRESS = "AddKnight_button_press.png";
	const char *SUB_BUTTON = "subKnight_button.png";
	const char *SUB_BUTTON_PRESS = "subKnight_button.png";

	const char *BACKGROUND_IMAGE_HERO = "m_PopupHero1.png";
	const char *BACKGROUND_IMAGE_HOUSE = "PopupHouse.png";
	const char *BACKGROUND_IMAGE_TOWNHALL = "UI_of_HallTown.png";
	const char *TOWN_HALL_BUTTON = "HallTown_button.png";
	const char *TOWN_HALL_BUTTON_PRESS = "HallTown_button_press.png";
	const char *SCOUT_TOWN_BUTTON = "ScoutTown2D_button.png";
	const char *SCOUT_TOWN_BUTTON_PRESS = "ScoutTown2D_button_press.png";
	const char *HOUSE_MAIN_BUTTON = "HouseMain_button.png";
	const char *HOUSE_MAIN_BUTTON_PRESS = "HouseMain_button_press.png";
	const char *HOUSE_STORE_BUTTON = "StoreHouse_button.png";
	const char *HOUSE_STORE_BUTTON_PRESS = "StoreHouse_button_press.png";
	const char *HOUSE_DECORATE_BUTTON = "HouseDecorate_button.png";
	const char *HOUSE_DECORATE_BUTTON_PRESS = "HouseDecorate_button_press";
	const char *AXE_ITEM = "axe.png";
	const char *KNIHT_ITEM = "itemKnight.png";
	const char *BACKGROUND_POPUP_CHOOSE_KNIGHT = "Popup_choose_knight.png";
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

	Popup *Popup::createAsMessage(const std::string &title, const std::string &msg)
	{
		return createAsConfirmDialogue(title, msg, NULL);
	}

	Popup *Popup::createAsConfirmDialogue(const std::string &title, const std::string &msg, const std::function<void()> &YesFunc)
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
	//-------------------------------------------------------------
	//---------------POPUP CONTAIN HOUSE---------------------------
	//-------------------------------------------------------------

	PopupHouse * PopupHouse::createAsMessage(const std::string & title, const std::string & msg)
	{
		//return createAsConfirmDialogue(title, msg, nullptr);
		return nullptr;
	}
	PopupHouse * PopupHouse::createAsConfirmDialogue(const std::string & title, 
		const std::string & msg, const std::function<void()>& townHall, 
		const std::function<void()>& scoutTown, const std::function<void()>& mainHouse, 
		const std::function<void()>& storeHouse, const std::function<void()>& DecorateHouse, 
		const std::function<void()>& YesFunc5, const std::function<void()>& YesFunc6)
	{
		return create(title, msg, NULL, townHall, scoutTown, mainHouse, storeHouse, DecorateHouse, YesFunc5, YesFunc6);
	}

	PopupHouse * PopupHouse::create(const std::string & title, const std::string & msg, 
		cocos2d::Label * lbl, const std::function<void()>& mainHouse,
		const std::function<void()>& townHall, const std::function<void()>& storeHouse,
		const std::function<void()>& scoutTown, const std::function<void()>& DecorateHouse,
		const std::function<void()>& YesFunc5, const std::function<void()>& YesFunc6)
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


			if (mainHouse) {

				MenuItemImage *houseMain = MenuItemImage::create(IMAGEPATH::HOUSE_MAIN_BUTTON, IMAGEPATH::HOUSE_MAIN_BUTTON_PRESS, [=](Ref *sender) {
					mainHouse();
					node->dismiss(true);
				});
				MenuItemImage *houseDecorate = MenuItemImage::create(IMAGEPATH::HOUSE_DECORATE_BUTTON, IMAGEPATH::HOUSE_DECORATE_BUTTON_PRESS, [=](Ref *sender) {
					DecorateHouse();
					node->dismiss(true);
				});
				MenuItemImage *StoreHouse = MenuItemImage::create(IMAGEPATH::HOUSE_STORE_BUTTON, IMAGEPATH::HOUSE_STORE_BUTTON_PRESS, [=](Ref *sender) {
					storeHouse();
					node->dismiss(true);
				});
				MenuItemImage *hallTownImage = MenuItemImage::create(IMAGEPATH::TOWN_HALL_BUTTON, IMAGEPATH::TOWN_HALL_BUTTON_PRESS, [=](Ref *sender) {
					townHall();
					node->dismiss(true);
				});
				MenuItemImage *scoutTownImage = MenuItemImage::create(IMAGEPATH::SCOUT_TOWN_BUTTON, IMAGEPATH::SCOUT_TOWN_BUTTON_PRESS, [=](Ref *sender) {
					scoutTown();
					node->dismiss(true);
				});
				MenuItemImage *noButton = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node](Ref *sender) {
					node->dismiss(true);
				});

				Menu *menu = Menu::create(houseMain, hallTownImage, StoreHouse, scoutTownImage, houseDecorate,NULL);
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
	PopupHero * PopupHero::createAsConfirmDialogue(Layer * layer, const std::string & title, const std::string & msg, const std::function<void()>& YesFunc)
	{
		return create(layer, title, msg, NULL, YesFunc);
	}
	PopupHero * PopupHero::create(Layer *layer, const std::string & title, const std::string & msg, cocos2d::Label * lbl, const std::function<void()>& YesFunc)
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
				Vector<MenuItem *> menuItemImage;
				for (size_t i = 0; i < 24; i++)
				{

					auto item = new Item(layer, 2);

					menuItemImage.pushBack(item->getMenuItemImage());
				}

				Menu *menu = Menu::createWithArray(menuItemImage);

				node->addChild(menu, 2);

				menu->alignItemsInColumns(4, 4, 4, 4, 4, 4);
				menu->setPosition(winSize.width * 3 / 4.4, winSize.height / 1.9); //- lbl->getContentSize().height / 2 - 75);


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
	}
	//-------------------------------------------------------------------------------
	// -------------------POPUP CREATE KNIGHT OF TOWN HALL---------------------------
	//-------------------------------------------------------------------------------
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
				MenuItemImage *knight = MenuItemImage::create(IMAGEPATH::KNIHT_ITEM, IMAGEPATH::KNIHT_ITEM, [=](Ref *sender) {
					YesFunc();
					node->dismiss(true);
				});

				MenuItemImage *noButton = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node](Ref *sender) {
					node->dismiss(true);
				});

				Menu *menu = Menu::create(knight, noButton , NULL);
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
	//-------------------------------------------------------------------------------
	// -------------------POPUP CREATE KNIGHT OF TOWN HALL---------------------------
	//-------------------------------------------------------------------------------
	PopupChooseKnight * PopupChooseKnight::createAsMessage(const std::string & title, const std::string & msg)
	{
		return nullptr;
	}
	PopupChooseKnight * PopupChooseKnight::createAsConfirmDialogue(const std::string & title, const std::string & msg, const std::function<void()>& YesFunc)
	{
		return create(title, msg, NULL, YesFunc);
	}
	PopupChooseKnight * PopupChooseKnight::create(const std::string & title, const std::string & msg, cocos2d::Label * lbl, const std::function<void()>& YesFunc)
	{
		PopupChooseKnight *node = new (std::nothrow)PopupChooseKnight();
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
				MenuItemImage *knight = MenuItemImage::create(IMAGEPATH::KNIHT_ITEM, IMAGEPATH::KNIHT_ITEM, [=](Ref *sender) {

					YesFunc();
					node->dismiss(true);
				});
				knight->setScale(0.5);

				//Add menu yes no
				MenuItemImage *noButton = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node](Ref *sender) {
					node->dismiss(true);
				});
				MenuItemImage *YesButton = MenuItemImage::create(IMAGEPATH::OK_BUTTON, IMAGEPATH::OK_BUTTON_PRESSED, [=](Ref *sender) {
					YesFunc();
					node->dismiss(true);
				});
				Menu *menu = Menu::create(YesButton, noButton, NULL);
				node->addChild(menu, 2);
				menu->setPosition(winSize.width / 1.7, winSize.height / 1.5 - lbl->getContentSize().height / 2 - 75);
				menu->alignItemsHorizontallyWithPadding(FONT::LABEL_OFFSET / 2);

				//Add menu add sub
				auto addButton = MenuItemImage::create(IMAGEPATH::ADD_BUTTON, IMAGEPATH::ADD_BUTTON_PRESS, [=](Ref *sender) {

				});
				auto subButton = MenuItemImage::create(IMAGEPATH::SUB_BUTTON, IMAGEPATH::SUB_BUTTON_PRESS, [=](Ref *sender) {

				});
				Menu *menuAddSub = Menu::create(subButton, addButton, NULL);
				node->addChild(menuAddSub, 2);
				//menuAddSub->setPosition(winSize.width * 0.8, menu->getPosition());
				menuAddSub->alignItemsHorizontallyWithPadding(subButton->getContentSize().width / 2);
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
	void PopupChooseKnight::initBg(const cocos2d::Size size, const std::string & title)
	{
		Size winSize = Director::getInstance()->getWinSize();

		_bg = ui::ImageView::create(IMAGEPATH::BACKGROUND_POPUP_CHOOSE_KNIGHT);
		this->addChild(_bg);

		_bg->setPosition(Point(winSize.width * 0.6, winSize.height * 0.6));
		_bg->setScale9Enabled(true);
		//_bg->setContentSize(Size(_bg->getContentSize().width * 1.5, _bg->getContentSize().height));
		_bg->setScale(1.5);
		ui::ImageView *fill = ui::ImageView::create(IMAGEPATH::BACKGROUND_POPUP_CHOOSE_KNIGHT);
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
