#include "Human.h"

Human::Human()
{

}

Human::~Human()
{

}

void Human::SetColor(int color)
{
	m_color = color;
}

int Human::GetColor()
{
	return m_color;
}

void Human::SetAmor(float amor)
{
	m_amor = amor;
}

float Human::GetAmor()
{
	return m_amor;
}

void Human::SetBlood(float blood)
{
	m_blood = blood;
}

float Human::GetBlood()
{
	return m_blood;
}

void Human::RedurceBlood(float dame)
{
	m_blood = m_blood - dame;
}

