#include "TownHall.h"
#include "ResourceManager.h"

TownHall ::~TownHall()
{
	delete this;
}

TownHall::TownHall(Layer* _layer, int id)
{
	this->Init(id);

	//blood = new Blood(m_sprite, 1000);
	_layer->addChild(m_button, 10);
}

void TownHall::Init(int id)
{
	//this->m_button = ResourceManager::GetInstance()->GetSpriteById(id);

	m_button = ui::Button::create("HallTown.png", "");
	hallTownOpacity = m_button->getOpacity();
	m_button->setOpacity(30);

	MyBodyParser::getInstance()->parseJsonFile("HouseDecorate.json");
	auto physicBody = MyBodyParser::getInstance()->bodyFormJson(m_button, "HouseDecorateBody", PhysicsMaterial(0, 0, 0));

	physicBody->setGravityEnable(false);
	physicBody->setRotationEnable(false);
	physicBody->setCategoryBitmask(4);
	physicBody->setCollisionBitmask(125);

	/*auto blood = Sprite::create("loadingBarHouse.png");
	float x = m_button->getPosition().x + m_button->getContentSize().width / 4;
	float y = m_button->getPosition().y + m_button->getContentSize().height;
	blood->setPosition(Vec2(x, y));
	m_button->addChild(blood);*/
	blood = new Blood(m_sprite, 500, id);
	SetColor(id);
	SetAmor(id);

	m_button->setPhysicsBody(physicBody);


	this->LoadingBuild();
}

void TownHall::Died()
{
	m_button->removeFromParentAndCleanup(true);
}

void TownHall::LoadingBuild()
{
	loadingBar = Sprite::create("loadingBarHouse.png");
	loadingBar->setAnchorPoint(Vec2(0, 0.5));
	loadingBar->setPosition(m_button->getPosition().x * 2 + m_button->getContentSize().width / 4, m_button->getPosition().y / 2);
	loadingBar->setScaleX(0);
	m_button->addChild(loadingBar, 1);
	loadingBarBg = Sprite::create("loadingBarBgHouse.png");
	loadingBarBg->setAnchorPoint(Vec2(0, 0.5));
	loadingBarBg->setPosition(m_button->getPosition().x * 2 + m_button->getContentSize().width / 4, m_button->getPosition().y / 2);
	m_button->addChild(loadingBarBg, 0);
}

void TownHall::Update(float dt)
{
	if (loadingBar != nullptr)
	{
		float percent = loadingBar->getScaleX();
		percent = percent + dt;
		loadingBar->setScaleX(percent);
		if (percent >= 1.0f)
		{
			m_button->setOpacity(hallTownOpacity);
			m_button->getPhysicsBody()->setDynamic(false);

			loadingBar->removeFromParentAndCleanup(true);
			loadingBarBg->removeFromParentAndCleanup(true);
			loadingBar = nullptr;
		}
	}
}

void TownHall::OnTouchEnd(Touch * touch, Event * unused_event)
{
}

Blood * TownHall::GetBlood()
{
	return blood;
}
