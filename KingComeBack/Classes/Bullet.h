#pragma once
#include "MyObject.h"
#include "Hero.h"
#include "Knight.h"
#include "Dragon.h"
class Bullet : public MyObject{
public:
	Bullet(Layer * _layer2D);
	//Bullet(Layer * _layer2D, Vec2);
	~Bullet();
	void Init(int) override;
	void Died()override;
	void Shoot(Vec2);
	void stopHide();
	void setPositon(Vec2);
	void setPoint(Vec2 p1, Vec2 p2);
	void setPoint(Vec2 p1, Vec2 p2, Vec2 p3);
	void setEndPoint(Vec2 p3);
	void Update(float dt);

	void Move(Knight * h);
	void Move(Dragon * h);
private:
	cocos2d::ccBezierConfig bezier;
};