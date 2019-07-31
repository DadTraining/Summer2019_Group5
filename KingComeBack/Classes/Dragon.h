#pragma once
#include "Person.h"
#include "cocos2d.h"
#include "Blood.h"
#include "Damage.h"
#include "Defines.h"
#include "Knight.h"

#define Distance 20
#define Fire 100
class Dragon  : public Person{
public:
	Dragon(Layer * _layer2D, int id);
	~Dragon();
	void Init(int) override;
	void Died() override;
	void Update(float dt) override;

	Animation* createAnimation(std::string frefixName, int pFrame, int delay);
	Blood * getBlood();
	void handleBloodBar();
	
	void createFire(Layer * _layer2D);

	void dragonMove(int direct);

	void dragonFire(int direct);

	void updatePositionloodBar();

	Damage * getDamage();

	// Code Tuan
	void SetDirect(Vec2 vec);
	void AnimateStand();
	Animate* ActionDragon(std::string name, int begin, int end);
	void Move(Vec2 vec) override;
	void Attack() override;
	

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

	// code tuan
	Vec2 m_direct;
	int m_currentDirect;
	float m_distance;
};