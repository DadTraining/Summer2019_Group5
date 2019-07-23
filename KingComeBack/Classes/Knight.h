#pragma once

#include "cocos2d.h"
#include "Person.h"

USING_NS_CC;

class Knight : public Person
{
private:
	int m_currentDirect;

	void SetCurrentDirect(Vec2 vec);

	Animate* ActionKnight(std::string actionName);

	bool m_isSelected = false;
public:
	Knight(Layer* layer, int id);
	~Knight();

	void Init(int id) override;
	void Update(float dt) override;
	void Move(Vec2 vec) override;
	void Died() override;
	void Attack() override;

	void SetPositionKnight(Vec2 vec);

	void SetSelected(bool isSelected);

	bool GetSelected();

	static const int CURRENT_DIRECT_0 = 0;
	static const int CURRENT_DIRECT_1 = CURRENT_DIRECT_0 + 1;
	static const int CURRENT_DIRECT_2 = CURRENT_DIRECT_1 + 1;
	static const int CURRENT_DIRECT_3 = CURRENT_DIRECT_2 + 1;
	static const int CURRENT_DIRECT_4 = CURRENT_DIRECT_3 + 1;
	static const int CURRENT_DIRECT_5 = CURRENT_DIRECT_4 + 1;
	static const int CURRENT_DIRECT_6 = CURRENT_DIRECT_5 + 1;
	static const int CURRENT_DIRECT_7 = CURRENT_DIRECT_6 + 1;

	static const int MAX_FRAMES = 10;
	static const int MAX_LENGHT = 50;
};