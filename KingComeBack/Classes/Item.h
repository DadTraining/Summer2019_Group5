#pragma once
#include "ResourceManager.h"
#include "MyObject.h"
#define ID_ITEM_STRENGTH 1

class Item : public MyObject{
private:
	std::string m_itemAttribute;
	float m_dame;
	std::string m_state = "home";
public:
	Item(Scene* scene, int ID);
	~Item();
	void Init(int ID);
	void Died();
	std::string SetState(std::string state);
	void SetPosition();

};