#pragma once
#include "MyObject.h"
class dotMiniMap : public MyObject {
public:
	dotMiniMap(Layer *, int type);
	~dotMiniMap();
	 void Init(int ID);
	 void Died() ;
	 void updatePosition(Vec2 p);
	 void VisiableDot(bool b);

private:
	
};
