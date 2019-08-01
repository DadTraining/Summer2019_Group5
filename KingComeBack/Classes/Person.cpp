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
