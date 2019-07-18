#include "TownHall.h"
#include "ResourceManager.h"

TownHall ::~TownHall()
{
}

TownHall::TownHall(Layer* _layer, int id)
{
	this->Init(id);
	_layer->addChild(m_sprite, 10);
}

void TownHall::Init(int id)
{
	//this->m_sprite = ResourceManager::GetInstance()->GetSpriteById(id);

	m_sprite = Sprite::create("HallTown.png");
}

void TownHall::Died()
{
	m_sprite->removeFromParentAndCleanup(true);
}

void TownHall::LoadingBuild()
{

}

void TownHall::Update(float dt)
{
}

void TownHall::CreateKnight()
{

}

bool TownHall::OnTouchBegan(Touch * touch, Event * unused_event)
{
	
	return true;
}

void TownHall::OnTouchMove(Touch * touch, Event * unused_event)
{

}

void TownHall::OnTouchEnd(Touch * touch, Event * unused_event)
{
}
