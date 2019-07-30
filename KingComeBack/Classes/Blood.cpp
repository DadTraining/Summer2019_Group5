#pragma once
#include "Blood.h"


Blood::Blood(Sprite * m_sprite, float b)
{
	this->m_blood = b;
	spriteBlood = Sprite::create("loadingBarHouse.png");
	spriteBlood->setAnchorPoint(Vec2(0,0));
	spriteBlood->setPosition(m_sprite->getPositionX(), m_sprite->getPositionY() + m_sprite->getContentSize().height);
	m_sprite->addChild(spriteBlood);
}

Blood::Blood(float b, float m)
{
	this->m_blood = b;
	this->m_mana = m;

}

Blood::Blood(float b, float m , float g)
{
	this->m_blood = b;
	this->m_green = g;
	this->m_mana = m;
}

Blood::~Blood()
{
}

void Blood::setBlood(float b)
{
	this->m_blood = b;
}

float Blood::getBlood()
{
	return this->m_blood;
}

void Blood::setMana(float m)
{
	this->m_mana += m;
}

float Blood::getMana()
{
	return this->m_mana;
}

void Blood::setGreen(float g)
{
	this->m_green += g;
}

float Blood::getGreen()
{
	return 	this->m_green;
}

void Blood::reduceBlood(float db)
{
	this->m_blood += db;
}
