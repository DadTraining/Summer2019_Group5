#include "HouseDragon.h"

HouseDragon::HouseDragon(Layer * layer, int id)
{
	Init(id);
	layer->addChild(m_sprite);
	_layer2D = layer;
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
	AddBlood();
	float bl = BLOOD_HOUSE;
	SetBlood(bl);
}

void HouseDragon::Died()
{
}

void HouseDragon::LoadingBuild()
{
}

void HouseDragon::Update(float dt)
{
	static float count = 0.0;
	if (count >= 3.0)
	{
		m_knight = new Knight(_layer2D, TEAM_RED);	
		int dir = rand() % (100 + 1 - 50) + 50;
		m_knight->SetPositionKnight(Vec2(m_sprite->getPosition().x + dir,
			m_sprite->getPosition().y - m_sprite->getContentSize().height + dir));
		count = 0;
		isNewKnight = true;
	}
	count += dt;
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

Knight* HouseDragon::GetKnight()
{
	return m_knight;
}

void HouseDragon::SetIsNewKnight(bool is)
{
	isNewKnight = is;
}

bool HouseDragon::GetIsNewKnight()
{
	return isNewKnight;
}

void HouseDragon::AddBlood()
{
	auto blood = Sprite::create("loadingBarHouse.png");
	float x = m_sprite->getPosition().x + m_sprite->getContentSize().width / 4;
	float y = m_sprite->getPosition().y + m_sprite->getContentSize().height;
	blood->setPosition(Vec2(x, y));
	blood->setTag(TAG_BLOOD);
	blood->setColor(Color3B::RED);
	m_sprite->addChild(blood);
}
