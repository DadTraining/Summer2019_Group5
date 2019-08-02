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
	m_button = ui::Button::create("gold_mine.png");
	decorateHouseOpacity = m_button->getOpacity();
	m_button->setOpacity(30);
	
	MyBodyParser::getInstance()->parseJsonFile("gold_mine.json");
	auto physicBody = MyBodyParser::getInstance()->bodyFormJson(m_button, "GoldMineBody", PhysicsMaterial(0, 0, 0));

	physicBody->setGravityEnable(false);
	physicBody->setRotationEnable(false);
	physicBody->setCategoryBitmask(4);
	physicBody->setCollisionBitmask(125);
	m_button->setPhysicsBody(physicBody);

	AddBlood(id);

	SetColor(id);
	SetAmor(AMOR_HOUSE);
	float bl = BLOOD_HOUSE;
	SetBlood(bl);

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
