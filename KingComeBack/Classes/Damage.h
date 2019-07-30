#pragma once
class Damage {

public:
	Damage(float d);
	Damage(float d, float d1, float d2);
	~Damage();
	void setDamage(float d, float d1, float d2);
	float getDamageNormal();
	float getDamageSkill_1();
	float getDamageSkill_2();
	void reduceDamageSkill_1(float d1);
	void reduceDamageSkill_2(float d2);
private:
	float damageNormal;
	float damageSkill_1;
	float damageSkill_2;
};