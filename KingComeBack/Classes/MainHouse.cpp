#include "MainHouse.h"

MainHouse::MainHouse(Layer* scene, int id)
{
	this->Init(id);
	scene->addChild(m_button, 10);

}

MainHouse::~MainHouse()
{
	delete this;
}

void MainHouse::Init(int id)
{
	m_button = ui::Button::create("HouseMain.png", "");
	mainHouseOpacity = m_button->getOpacity();
	m_button->setOpacity(30);
	
	MyBodyParser::getInstance()->parseJsonFile("PhysicsBodyMainHouse.json");
	auto physicBody = MyBodyParser::getInstance()->bodyFormJson(m_button, "MainHouseBody", PhysicsMaterial(0, 0, 0));

	physicBody->setGravityEnable(false);
	physicBody->setRotationEnable(false);
	physicBody->setCategoryBitmask(4);
	physicBody->setCollisionBitmask(125);
	m_button->setPhysicsBody(physicBody);
	this->LoadingBuild();
}

void MainHouse::Died()
{

}

void MainHouse::Attack()
{

}

void MainHouse::LoadingBuild()
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

void MainHouse::Update(float dt)
{
	if (loadingBar != nullptr)
	{
		float percent = loadingBar->getScaleX();
		percent = percent + dt;
		loadingBar->setScaleX(percent);
		if (percent >= 1.0f)
		{
			m_button->setOpacity(mainHouseOpacity);
			loadingBar->removeFromParentAndCleanup(true);
			loadingBarBg->removeFromParentAndCleanup(true);
			m_button->getPhysicsBody()->setDynamic(false);
			loadingBar = nullptr;
		}
	}
}
