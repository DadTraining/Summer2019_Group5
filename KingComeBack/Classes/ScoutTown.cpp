#include "ScoutTown.h"

ScoutTown::ScoutTown(Layer* scene, int id)
{
	this->Init(id);
	
	scene->addChild(m_sprite);

	//bullet = new Bullet(scene);

	for (int i = 0; i < 2; i++)
	{
		Bullet *m_bullet1 = new Bullet(scene);
		this->m_listBullets.push_back(m_bullet1);
	}

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
	auto physicBody = PhysicsBody::createBox(m_sprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	physicBody->setGravityEnable(false);
	physicBody->setRotationEnable(false);
	physicBody->setCategoryBitmask(4);
	physicBody->setCollisionBitmask(25);
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
	loadingBar->setPosition(m_sprite->getPosition().x / 2, m_sprite->getPosition().y / 2);
	loadingBar->setScaleX(0);
	m_sprite->addChild(loadingBar, 1);
	loadingBarBg = Sprite::create("loadingBarBgHouse.png");
	loadingBarBg->setAnchorPoint(Vec2(0, 0.5));
	loadingBarBg->setPosition(m_sprite->getPosition() / 2);
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

void ScoutTown::Shoot(Knight * monster)
{
	for (auto b : m_listBullets) {
		if (b->getSprite()->isVisible()!=true)
		{
			b->getSprite()->setVisible(true);
			b->getSprite()->setPosition(m_sprite->getPositionX(), m_sprite->getPositionY() + m_sprite->getContentSize().height / 2);
			b->Move(monster);
			break;
		}
	}
	
}

void ScoutTown::Update(float dt, Knight * h)
{
	
	
	
		Shoot(h);
	
	
}




