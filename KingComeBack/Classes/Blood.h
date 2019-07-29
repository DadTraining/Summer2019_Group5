#pragma once
#include "cocos2d.h"
class Blood {
public:
	Blood(float);
	Blood(float, float);
	Blood(float, float, float);
	~Blood();
	void setBlood(float);
	float getBlood();
	void setMana(float);
	float getMana();
	void setGreen(float);
	float getGreen();
	void reduceBlood( float );

private:
	float m_blood ;
	float m_mana ;
	float m_green ;
};