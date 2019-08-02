#pragma once
#include "cocos2d.h"
#include "Human.h"
#include "MyBodyParser.h"

USING_NS_CC;

class Person : public Human
{
public:
	Person ();
	~Person();
	virtual void Init(int id) = 0;
	virtual void Update();
	virtual void Move(Vec2 vec) = 0;
	virtual void Died() = 0;
	virtual void Attack(Human*, float) = 0;

	void SetDame(float dame);
	float GetDame();

	int checkTrueSkill_2( Vec2  v);
	void AddBlood(int id) override;
protected:
	float m_speedMovement;
	float m_dame;
	float m_range;
};

