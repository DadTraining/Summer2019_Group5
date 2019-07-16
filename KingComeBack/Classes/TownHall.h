#pragma once
#include "cocos2d.h"
#include "Home.h"

USING_NS_CC;

class TownHall : public Home
{
public:
	~TownHall ();
	TownHall(Layer * scene, int id);
	void Init(int id) override; 
	void Died() override;
	void LoadingBuild() override;
	void Update(float dt) override;

	void CreateKnight();

	bool OnTouchBegan(Touch *touch, Event *unused_event);
	void OnTouchMove(Touch *touch, Event *unused_event);
	void OnTouchEnd(Touch *touch, Event *unused_event);


private:
	int id_home;
};
