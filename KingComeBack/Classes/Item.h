#pragma once
#include "ResourceManager.h"
#include "MyObject.h"
#include "ui\CocosGUI.h"
#define ID_ITEM_STRENGTH 1
#define ID_ITEM_AGILITY 2
#define ID_ITEM_INTELIGENT 3
#define ID_STATE_HOME 4
#define ID_STATE_WAREHOUSE 5
#define ID_STATE_EQUIPMENT 6

#define HP 7
#define MP 8
#define WEAPON 9
#define HAT	10

class Item : public MyObject{
private:
	Size screenSize;
	int m_itemAttribute;
	float m_dame;
	int m_state;
	ui::Button *m_button;
public:
	Item();
	Item(Layer* layer, int ID);
	~Item();
	void Init(int ID);
	void Died();
	int SetState(int state);
	void SetPosition(Ref *ref);
	ui::Button *getButton();

	Item *create(Layer * layer, int ID);
	void retain();
	void ItemIsClick(int id_equip);
};