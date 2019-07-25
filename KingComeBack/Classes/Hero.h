#pragma once
#include "Person.h"
#include "cocos2d.h"
class Hero : public Person {
public:
	Hero(Layer * _layer2D);
	~Hero();
	void Init( int ) override;
	void Attack() override;
	void Update( float) override;
	void Move(Vec2 vec) override;
	void Died()override;
	Animation* createAnimation(std::string frefixName, int pFrame, float delay);
	

	void moveR(int, int, int);
	

	int getDirect();

	void setDirect(int);

	void getAttack(int);

	Vec2  getPositionHero();

private:
	const int BITMASK_LAYER_UI = 101;
	Size screenSize;
	cocos2d::Animation * animaton;
	Vec2 tempPositinSprite;
	PhysicsBody * bodyA;
	Vec2 origin;
	int direct=0;
	cocos2d::Action* mListAction[100];
	
};