#pragma once
#include "Person.h"
#include "cocos2d.h"
#include "Blood.h"
#include "Damage.h"
#include "Defines.h"

#define Distance 20
#define Fire 100
class Dragon  : public MyObject{
public:
	Dragon(Layer * _layer2D);
	~Dragon();
	void Init(int) override;
	void Died() override;
	Animation* createAnimation(std::string frefixName, int pFrame, int delay);
	Blood * getBlood();
	void handleBloodBar();
	
	void createFire(Layer * _layer2D);

	void dragonMove(int direct);

	void dragonFire(int direct);

	void updatePositionloodBar();

	Damage * getDamage();
	

private:
	const int BITMASK_LAYER_UI = 101;
	Size screenSize;
	cocos2d::Animation * animaton;
	Vec2 tempPositinSprite;
	PhysicsBody * bodyA;
	Vec2 origin;
	int direct=0;

	Blood * blood;
	Sprite * spriteBlood, *fire;

	Damage * damage;

};