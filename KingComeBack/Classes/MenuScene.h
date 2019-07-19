#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"

USING_NS_CC;

class MenuScene : public Scene
{
public:
	MenuScene();
	~MenuScene();
	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(MenuScene);
private:
	Sprite *background, *logo;
	ui::Button *btnPlay, *btnExit, *btnSetting, *btnAgainPlay;
};


