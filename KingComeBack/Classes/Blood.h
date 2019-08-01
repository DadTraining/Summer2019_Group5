#pragma once
#include "cocos2d.h"
#include "Defines.h"
USING_NS_CC;
class Blood {
public:
	Blood(Sprite * p,float,int);
	Blood(float, float);
	Blood(Sprite * m_sprite,float, float, float);
	~Blood();
	void setBlood(float);
	float getBlood();
	void setMana(float);
	float getMana();
	void setGreen(float);
	float getGreen();
	void reduceBlood( float );
	bool isDie();
	void handleBar();

private:
	float m_bloodMax;
	float m_blood ;
	float m_mana ;
	float m_green ;
	Sprite * spriteBlood;

	bool state;
	bool isDragon = false;

};