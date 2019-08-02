#pragma once
#include "cocos2d.h"
#include "Human.h"
#include"MyBodyParser.h"
#include"ui/CocosGUI.h"

USING_NS_CC;

class Home : public Human
{
public:
	Home();
	~Home();
	virtual void Init(int id) = 0;
	virtual void Died() = 0;
	virtual void LoadingBuild() = 0;
	virtual void Update(float dt) = 0;
	void SetButton(ui::Button *_button);
	ui::Button *GetButton();

	void AddBlood(int id) override;
protected :
	ui::Button *m_button;
};

