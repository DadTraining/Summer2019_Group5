#include "Blood.h"
#pragma once

Blood::Blood(float b)
{
	this->m_blood = b;
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
	this->m_blood += b;
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
