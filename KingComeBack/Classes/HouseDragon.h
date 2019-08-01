#pragma once
#include "Home.h"
#include "Defines.h"
#include "Knight.h"

USING_NS_CC;

class HouseDragon : public Home
{
private:
	Layer* _layer2D;
	Knight *m_knight;
	bool isNewKnight = false;
public:
	HouseDragon(Layer* scene, int id);
	~HouseDragon();
	void Init(int id) override;
	void Died() override;
	void LoadingBuild() override;
	void Update(float dt) override;
	Vec2 GetPosition() override;

	void RedurceBlood(float) override;
	void SetScaleBlood(float dame) override;

	void SetPosition(Vec2 vec);
	Knight* GetKnight();
	void SetIsNewKnight(bool);
	bool GetIsNewKnight();
};