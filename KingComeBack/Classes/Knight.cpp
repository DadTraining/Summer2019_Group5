#include "Knight.h"


void Knight::SetCurrentDirect(Vec2 vec)
{
	direct = Vec2(m_sprite->getPosition(), vec);
	m_distance = vec.distance(m_sprite->getPosition());

	if (direct.x > 0 && direct.y > 0 && direct.y / direct.x > 0.5 && direct.y / direct.x <= 2.5)
	{
		m_currentDirect = CURRENT_DIRECT_1;
	}
	else if (direct.x / direct.y < 0.5 && direct.x / direct.y > -0.5 && direct.y > 0)
	{
		m_currentDirect = CURRENT_DIRECT_2;
	}
	else if (direct.x < 0 && direct.y > 0 && direct.y / direct.x <= -0.5 && direct.y / direct.x >= -2.5)
	{
		m_currentDirect = CURRENT_DIRECT_3;
	}
	else if (direct.x < 0 && direct.y / direct.x > -0.5 && direct.y / direct.x < 0.5)
	{
		m_currentDirect = CURRENT_DIRECT_4;
	}
	else if (direct.x < 0 && direct.y < 0 && direct.y / direct.x > 0.5 && direct.y / direct.x <= 2.5)
	{
		m_currentDirect = CURRENT_DIRECT_5;
	}
	else if (direct.x / direct.y < 0.5 && direct.x / direct.y > -0.5 && direct.y < 0)
	{
		m_currentDirect = CURRENT_DIRECT_6;
	}
	else if (direct.x > 0 && direct.y < 0 && direct.y / direct.x <= -0.5 && direct.y / direct.x >= -2.5)
	{
		m_currentDirect = CURRENT_DIRECT_7;
	}
	else if (direct.x > 0 && direct.y / direct.x > -0.5 && direct.y / direct.x < 0.5)
	{
		m_currentDirect = CURRENT_DIRECT_0;
	}
}

Animate* Knight::ActionKnight(std::string actionName)
{
	Vector<SpriteFrame*> animateFrames;

	for (int index = 0; index < MAX_FRAMES; index++)
	{
		char buffer[MAX_LENGHT] = { 0 };
		sprintf(buffer, "%d.png", index);

		std::string str = actionName + buffer;

		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animateFrames.pushBack(frame);
	}
	auto animationFunc = Animation::createWithSpriteFrames(animateFrames, 0.1f);
	animateFrames.clear();

	Animate* animate = Animate::create(animationFunc);
	animate->retain();

	return animate;
}

Knight::Knight(Layer * layer, int id)
{
	Init(id);
	layer->addChild(m_sprite);
}

Knight::~Knight()
{
}

void Knight::Init(int id)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("knight.plist", "knight.png");

	m_sprite = Sprite::createWithSpriteFrameName("knight_walk_00000.png");

	auto body = PhysicsBody::createBox(m_sprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	body->setGravityEnable(false);
	body->setCategoryBitmask(16);
	body->setCollisionBitmask(5);
	m_sprite->setPhysicsBody(body);

	SetColor(id);
}

void Knight::Update(float dt)
{
	Attack();
}

void Knight::Move(Vec2 vec)
{
	SetCurrentDirect(vec);

	char actionName[MAX_LENGHT] = { 0 };
	sprintf(actionName, "knight_walk_%d000", m_currentDirect);

	m_time = m_distance / 70.0;
	auto moveTo = MoveTo::create(m_time, vec);

	count_repeat = m_time + 1;
	auto action = Repeat::create(ActionKnight(actionName), count_repeat);

	auto spaw = Spawn::create(moveTo, action, nullptr);
	m_sprite->runAction(spaw);
}

void Knight::Died()
{
}

void Knight::Attack()
{
	char actionName[MAX_LENGHT] = { 0 };
	sprintf(actionName, "knight_attack_%d000", m_currentDirect);
	auto spaw = Spawn::create(ActionKnight(actionName), nullptr);
	m_sprite->runAction(spaw);
}

void Knight::SetPositionKnight(Vec2 vec)
{
	m_sprite->setPosition(vec);
}

void Knight::SetSelected(bool isSelected)
{
	m_isSelected = isSelected;
}

bool Knight::GetSelected()
{
	return m_isSelected;
}
