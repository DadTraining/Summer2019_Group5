#include "Bullet.h"


Bullet::Bullet(Layer * _layer2D)
{
	m_sprite = Sprite::create("bullet.png");
	m_sprite->setScale(0.08);
	m_sprite->setCameraMask(2);
	//m_sprite->setPosition(p);
	m_sprite->setVisible(false);
	_layer2D->addChild(m_sprite, 11);
}

Bullet::~Bullet()
{
}

void Bullet::Init(int)
{
	
}

void Bullet::Died()
{
}

void Bullet::Shoot(Vec2 p3)
{
	

}

void Bullet::stopHide()
{
	m_sprite->setVisible(false);
}

void Bullet::setPositon(Vec2)
{
}

void Bullet::setPoint(Vec2 p1, Vec2 p2)
{
	bezier.controlPoint_1 = (Point)p1;
	bezier.controlPoint_2 = (Point)p2;
	
}

void Bullet::setPoint(Vec2 p1, Vec2 p2, Vec2 p3)
{
	bezier.controlPoint_1 =(Point) p1;
	bezier.controlPoint_2 = (Point) p2;
	bezier.endPosition = (Point)p3;
}

void Bullet::setEndPoint(Vec2 p3)
{
	bezier.endPosition = (Point) p3;
}

void Bullet::Update(float dt)
{
	auto movetToOfBullet = BezierTo::create(0.4f, bezier);
	auto callfunct = CallFunc::create(CC_CALLBACK_0(Bullet::stopHide, this));
	auto sq = Sequence::create(movetToOfBullet, callfunct, nullptr);
	m_sprite->runAction(sq);
}

void Bullet::Move(Knight * h)
{
	ccBezierConfig bezier;
	bezier.controlPoint_1 = Point(m_sprite->getPositionX(), m_sprite->getPositionY() + 100);
	bezier.controlPoint_2 = Point(Vec2(((m_sprite->getPositionX() + h->getSprite()->getPositionX()) / 2), (m_sprite->getPositionY() + h->getSprite()->getPositionY()) / 2 + 200));
	bezier.endPosition = Point(Vec2(h->getSprite()->getPosition()));

	auto movetToOfBullet = BezierTo::create(0.4f, bezier);
	auto callfunct = CallFunc::create(CC_CALLBACK_0(Bullet::stopHide, this));
	auto sq = Sequence::create(movetToOfBullet, callfunct, nullptr);

	m_sprite->runAction(sq);
}

