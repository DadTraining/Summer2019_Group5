#include "HouseDragon.h"

HouseDragon::HouseDragon(Layer * layer, int id)
{
	Init(id);
	layer->addChild(m_sprite);
}

HouseDragon::~HouseDragon()
{
}

void HouseDragon::Init(int id)
{
	m_sprite = Sprite::create("DragonHouse.png");
	//m_houseDragon->setPosition(mapTopRight->getPosition() + mapTopRight->getContentSize() * 8 / 9);
	//m_houseDragon->setScale(1);
	m_sprite->setCameraMask(2);

	auto body = PhysicsBody::create();
	body->setCategoryBitmask(4);
	body->setDynamic(false);
	m_sprite->setPhysicsBody(body);

	SetColor(id);
	SetAmor(60);
}

void HouseDragon::Died()
{
}

void HouseDragon::LoadingBuild()
{
}

void HouseDragon::Update(float dt)
{
	/*static float count = 0.0;
	if (count == 5.0)*/
}

Vec2 HouseDragon::GetPosition()
{
	return m_sprite->getPosition();
}

void HouseDragon::RedurceBlood(float blood)
{
	if (blood > 0)
	{
		m_blood -= blood;
	}
}

void HouseDragon::SetScaleBlood(float dame)
{
	RedurceBlood(dame);
	if (m_blood > 0)
	{
		m_sprite->getChildByName(TAG_BLOOD)->setScaleX(m_blood / BLOOD_HOUSE);
	}
}

void HouseDragon::SetPosition(Vec2 vec)
{
	m_sprite->setPosition(vec);
}
