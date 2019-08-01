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
	Vec2 GetPosition() override;
	void RedurceBlood(float dame) override;

	Sprite *loadingBar;

	bool isSelected = false;

	void SetScaleBlood(float dame) override;
private:
	Sprite *loadingBarBg;
	GLubyte hallTownOpacity;
};
