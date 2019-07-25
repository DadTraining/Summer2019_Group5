#pragma once
#include "cocos2d.h"
#include "Home.h"
#include "Defines.h"
#include "ui/CocosGUI.h"
#include "Bullet.h"

USING_NS_CC;

class ScoutTown : public Home
{
public:
	ScoutTown (Layer* scene,int id);
	~ScoutTown ();
	void Init(int id) override;
	void Died() override;
	void Attack();
	void LoadingBuild() override;
	void Update(float dt) override;
	void Shoot(Hero *);
	void Update(float dt, Hero* h);


private:
	float m_dame;
	Sprite *loadingBar;
	Sprite *loadingBarBg;
	GLubyte scoutTownOpacity;
	std::vector < Bullet * > m_listBullets;

};

