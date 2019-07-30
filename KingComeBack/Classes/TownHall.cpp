#include "TownHall.h"
#include "ResourceManager.h"

TownHall ::~TownHall()
{
	delete this;
}

TownHall::TownHall(Layer* _layer, int id)
{
	this->Init(id);
	blood = new Blood(m_sprite, 1000);
	_layer->addChild(m_sprite, 10);
}

void TownHall::Init(int id)
{
	//this->m_sprite = ResourceManager::GetInstance()->GetSpriteById(id);

	m_sprite = Sprite::create("HallTown.png");
	hallTownOpacity = m_sprite->getOpacity();
	m_sprite->setOpacity(30);

	auto physicBody = PhysicsBody::createBox(m_sprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	physicBody->setGravityEnable(false);
	physicBody->setRotationEnable(false);
	physicBody->setCategoryBitmask(4);
	physicBody->setCollisionBitmask(25);

	m_sprite->setPhysicsBody(physicBody);
	this->LoadingBuild();
}

void TownHall::Died()
{
	m_sprite->removeFromParentAndCleanup(true);
}

void TownHall::LoadingBuild()
{
	loadingBar = Sprite::create("loadingBarHouse.png");
	loadingBar->setAnchorPoint(Vec2(0, 0.5));
	loadingBar->setPosition(m_sprite->getPosition().x * 2, m_sprite->getPosition().y / 2);
	loadingBar->setScaleX(0);
	m_sprite->addChild(loadingBar, 1);
	loadingBarBg = Sprite::create("loadingBarBgHouse.png");
	loadingBarBg->setAnchorPoint(Vec2(0, 0.5));
	loadingBarBg->setPosition(m_sprite->getPosition().x * 2 , m_sprite->getPosition().y / 2);
	m_sprite->addChild(loadingBarBg, 0);
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
			m_sprite->setOpacity(hallTownOpacity);
			m_sprite->getPhysicsBody()->setDynamic(false);

			loadingBar->removeFromParentAndCleanup(true);
			loadingBarBg->removeFromParentAndCleanup(true);
			loadingBar = nullptr;
		}
	}
}

void TownHall::CreateKnight()
{

}

bool TownHall::OnTouchBegin(Touch * touch, Event * unused_event)
{
	if (m_sprite->getBoundingBox().containsPoint(touch->getLocation()))
	{
		auto popup = UICustom::PopupTownHall::createAsConfirmDialogue("Town hall", "", [=]()
		{
			// event
		});
		return true;
	}
	return false;
}

void TownHall::OnTouchEnd(Touch * touch, Event * unused_event)
{
}
