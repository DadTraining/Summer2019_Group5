#pragma once
#include "Blood.h"





Blood::Blood(Sprite * m_sprite, float m_input)
{
	this->m_blood = m_input;
	spriteBlood = Sprite::create("loadingBarHouse.png");
	spriteBlood->setAnchorPoint(Vec2(0,0));
	spriteBlood->setPosition(m_sprite->getPositionX(), m_sprite->getPositionY() + m_sprite->getContentSize().height);
	m_sprite->addChild(spriteBlood,12);

}

Blood::Blood(float m_input, float m)
{
	this->m_blood = m_input;
	this->m_mana = m;

}

Blood::Blood(Sprite * m_sprite,float m_input, float m , float g)
{
	this->m_blood = m_input;
	this->m_green = g;
	this->m_mana = m;
	spriteBlood = Sprite::create("bloodBar.png");
	spriteBlood->setPosition(322, 97);
	spriteBlood->setAnchorPoint(Vec2(0, 0));
	spriteBlood->setPosition(m_sprite->getPositionX(), m_sprite->getPositionY() + m_sprite->getContentSize().height);
	m_sprite->addChild(spriteBlood, 12);
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
	handleBar();
}

bool Blood::stateSprite()
{
	if (m_blood <5) {
		return false;
	}
	else return true;
}

void Blood::handleBar()
{
	if (m_blood > 0) {
		spriteBlood->setScaleX(m_blood/ m_input);
	}
	else
	{
		spriteBlood->setVisible(false);
	} 
	
	
}
