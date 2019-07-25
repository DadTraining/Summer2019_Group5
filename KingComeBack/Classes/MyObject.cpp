#include "MyObject.h"

USING_NS_CC;
MyObject::MyObject()
{
}

MyObject::~MyObject()
{
}

Sprite * MyObject::getSprite()
{
	return m_sprite;
}
/*
Sprite* MyObject::DuplicateSprite(Sprite * sprite)
{
Sprite* pRet = Sprite::createWithTexture(sprite->getTexture());
if (sprite->getChildrenCount() > 0)
{
for (int child = 0; child < sprite->getChildrenCount(); child++)
{
Sprite* spriteChild = (Sprite*)sprite->getChildren().at(child);
Sprite* clone = DuplicateSprite((Sprite*)spriteChild);
clone->boundingBox() = spriteChild->boundingBox();
clone->setContentSize(spriteChild->getContentSize());
clone->setPosition(spriteChild->getPosition());
clone->setAnchorPoint(spriteChild->getAnchorPoint());
pRet->addChild(clone, spriteChild->getZOrder(), spriteChild->getTag());
}
}
return pRet;
}

*/
