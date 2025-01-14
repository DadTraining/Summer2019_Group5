#ifndef Popup_h
#define Popup_h

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Item.h"
#include "Defines.h"

/*
-Displays a popup
-Resizes itself
-Automatically swallows rest of the touches
-Exit is called if touch is outside Bg
*/

namespace UICustom {


	class PopupDelegates : public cocos2d::LayerRadialGradient
	{

	public:
		static PopupDelegates *create();

	protected:
		virtual bool init();
		virtual void setUpTouches();

		virtual void show(const bool animated = true);
		virtual void dismiss(const bool animated = true);
		//void setAnimated(const bool animated) { _isAnimated = animated; };
		//Size GetVisibleSize() { return Director::getInstance()->getVisibleSize(); };

		cocos2d::ui::ImageView *_bg = nullptr;
	private:
		//bool _isAnimated = false;
	};



	class Popup : public PopupDelegates
	{

	public:
		static Popup* createAsMessage(const std::string &title, const std::string &msg);
		static Popup* createAsConfirmDialogue(const std::string &title, const std::string &msg, const std::function<void()> &YesFunc);
		static Popup* create(const std::string &title, const std::string &msg, cocos2d::Label *lbl, const std::function<void()> &YesFunc);

	private:
		void initBg(const cocos2d::Size size, const std::string &title);
	};

	// class popup building house
	class PopupHouse : public PopupDelegates
	{
	public:
		static PopupHouse* createAsMessage(const std::string &title, const std::string &msg);

		static PopupHouse* createAsConfirmDialogue(const std::string &title, const std::string &msg, 
			const std::function<void()> &townHall, const std::function<void()> &scoutTown, 
			const std::function<void()> &mainHouse, const std::function<void()> &storeHouse, 
			const std::function<void()> &DecorateHouse, const std::function<void()> &YesFunc5, 
			const std::function<void()> &YesFunc6);
		static PopupHouse* create(const std::string &title, const std::string &msg,
			cocos2d::Label *lbl, const std::function<void()> &townHall,
			const std::function<void()> &scoutTown, const std::function<void()> &mainHouse
			, const std::function<void()> &storeHouse, const std::function<void()> &DecorateHouse,
			const std::function<void()> &YesFunc5, const std::function<void()> &YesFunc6);

	private:
		void initBg(const cocos2d::Size size, const std::string &title);
	};

	// popup hero
	class PopupHero : public PopupDelegates
	{
	public:
		static PopupHero* createAsMessage(const std::string &title, const std::string &msg);
		static PopupHero* createAsConfirmDialogue(const std::string &title, const std::string &msg, 
			std::vector<Item *> &menuItem, const std::function<void()> &YesFunc, MenuItemLabel * _menuLabelHp
			, MenuItemLabel * _menuLabelDamage, MenuItemLabel * _menuLabelArmor, MenuItemLabel * _menuLabelStrength);
		static PopupHero* create(const std::string &title, const std::string &msg, 
			cocos2d::Label *lbl, std::vector<Item *> &menuItem,const std::function<void()> &YesFunc, MenuItemLabel * _menuLabelHp
			, MenuItemLabel * _menuLabelDamage, MenuItemLabel * _menuLabelArmor, MenuItemLabel * _menuLabelStrength);
	private:
		void initBg(const cocos2d::Size size, const std::string &title);
	};

	// popup town hall
	class PopupTownHall : public PopupDelegates
	{
	public:
		static PopupTownHall* createAsMessage(const std::string &title, const std::string &msg);
		static PopupTownHall* createAsConfirmDialogue(const std::string &title, const std::string &msg, const std::function<void()> &YesFunc);
		static PopupTownHall* create(const std::string &title, const std::string &msg, cocos2d::Label *lbl, const std::function<void()> &YesFunc);

	private:
		void initBg(const cocos2d::Size size, const std::string &title);
	};
	// pop up to choose knight
	class PopupChooseKnight : public PopupDelegates
	{
	public:
		static PopupChooseKnight* createAsMessage(const std::string &title, const std::string &msg);
		static PopupChooseKnight* createAsConfirmDialogue(const std::string &title, const std::string &msg, const std::function<void()>& add, 
			const std::function<void()>& sub,
			const std::function<void()>& knight);
		
		static PopupChooseKnight* create(const std::string &title, const std::string &msg, cocos2d::Label *intSum,
			cocos2d::Label *labelSum, cocos2d::Label *labelChoose, cocos2d::Label *intChoose,
			const std::function<void()>& add, const std::function<void()>& sub,
			const std::function<void()>& knight);
	private:
		void initBg(const cocos2d::Size size, const std::string &title);
	};
	// popup shop
	class PopupShop : public PopupDelegates
	{
	public:
		static PopupShop* createAsMessage(const std::string &title, const std::string &msg);
		static PopupShop* createAsConfirmDialogue(int &m_gold, const std::string &title, const std::string &msg,
			std::vector<Item *> &menuItem, std::vector<Item *> &menuItemShop,const std::function<void()> &YesFunc);
		static PopupShop* create(int &m_gold, const std::string &title, const std::string &msg,
			cocos2d::Label *lbl, std::vector<Item *> &menuItem, std::vector<Item *>& menuItemShop, const std::function<void()> &YesFunc);
	private:
		void initBg(const cocos2d::Size size, const std::string &title);
	};

	class PopupMainHouse : public PopupDelegates
	{
	public:
		static PopupMainHouse* createAsMessage(const std::string &title, const std::string &msg);
		static PopupMainHouse* createAsConfirmDialogue(Layer *layer, const std::string &title, const std::string &msg,
			std::vector<Item *> &menuItem, const std::function<void()> &YesFunc);
		static PopupMainHouse* create(Layer *layer, const std::string &title, const std::string &msg,
			cocos2d::Label *lbl, std::vector<Item *> &menuItem, const std::function<void()> &YesFunc);
	private:
		void initBg(const cocos2d::Size size, const std::string &title);
	};
}

#endif /* Popup_h */