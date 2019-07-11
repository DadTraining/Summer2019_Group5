#pragma once
#include "cocos2d.h"
#include "Human.h"

USING_NS_CC;

class Home : public Human
{
public:
	Home();
	~Home();
	virtual void Init(int id) = 0;
	virtual void Died() = 0;
	virtual void LoadingBuil() = 0;
private:

};

