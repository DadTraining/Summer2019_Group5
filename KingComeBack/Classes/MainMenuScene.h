#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"


USING_NS_CC;

class MainMenuScene : public Scene
{
public:
	MainMenuScene();
	~MainMenuScene();
	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(MainMenuScene);
private:
	Sprite *background, *logo;
	ui::Button *btnPlay, *btnBack /*hero thiện xạ*/, *itemWitch /*hero phuf thuy*/, *itemStrength/*hero suc manh*/, *itemMarksman;
	Label *lbHero, *lbWitch, *lbStrength;
	std::string text ;
	ui::TextField *textName;
};


