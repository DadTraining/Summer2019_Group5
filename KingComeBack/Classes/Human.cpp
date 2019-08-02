#include "Human.h"

Human::Human()
{

}

Human::~Human()
{

}

float Human::GetMaxBlood()
{
	return m_maxBlood;
}

void Human::SetMaxBlood(float _maxBlood)
{
	m_maxBlood = _maxBlood;
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
	if (dame > 0)
	{
		m_blood = m_blood - dame;
	}
	if (m_blood <= 0)
	{
		m_sprite->setPosition(-3000, 0);
	}
}

void Human::SetScaleBlood(float bl)
{
	
	if (bl > 0)
	{
		RedurceBlood(bl);
		m_sprite->getChildByTag(TAG_SPRITE_BLOOD)->setScaleX(m_blood / m_maxBlood);
	}
}

bool Human::IsDie()
{
	if (m_blood <= 0)
		return true;
	return false;
}

Vec2 Human::GetPosition()
{
	return m_sprite->getPosition();
}

void Human::AddBlood(int id)
{
	auto bl = Sprite::create("Sprites/Loading/progress.png");
	float x = m_sprite->getPosition().x;
	float y = m_sprite->getPosition().y + m_sprite->getContentSize().height;
	bl->setAnchorPoint(Vec2::ZERO);
	//bl->setScale(0.3);
	bl->setPosition(Vec2(x, y));	
	bl->setScaleY(0.05);
	bl->setTag(TAG_SPRITE_BLOOD);

	if (id == TEAM_BLUE)
	{
		bl->setColor(Color3B::GREEN);
	}
	if (id == TEAM_RED)
	{
		bl->setColor(Color3B::RED);
	}
	m_sprite->addChild(bl);
}

