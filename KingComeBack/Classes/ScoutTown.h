#pragma once
#include "cocos2d.h"
#include "Home.h"
#include "Defines.h"
#include "ui/CocosGUI.h"
#include "Blood.h"
#include "Bullet.h"
#include "Knight.h"
#include "Damage.h"
#include "Skill.h"
#include "dotMiniMap.h"

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
	void Shoot(Knight *);
	void Update(float dt, Knight* h);
	dotMiniMap * getDotMiniMap();
	void setDotMiniMap(dotMiniMap * d);

	Blood * getBlood();

	Damage * getDamage();

	Skill * getSkill();
private:
	
	Sprite *loadingBar;
	Sprite *loadingBarBg;
	GLubyte scoutTownOpacity;
	Blood *blood;
	std::vector < Bullet * > m_listBullets;

	Damage *d;

	Skill * s;

	dotMiniMap * dot;


};

