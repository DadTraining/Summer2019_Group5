#include "Person.h"

Person::Person()
{

}
 
Person::~Person()
{

}

void Person::Update()
{
}

void Person::SetDame(float dame)
{
	m_dame = dame;
}

float Person::GetDame()
{
	return m_dame;
}

int Person::checkTrueSkill_2(Vec2  v)
{

	float temp = (this->getSprite()->getPosition().x - v.x) / (this->getSprite()->getPosition().y);
	if (temp > -0.5 && temp <0.5  &&  v.x > 0) {
		return 1;
	}
	if (temp > 0.5 && temp < 1.5 && v.x>0) {
		return 2;
	}
	if (temp > 1.5 && v.x>0) {
		return 3;
	}
	if (temp < -1.5 && v.x <0) {
		return 4;
	}
	if (temp > -1.5 && temp <-0.5 && v.x <0) {
		return 5;
	}
	if (temp > -0.5 && temp <0.5  &&  v.x < 0) {
		return 6;
	}
	if (temp > 0.5 && temp < 1.5 && v.x<0) {
		return 7;
	}
	if (temp > 1.5 && v.x<0) {
		return 0;
	}
}

void Person::AddBlood(int id)
{
	auto bl = Sprite::create("Sprites/Loading/progress.png");
	float x = m_sprite->getPosition().x;
	float y = m_sprite->getPosition().y + m_sprite->getContentSize().height;
	bl->setAnchorPoint(Vec2::ZERO);
	//bl->setScale(0.3);
	bl->setPosition(Vec2(x, y));
	bl->setScaleY(0.1);
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
