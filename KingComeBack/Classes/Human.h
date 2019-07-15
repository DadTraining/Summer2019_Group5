#pragma once
#include "cocos2d.h"
#include "MyObject.h"

USING_NS_CC;

class Human : public MyObject
{
public:
	Human();
	~Human();
	virtual void Init(int id) = 0;
	virtual void Died() = 0;
private:
	float m_blood;
	float m_amor;
};

