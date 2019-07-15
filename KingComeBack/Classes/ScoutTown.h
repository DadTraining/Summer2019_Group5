#pragma once
#include "cocos2d.h"
#include "Home.h"
#include "Defines.h"

USING_NS_CC;

class ScoutTown : public Home
{
public:
	ScoutTown (Scene* scene,int id);
	~ScoutTown ();
	void Init(int id) override;
	void Died() override;
	void Attack();
private:
	float m_dame;
};

