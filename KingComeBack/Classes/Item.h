#pragma once
#include "ResourceManager.h"
#include "MyObject.h"
#include "ui\CocosGUI.h"
#include "Defines.h"

class Item : public MyObject{
private:
	Size screenSize;
	int m_itemAttribute;
	float m_mp;
	float m_hp;
	float m_dame;
	float m_armor;
	float m_speedAttack;
	int m_state;
	int ID;
	ui::Button *m_button;
	Vec2 prePosition;
public:
	Item();
	Item(int ID, int ID_state);
	~Item();
	void Init(int ID, int ID_state);
	void Init(int ID) override;
	void Died() override;

	int GetState();
	void SetState(int state);
	Vec2 getPrePosition();
	void setPrePosition(Vec2 _pos);
	int GetId();
	void SetId(int _ID);

	ui::Button *getButton();

	void retain();
	void ItemIsClick(int id_equip);

	bool checkAddchild = false;
};