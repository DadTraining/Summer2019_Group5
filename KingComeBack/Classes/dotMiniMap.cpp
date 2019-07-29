#include "dotMiniMap.h"
#define Hero 0
#define House 1
#define ScoutTown 2
dotMiniMap::dotMiniMap(Layer * layerUI, int type)
{
	switch (type)
	{
	case Hero:
		m_sprite = Sprite::create("dotHero.png");
		m_sprite->setScale(0.01);
		break;
		
	case House:
		m_sprite = Sprite::create("dotHallTown.png");
		m_sprite->setScale(1);
		break;

	case ScoutTown:
		m_sprite = Sprite::create("dotScoutTown2D.png");
		m_sprite->setScale(0.8);
		break;

	default:
		break;
	}

	Init(1);
	layerUI->addChild(m_sprite, 11);
}

dotMiniMap::~dotMiniMap()
{
}

void dotMiniMap::Init(int ID)
{
	//Sprite*  minimapSprite = Sprite::create("minimap.png");

	//minimapSprite->setScale(0.3);
	//minimapSprite->setPosition(50*screenSize.width / (2 * 256), 820*screenSize.height  / (2*512));
	m_sprite->setAnchorPoint(Vec2(0, 0));
	m_sprite->setPosition(0, 0);
	//_layerUI->addChild(minimapSprite,11);
	m_sprite->setVisible(false);
}

void dotMiniMap::Died()
{
}

void dotMiniMap::updatePosition(Vec2 newPoint)
{
	m_sprite->setPosition(newPoint);
}

void dotMiniMap::VisiableDot(bool b)
{
	if (b==true) {
		m_sprite->setVisible(true);
	}
	else {
		m_sprite->setVisible(false);
	}
}
