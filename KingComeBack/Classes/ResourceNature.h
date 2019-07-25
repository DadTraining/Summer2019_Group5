#pragma once
#include"ResourceManager.h"
#include "MyObject.h"
class ResourceNature : public  MyObject {
private:
	std::string m_moneyAttribute;
	int m_total;
public:
	ResourceNature(Scene * scene, int ID);
	
	void Init(int ID);
	void Died();
	void Reduce(int ID);
};