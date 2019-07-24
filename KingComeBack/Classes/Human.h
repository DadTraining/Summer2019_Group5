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
	virtual void Update(float dt) = 0;

	void SetColor(int color);
	int GetColor();
protected:
	float m_blood;
	float m_amor;
	int m_color;
};
