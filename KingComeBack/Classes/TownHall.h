#pragma once
#include "cocos2d.h"
#include "Home.h"
#include "Popup.h"
#include "Blood.h"

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

	Sprite *loadingBar;

	bool isSelected = false;

	void ScaleBlood(float dame);
private:
	int id_home;
	Sprite *loadingBarBg;
	GLubyte hallTownOpacity;
};
