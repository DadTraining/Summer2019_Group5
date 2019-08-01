#pragma once
#include "cocos2d.h"
#include "MyObject.h"
#include "Defines.h"

USING_NS_CC;

class Human : public MyObject
{
public:
	Human();
	~Human();
	virtual void Init(int id) = 0;
	virtual void Died() = 0;
	virtual void Update(float dt) = 0;

	float GetMaxBlood();
	void SetMaxBlood(float _maxBlood);
	void SetColor(int color);
	int GetColor();
	void SetAmor(float amor);
	float GetAmor();
	void SetBlood(float blood);
	float GetBlood();
	virtual void RedurceBlood(float);
	virtual void SetScaleBlood(float bl);
	
	bool IsDie();
	virtual Vec2 GetPosition();
protected:
	float m_blood;
	float m_amor;
	int m_color;
	float m_maxBlood;
};

