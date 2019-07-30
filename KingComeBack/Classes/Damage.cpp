#include "Damage.h"

Damage::Damage(float d)
{
	damageNormal = d;
}

Damage::Damage(float d, float d1, float d2)
{
	damageNormal = d;
	damageSkill_1 = d1;
	damageSkill_2 = d2;
}

Damage::~Damage()
{
}

void Damage::setDamage(float d, float d1, float d2)
{
	damageNormal = d;
	damageSkill_1 = d1;
	damageSkill_2 = d2;
}

float Damage::getDamageNormal()
{
	return damageNormal;
}

float Damage::getDamageSkill_1()
{
	return damageSkill_1;
}

float Damage::getDamageSkill_2()
{
	return damageSkill_2;
}

void Damage::reduceDamageSkill_1(float d1)
{
	damageSkill_1 += d1;
}

void Damage::reduceDamageSkill_2(float d2)
{
	damageSkill_2 += d2;
}
