#pragma once
#include "cocos2d.h"
#include "Home.h"
#include "Popup.h"

USING_NS_CC;

class TownHall : public Home
{
public:
	~TownHall ();
	TownHall(Layer * scene, int id);
	void Init(int id) override; 
	void Died() override;
	void LoadingBuild() override;
	void Update(float dt) override;

	void CreateKnight();

	bool OnTouchBegin(Touch * touch, Event * unused_event);
//void OnTouchMove(Touch *touch, Event *unused_event);
	void OnTouchEnd(Touch *touch, Event *unused_event);

	Sprite *loadingBar;


private:
	int id_home;
	Sprite *loadingBarBg;
	GLubyte hallTownOpacity;
};
