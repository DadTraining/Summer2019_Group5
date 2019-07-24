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
	void update(float dt) ;

	bool OnTouchBegan(Touch *touch, Event *unused_event);
	void OnTouchMove(Touch *touch, Event *unused_event);
	void OnTouchEnd(Touch *touch, Event *unused_event);

	void AddListener();
	void heroAnimation(int);

	void createani();
	CREATE_FUNC(MainMenuScene);
private:
	Sprite *background, *logo, *itemMarksman;
	ui::Button *btnNext, *btnBack /*hero thiện xạ*/, *itemWitch /*hero phuf thuy*/, *itemStrength/*hero suc manh*/;
	Label *lbHero;
	cocos2d::Animation * animation;
	cocos2d::Action* mListAction[100];
	Vec2  mCurrentTouch;
};

