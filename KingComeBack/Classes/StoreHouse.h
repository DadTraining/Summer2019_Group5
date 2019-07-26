#pragma once
#include "cocos2d.h"
#include "Home.h"
#include "Defines.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class StoreHouse : public Home
{
public:
	StoreHouse(Layer* scene, int id);
	~StoreHouse();
	void Init(int id) override;
	void Died() override;
	void Attack();
	void LoadingBuild() override;
	void Update(float dt) override;

private:
	float m_dame;
	Sprite *loadingBar;
	Sprite *loadingBarBg;
	GLubyte storeHouseOpacity;
};

