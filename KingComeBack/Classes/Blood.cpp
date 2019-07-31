#pragma once
#include "Blood.h"





Blood::Blood(Sprite * m_sprite, float bloodMax, int color)
{
	this->m_blood = bloodMax;
	m_bloodMax = bloodMax;
	spriteBlood = Sprite::create("loadingBarHouse.png");
	
	//spriteBlood->setAnchorPoint(Vec2(0,0));
	spriteBlood->setPosition(m_sprite->getPositionX(), m_sprite->getPositionY() + m_sprite->getContentSize().height);
	spriteBlood->setCameraMask(2);

	
	
	if (color == TEAM_BLUE)
	{
		spriteBlood->setColor(Color3B::GREEN);
	}
	if (color == TEAM_RED)
	{
		spriteBlood->setColor(Color3B::RED);
	}
	
	m_sprite->addChild(spriteBlood,12);

}

Blood::Blood(float bloodMax, float m)
{
	this->m_blood = bloodMax;
	this->m_mana = m;
	
	isDragon = true;

}

Blood::Blood(Sprite * m_sprite,float b, float m , float g)
{
	this->m_blood = b;
	m_bloodMax = b;
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
	if (isDragon == false) {
		handleBar();
	}
	
}

bool Blood::isDie()
{
	if (m_blood <=0) {
		return true;
	}
	else return false;
}

void Blood::handleBar()
{

	if (m_blood <= 0) {
		spriteBlood->setVisible(false);
	}
	else {
		spriteBlood->setScaleX(m_blood / m_bloodMax);
	}
		
		
}
