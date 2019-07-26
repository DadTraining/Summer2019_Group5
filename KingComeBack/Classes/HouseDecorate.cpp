#include "HouseDecorate.h"


HouseDecorate::HouseDecorate(Layer* scene, int id)
{
	this->Init(id);
	scene->addChild(m_sprite);

}

HouseDecorate::~HouseDecorate()
{
	delete this;
}

void HouseDecorate::Init(int id)
{
	m_sprite = Sprite::create("HouseDecorate.png");
	decorateHouseOpacity = m_sprite->getOpacity();
	m_sprite->setOpacity(30);
	auto physicBody = PhysicsBody::createBox(m_sprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	physicBody->setGravityEnable(false);
	physicBody->setRotationEnable(false);
	physicBody->setCategoryBitmask(4);
	physicBody->setCollisionBitmask(25);
	m_sprite->setPhysicsBody(physicBody);

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
	loadingBar->setPosition(m_sprite->getPosition().x / 2, m_sprite->getPosition().y / 2);
	loadingBar->setScaleX(0);
	m_sprite->addChild(loadingBar, 1);
	loadingBarBg = Sprite::create("loadingBarBgHouse.png");
	loadingBarBg->setAnchorPoint(Vec2(0, 0.5));
	loadingBarBg->setPosition(m_sprite->getPosition() / 2);
	m_sprite->addChild(loadingBarBg, 0);
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
			m_sprite->setOpacity(decorateHouseOpacity);
			loadingBar->removeFromParentAndCleanup(true);
			loadingBarBg->removeFromParentAndCleanup(true);
			m_sprite->getPhysicsBody()->setDynamic(false);
			loadingBar = nullptr;
		}
	}
}