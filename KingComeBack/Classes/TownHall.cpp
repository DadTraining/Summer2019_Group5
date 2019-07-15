#include "TownHall.h"
#include "ResourceManager.h"

TownHall ::~TownHall()
{
}

TownHall::TownHall(Scene* scene, int id)
{
	Init(id);
	scene->addChild(m_sprite, 10);
	scene->addChild(this->m_sprite, 10);
}

void TownHall::Init(int id)
{
	this->m_sprite = ResourceManager::GetInstance()->GetSpriteById(id);
	this->m_sprite->setVisible(false);

	this->m_sprite->setScale(0.5);

}

void TownHall::Died()
{

	m_sprite->setVisible(false);

	this->m_sprite->setVisible(false);

}

void TownHall::CreateKnight()
{

}