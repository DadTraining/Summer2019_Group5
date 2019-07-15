#pragma once
#include "cocos2d.h"
#include "Home.h"

USING_NS_CC;

class TownHall : public Home
{
public:
	~TownHall ();
	TownHall(Scene * scene, int id);
	void Init(int id) override; 
	void Died() override;
	void CreateKnight();
private:
	int id_home;
};
