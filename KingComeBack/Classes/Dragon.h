#pragma once
#include "Person.h"
#include "cocos2d.h"
class Dragon  : public MyObject{
public:
	Dragon(Layer * _layer2D);
	~Dragon();
	void Init(int) override;
	void Died() override;
	Animation* createAnimation(std::string frefixName, int pFrame, int delay);
	
private:
	const int BITMASK_LAYER_UI = 101;
	Size screenSize;
	cocos2d::Animation * animaton;
	Vec2 tempPositinSprite;
	PhysicsBody * bodyA;
	Vec2 origin;
	int direct=0;
};