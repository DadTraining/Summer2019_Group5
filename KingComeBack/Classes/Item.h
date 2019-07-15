#pragma once
#include "ResourceManager.h"
#include "MyObject.h"
#define ID_ITEM_STRENGTH 1

class Item : public MyObject{
private:
	String 	m_itemAttribute;
	float m_dame;
	String m_state = "home";
public:
	Item(Scene* scene, int ID);
	~Item();
	void Init(int ID);
	void Died();
	String SetState(String state);
	void SetPosition();

};