#include "Home.h"

Home::Home()
{

}

Home::~Home()
{

}

void Home::SetButton(ui::Button * _button)
{
	m_button = _button;
}

ui::Button * Home::GetButton()
{
	return m_button;
}

void Home::AddBlood(int id)
{
	auto bl = Sprite::create("Sprites/Loading/progress.png");
	float x = m_button->getPosition().x;
	float y = m_button->getPosition().y + m_button->getContentSize().height;
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
	m_button->addChild(bl);
}

