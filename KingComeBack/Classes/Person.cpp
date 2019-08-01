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

void Person::SetID(int i)
{
	id = i;
}

int Person::GetID()
{
	return id;
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
