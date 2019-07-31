#include "HouseDecorate.h"


HouseDecorate::HouseDecorate(Layer* scene, int id)
{
	this->Init(id);
	scene->addChild(m_button, 10);

}

HouseDecorate::~HouseDecorate()
{
	delete this;
}

void HouseDecorate::Init(int id)
{
	m_button = ui::Button::create("HouseDecorate.png");
	decorateHouseOpacity = m_button->getOpacity();
	m_button->setOpacity(30);
	
	MyBodyParser::getInstance()->parseJsonFile("HouseDecorate.json");
	auto physicBody = MyBodyParser::getInstance()->bodyFormJson(m_button, "HouseDecorateBody", PhysicsMaterial(0, 0, 0));

	physicBody->setGravityEnable(false);
	physicBody->setRotationEnable(false);
	physicBody->setCategoryBitmask(4);
	physicBody->setCollisionBitmask(125);
	m_button->setPhysicsBody(physicBody);

	if (id == TEAM_BLUE)
	{
		blood = new Blood(m_sprite, 500, id);
	}
	if (id == TEAM_RED)
	{
		blood = new Blood(m_sprite, 500, id);
	}

	SetColor(id);
	SetAmor(AMOR_HOUSE);

	this->LoadingBuild();
}

void HouseDecorate::Died()
{

}

void HouseDecorate::Attack()
{

}

void HouseDecorate::LoadingBuild()
{
	loadingBar = Sprite::create("loadingBarHouse.png");
	loadingBar->setAnchorPoint(Vec2(0, 0.5));
	loadingBar->setPosition(m_button->getPosition().x / 2 + m_button->getContentSize().width / 4, m_button->getPosition().y / 2);
	loadingBar->setScaleX(0);
	m_button->addChild(loadingBar, 1);
	loadingBarBg = Sprite::create("loadingBarBgHouse.png");
	loadingBarBg->setAnchorPoint(Vec2(0, 0.5));
	loadingBarBg->setPosition(m_button->getPosition().x / 2 + m_button->getContentSize().width / 4, m_button->getPosition().y / 2);
	m_button->addChild(loadingBarBg, 0);
}

void HouseDecorate::Update(float dt)
{
	if (loadingBar != nullptr)
	{
		float percent = loadingBar->getScaleX();
		percent = percent + dt;
		loadingBar->setScaleX(percent);
		if (percent >= 1.0f)
		{
			m_button->setOpacity(decorateHouseOpacity);
			loadingBar->removeFromParentAndCleanup(true);
			loadingBarBg->removeFromParentAndCleanup(true);
			m_button->getPhysicsBody()->setDynamic(false);
			loadingBar = nullptr;
		}
	}
}

Blood * HouseDecorate::GetBlood()
{
	return blood;
}
