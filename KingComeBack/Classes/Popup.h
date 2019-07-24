//
//  Popup.h
//  dreamWeek
//
//  Created by Bilal Mirza on 07/08/2017.
//
//

#ifndef Popup_h
#define Popup_h

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Item.h"

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

	class PopupHouse : public PopupDelegates
	{
	public:
		static PopupHouse* createAsMessage(const std::string &title, const std::string &msg);
		static PopupHouse* createAsConfirmDialogue(const std::string &title, const std::string &msg,  const std::function<void()> &YesFunc, const std::function<void()> &YesFunc1);
		static PopupHouse* create(const std::string &title, const std::string &msg, cocos2d::Label *lbl, const std::function<void()> &YesFunc, const std::function<void()> &YesFunc1);

	private:
		void initBg(const cocos2d::Size size, const std::string &title);
	};

	// popup hero
	class PopupHero : public PopupDelegates
	{
	public:
		static PopupHero* createAsMessage(const std::string &title, const std::string &msg);
		static PopupHero* createAsConfirmDialogue(Layer *layer, const std::string &title, const std::string &msg, const std::function<void()> &YesFunc);
		static PopupHero* create(Layer *layer, const std::string &title, const std::string &msg, cocos2d::Label *lbl, const std::function<void()> &YesFunc);

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

	class PopupCreateKnight : public PopupDelegates
	{
	public:
		static PopupCreateKnight* createAsMessage(const std::string &title, const std::string &msg);
		static PopupCreateKnight* createAsConfirmDialogue(const std::string &title, const std::string &msg, const std::function<void()> &YesFunc);
		static PopupCreateKnight* create(const std::string &title, const std::string &msg, cocos2d::Label *lbl, const std::function<void()> &YesFunc);

	private:
		void initBg(const cocos2d::Size size, const std::string &title);
	};
}

#endif /* Popup_h */