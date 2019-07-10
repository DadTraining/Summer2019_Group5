#include "ResourceNature.h"

ResourceNature::ResourceNature(Scene * scene, int ID)
{
	this->Init(ID); //nhap id vao func init()
	scene->addChild(m_sprite);
}

void ResourceNature::Init(int ID)
{
	switch (ID)
	{
	case 0:
		m_moneyAttribute = "Gold";
		m_total = 5000;
		break;
	case 1:
		m_moneyAttribute = "Woods";
		m_total = 5;
		break;
	default:
		break;
	}
	this->m_sprite = ResourceManager::getInstance()->GetSpriteById(ID);
	Size screensize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	this->m_sprite->removeFromParent();
}

void ResourceNature::Reduce(int ID)
{
	switch (ID)
	{
	case 0:
		m_total -= 5;
		break;
	case 1:
		m_total -= 100;
		break;

	default:
		break;
	}
}
