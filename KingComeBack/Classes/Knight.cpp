#include "Knight.h"
#include "Defines.h"


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

int Knight::GetCurrentDirect()
{
	return m_currentDirect;
}

void Knight::SetLastDirect(int dir)
{
	m_lastDirect = dir;
}

int Knight::GetLastDirect()
{
	return m_lastDirect;
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
	m_sprite->setCameraMask(2);
}

Knight::~Knight()
{
}

void Knight::Init(int id)
{

	if (id == TEAM_RED)
	{
		InitRed();
	}
	else if (id == TEAM_BLUE)
	{
		InitBlue();
	}
	m_currentDirect = 0;


	SetColor(id);
}

void Knight::Update(float dt)
{
	//Attack();
}

void Knight::Move(Vec2 vec)
{
	if (m_sprite->getActionByTag(TAG_ACTION_WALK) ||
		m_sprite->getActionByTag(TAG_ACTION_ATTACK))
	{
		m_sprite->stopAllActions();
	}
	m_lastDirect = m_currentDirect;
	
	SetCurrentDirect(vec);

	char actionName[MAX_LENGHT] = { 0 };
	sprintf(actionName, "knight_walk_%d000", m_currentDirect);

	m_time = m_distance / 70.0;
	auto moveTo = MoveTo::create(m_time, vec);

	count_repeat = m_time + 1;
	auto action = Repeat::create(ActionKnight(actionName), count_repeat);

	auto spaw = Spawn::create(moveTo, action, nullptr);
	spaw->setTag(TAG_ACTION_WALK);
	m_sprite->runAction(spaw);

	

}

void Knight::Died()
{
}

void Knight::InitRed()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("knight.plist", "knight.png");

	m_sprite = Sprite::createWithSpriteFrameName("knight_walk_00000.png");
	m_sprite->setScale(0.5);
	auto body = PhysicsBody::createBox(m_sprite->getContentSize() / 2, PHYSICSBODY_MATERIAL_DEFAULT);
	body->setGravityEnable(false);
	body->setCategoryBitmask(32);
	body->setRotationEnable(false);
	body->setCollisionBitmask(53);
	body->setContactTestBitmask(53);
	body->getFirstShape()->setRestitution(10);
	body->getShape(0)->setFriction(1);
	body->getShape(0)->setMass(100);

	//body->setDynamic(false);	
	m_sprite->setPhysicsBody(body);
	m_sprite->setColor(Color3B::RED);
}

void Knight::MoveRed(Vec2 vec)
{
	if (vec == Vec2::ZERO)
	{
		m_sprite->stopAllActions();
	}
	else if (!m_sprite->getActionByTag(TAG_ACTION_WALK))
	{
		SetCurrentDirect(vec);

		char actionName[MAX_LENGHT] = { 0 };
		sprintf(actionName, "knight_walk_%d000", m_currentDirect);

		m_time = m_distance / 70.0;
		auto moveTo = MoveTo::create(m_time, vec);

		count_repeat = m_time + 1;
		auto action = Repeat::create(ActionKnight(actionName), count_repeat);

		auto spaw = Spawn::create(moveTo, action, nullptr);
		spaw->setTag(TAG_ACTION_WALK);
		m_sprite->runAction(spaw);
	}
	
}

void Knight::InitBlue()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("knight.plist", "knight.png");

	m_sprite = Sprite::createWithSpriteFrameName("knight_walk_00000.png");
	m_sprite->setScale(0.5);
	auto body = PhysicsBody::createBox(m_sprite->getContentSize() / 2, PHYSICSBODY_MATERIAL_DEFAULT);
	body->setGravityEnable(false);
	body->setCategoryBitmask(16);
	body->setRotationEnable(false);
	body->setCollisionBitmask(61);
	body->setContactTestBitmask(61);
	body->getFirstShape()->setRestitution(1);
	body->getShape(0)->setFriction(1);
	body->getShape(0)->setMass(100);

	//body->setDynamic(true);
	m_sprite->setPhysicsBody(body);
}

void Knight::Attack()
{
	if (m_sprite->getActionByTag(TAG_ACTION_WALK))
	{
		m_sprite->stopActionByTag(TAG_ACTION_WALK);

		if (!m_sprite->getActionByTag(TAG_ACTION_ATTACK))
		{
			char actionName[MAX_LENGHT] = { 0 };
			sprintf(actionName, "knight_attack_%d000", m_currentDirect);
			auto spaw = Spawn::create(ActionKnight(actionName), nullptr);
			spaw->setTag(TAG_ACTION_ATTACK);
			m_sprite->runAction(RepeatForever::create(spaw));
		}		
	}
	
}

void Knight::StopAllAction()
{
	m_sprite->stopAllActions();
}

void Knight::SetDynamic(bool dynamic)
{
	m_sprite->getPhysicsBody()->setDynamic(dynamic);
}

void Knight::SetPositionKnight(Vec2 vec)
{
	m_sprite->setPosition(vec);
}

Point Knight::GetPositionKnight()
{
	return m_sprite->getPosition();
}

void Knight::SetSelected(bool isSelected)
{
	m_isSelected = isSelected;
}

bool Knight::GetSelected()
{
	return m_isSelected;
}
