#pragma once
#include "cocos2d.h"
#include "Home.h"
#include "Defines.h"
#include "ui/CocosGUI.h"
#include "Blood.h"

USING_NS_CC;

class HouseDecorate : public Home
{
public:
	HouseDecorate(Layer* scene, int id);
	~HouseDecorate();
	void Init(int id) override;
	void Died() override;
	void Attack();
	void LoadingBuild() override;
	void Update(float dt) override;

private:
	float m_dame;
	Sprite *loadingBar;
	Sprite *loadingBarBg;
	GLubyte decorateHouseOpacity;
};



