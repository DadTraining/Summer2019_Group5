#pragma once
#include "cocos2d.h"
USING_NS_CC;
class MyObject {
protected:
	Sprite* m_sprite;
public:
	MyObject();
	~MyObject();
	virtual void Init(int ID) = 0;
	virtual void Died() = 0;
	//Sprite * DuplicateSprite(Sprite * sprite);
	Sprite *getSprite();
};