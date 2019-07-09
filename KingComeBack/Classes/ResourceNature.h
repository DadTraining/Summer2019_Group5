#pragma once
#include "MyObject.h"
class ResourceNature : public  MyObject {
private:
	String m_moneyAttribute;
	int m_total;
public:
	ResourceNature(Scene * scene, int ID);
	~Money();
	void Init(int ID);
	void Died();
	void Reduce(int ID);
};