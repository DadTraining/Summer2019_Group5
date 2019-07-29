#include "ScoutTown.h"

ScoutTown::ScoutTown(Layer* scene, int id)
{
	this->Init(id);
	scene->addChild(m_sprite, 10);

}

ScoutTown::~ScoutTown()
{
	delete this;
}

void ScoutTown::Init(int id)
{
	m_sprite = Sprite::create("ScoutTown2D.png");
	scoutTownOpacity = m_sprite->getOpacity();
	m_sprite->setOpacity(30);

	MyBodyParser::getInstance()->parseJsonFile("ScoutTown.json");
	auto physicBody = MyBodyParser::getInstance()->bodyFormJson(m_sprite, "ScoutTownBody", PhysicsMaterial(0, 0, 0));

	physicBody->setGravityEnable(false);
	physicBody->setRotationEnable(false);
	physicBody->setCategoryBitmask(4);
	physicBody->setCollisionBitmask(125);
	m_sprite->setPhysicsBody(physicBody);

	this->LoadingBuild();
}

void ScoutTown::Died()
{

}

void ScoutTown::Attack()
{

}

void ScoutTown::LoadingBuild()
{
	loadingBar = Sprite::create("loadingBarHouse.png");
	loadingBar->setAnchorPoint(Vec2(0, 0.5));
	loadingBar->setPosition(m_sprite->getPosition().x / 2 + m_sprite->getContentSize().width / 2, m_sprite->getPosition().y / 2);
	loadingBar->setScaleX(0);
	m_sprite->addChild(loadingBar, 1);
	loadingBarBg = Sprite::create("loadingBarBgHouse.png");
	loadingBarBg->setAnchorPoint(Vec2(0, 0.5));
	loadingBarBg->setPosition(m_sprite->getPosition().x / 2, m_sprite->getPosition().y / 2);
	m_sprite->addChild(loadingBarBg, 0);
}

void ScoutTown::Update(float dt)
{
	if (loadingBar != nullptr)
	{
		float percent = loadingBar->getScaleX();
		percent = percent + dt;
		loadingBar->setScaleX(percent);
		if (percent >= 1.0f)
		{
			m_sprite->setOpacity(scoutTownOpacity);
			loadingBar->removeFromParentAndCleanup(true);
			loadingBarBg->removeFromParentAndCleanup(true);
			m_sprite->getPhysicsBody()->setDynamic(false);
			loadingBar = nullptr;
		}
	}
}
