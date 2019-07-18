#include "ScoutTown.h"

ScoutTown::ScoutTown(Layer* scene, int id)
{
	this->Init(id);
	scene->addChild(m_sprite);
}

ScoutTown::~ScoutTown()
{

}  

void ScoutTown::Init(int id)
{
	m_sprite = Sprite::create("ScoutTown2D.png");
	auto physicBody = PhysicsBody::createBox(m_sprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	physicBody->setCategoryBitmask(0x08);
	physicBody->setCollisionBitmask(0x02);
	physicBody->setContactTestBitmask(0x01);

}

void ScoutTown::Died()
{

}

void ScoutTown::Attack()
{

}

void ScoutTown::LoadingBuild()
{
}

void ScoutTown::Update(float dt)
{
}
