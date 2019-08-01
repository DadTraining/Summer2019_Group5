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

	// Add Blood
	auto blood = Sprite::create("loadingBarHouse.png");
	float x = m_button->getPosition().x + m_button->getContentSize().width / 4;
	float y = m_button->getPosition().y + m_button->getContentSize().height;
	blood->setPosition(Vec2(x, y));
	blood->setTag(TAG_BLOOD);
	blood->setColor(Color3B::GREEN);
	m_button->addChild(blood);

	SetColor(id);
	SetAmor(id);
	float bl = BLOOD_HOUSE;
	SetBlood(bl);

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

Vec2 TownHall::GetPosition()
{
	return m_button->getPosition();
}

void TownHall::RedurceBlood(float dame)
{
	if (dame > 0)
	{
		m_blood = m_blood - dame;
	}
	if (m_blood <= 0)
	{
		m_button->setPosition(Vec2(-3000, 0));
	}
}

void TownHall::SetScaleBlood(float dame)
{
	RedurceBlood(dame);
	if (m_blood > 0)
	{
		auto bl = m_button->getChildByTag(TAG_BLOOD);
		bl->setScaleX(m_blood / BLOOD_HOUSE);
	}
	
}
