#include "Dragon.h"



Dragon::Dragon(Layer * _layer2D, int id)
{
	screenSize = Director::getInstance()->getVisibleSize();
	Init(id);
	_layer2D->addChild(m_sprite,10);
	
	AnimateStand();
	createFire(_layer2D);
	AddBlood();
}

Dragon::~Dragon()
{
}


void Dragon::Init(int id)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("dragon.plist", "dragon.png");

	m_sprite = Sprite::createWithSpriteFrameName("_dragon_000.png");

	MyBodyParser::getInstance()->parseJsonFile("dragon_body.json");
	auto bodyA = MyBodyParser::getInstance()->bodyFormJson(m_sprite, "DragonBodyPhysic", PhysicsMaterial(0, 0, 0));
	
	m_sprite->setScale(1.5);

	bodyA->setGravityEnable(false);
	bodyA->setCategoryBitmask(16);
	bodyA->setCollisionBitmask(5);
	bodyA->setRotationEnable(false);
	bodyA->setDynamic(true);
	m_sprite->setPhysicsBody(bodyA);

	SetColor(id);
	SetBlood(1000);
	m_maxBlood = 1000;
	SetAmor(50);
	SetDame(200);
}

void Dragon::Died()
{
}

void Dragon::Update(float dt)
{
}

Animation * Dragon::createAnimation(std::string frefixName, int begin, int  end )
{
	Vector<SpriteFrame*> animFrames;


	for (int index = begin ; index <= end; index++)
	{


		char buffer[20] = { 0 };
		
			sprintf(buffer, "%d.png", index);

		std::string str = frefixName + buffer;

		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);

		animFrames.pushBack(frame);

	}
	auto animatonFunc = Animation::createWithSpriteFrames(animFrames, 0.2f);

	animFrames.clear();
	return animatonFunc;
}




void Dragon::createFire(Layer * _layer2D)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fire.plist", "fire.png");
	fire = Sprite::createWithSpriteFrameName("red00.png");
	fire->setAnchorPoint(Vec2(0.5, 0));
	fire->setPosition(m_sprite->getPosition());
	fire->setCameraMask(2);
	fire->setVisible(false);
	_layer2D->addChild(fire, 100);
}

void Dragon::dragonMove(int direct)
{
	Animate* animate;
	MoveTo * moveTo;
	switch (direct)
	{
	case 0:
		animate = Animate::create(createAnimation("_dragon_00", 160, 191));
		moveTo = MoveTo::create(3,Vec2(m_sprite->getPositionX()+ Distance, m_sprite->getPositionY() - Distance) );
		break;
	case 1:
		 animate = Animate::create(createAnimation("_dragon_00", 128, 159));
		 moveTo = MoveTo::create(3, Vec2(m_sprite->getPositionX() + Distance, m_sprite->getPositionY() ));
		break;
	case 2:
		 animate = Animate::create(createAnimation("_dragon_00", 96, 123));
		 moveTo = MoveTo::create(3, Vec2(m_sprite->getPositionX() + Distance, m_sprite->getPositionY() + Distance));
		break;
	case 3:
		 animate = Animate::create(createAnimation("_dragon_00", 64, 95));
		 moveTo = MoveTo::create(3, Vec2(m_sprite->getPositionX() , m_sprite->getPositionY() + Distance));
		break;
	case 4:
		 animate = Animate::create(createAnimation("_dragon_00", 32, 63));
		 moveTo = MoveTo::create(3, Vec2(m_sprite->getPositionX() - Distance, m_sprite->getPositionY() + Distance));
		break;
	case 5:
		 animate = Animate::create(createAnimation("_dragon_00", 0, 31));
		 moveTo = MoveTo::create(3, Vec2(m_sprite->getPositionX() - Distance, m_sprite->getPositionY() ));
		break;
	case 6: 
		 animate = Animate::create(createAnimation("_dragon_00", 224, 255));
		 moveTo = MoveTo::create(3, Vec2(m_sprite->getPositionX() - Distance, m_sprite->getPositionY() - Distance));
		break;
	case 7:
		
		 animate = Animate::create(createAnimation("_dragon_00", 192, 223));
		 moveTo = MoveTo::create(3, Vec2(m_sprite->getPositionX() , m_sprite->getPositionY() - Distance));
		break;

	default:
		break;
	}
	
	animate->retain();
	m_sprite->stopAllActions();
	m_sprite->runAction(Repeat::create(animate,1));
	m_sprite->runAction(moveTo);


}

void Dragon::dragonFire(int direct)
{
	switch (direct)
	{
	case 0:
		fire->setPosition(Vec2(m_sprite->getPositionX() + Fire, m_sprite->getPositionY() - Fire));
		break;
	case 1:
		fire->setPosition(Vec2(m_sprite->getPositionX() + Fire, m_sprite->getPositionY() ));
		break;
	case 2:
		fire->setPosition(Vec2(m_sprite->getPositionX() + Fire, m_sprite->getPositionY() + Fire));
		break;
	case 3:
		fire->setPosition(Vec2(m_sprite->getPositionX() , m_sprite->getPositionY() + Fire));
		break;
	case 4:
		fire->setPosition(Vec2(m_sprite->getPositionX() - Fire, m_sprite->getPositionY() + Fire));
		break;
	case 5:
		fire->setPosition(Vec2(m_sprite->getPositionX() - Fire, m_sprite->getPositionY() ));
		break;
	case 6:
		fire->setPosition(Vec2(m_sprite->getPositionX() - Fire, m_sprite->getPositionY() - Fire));
		break;
	case 7:
		fire->setPosition(Vec2(m_sprite->getPositionX() , m_sprite->getPositionY() - Fire));
		break;
		
	default:
		break;
	}
	auto animate = Animate::create(createAnimation("red0",0, 2));
	fire->runAction(Repeat::create(animate, 1));
	fire->setVisible(true);
}



Damage * Dragon::getDamage()
{
	return damage;
}

void Dragon::AddBlood()
{
	auto bl = Sprite::create("Sprites/Loading/progress.png");
	float x = m_sprite->getPosition().x + m_sprite->getContentSize().width / 2;
	float y = m_sprite->getPosition().y + m_sprite->getContentSize().height;
	bl->setPosition(Vec2(x, y));
	bl->setScale(0.3);
	bl->setTag(TAG_SPRITE_BLOOD);
	m_sprite->addChild(bl);
}

// code Tuan
void Dragon::SetDirect(Vec2 vec)
{
	m_direct = Vec2(m_sprite->getPosition(), vec);
	m_distance = vec.distance(m_sprite->getPosition());

	if (m_direct.x > 0 && m_direct.y > 0 && m_direct.y / m_direct.x > 0.5 && m_direct.y / m_direct.x <= 2.5)
	{
		m_currentDirect = Knight::CURRENT_DIRECT_1 + 1;
	}
	else if (m_direct.x / m_direct.y < 0.5 && m_direct.x / m_direct.y > -0.5 && m_direct.y > 0)
	{
		m_currentDirect = Knight::CURRENT_DIRECT_2 + 1;
	}
	else if (m_direct.x < 0 && m_direct.y > 0 && m_direct.y / m_direct.x <= -0.5 &&
		m_direct.y / m_direct.x >= -2.5)
	{
		m_currentDirect = Knight::CURRENT_DIRECT_3 + 1;
	}
	else if (m_direct.x < 0 && m_direct.y / m_direct.x > -0.5 && m_direct.y / m_direct.x < 0.5)
	{
		m_currentDirect = Knight::CURRENT_DIRECT_4 + 1;
	}
	else if (m_direct.x < 0 && m_direct.y < 0 && m_direct.y / m_direct.x > 0.5 &&
		m_direct.y / m_direct.x <= 2.5)
	{
		m_currentDirect = Knight::CURRENT_DIRECT_5 + 1;
	}
	else if (m_direct.x / m_direct.y < 0.5 && m_direct.x / m_direct.y > -0.5 && m_direct.y < 0)
	{
		m_currentDirect = Knight::CURRENT_DIRECT_6 + 1;
	}
	else if (m_direct.x > 0 && m_direct.y < 0 && m_direct.y / m_direct.x <= -0.5 &&
		m_direct.y / m_direct.x >= -2.5)
	{
		m_currentDirect = Knight::CURRENT_DIRECT_7 - 7;
	}
	else if (m_direct.x > 0 && m_direct.y / m_direct.x > -0.5 && m_direct.y / m_direct.x < 0.5)
	{
		m_currentDirect = Knight::CURRENT_DIRECT_0 + 1;
	}
}

void Dragon::AnimateStand()
{
	auto action = RepeatForever::create(ActionDragon("_dragon_00", 0, 120));
	action->setTag(TAG_ACTION_STAND);
	m_sprite->runAction(action);
}

Animate * Dragon::ActionDragon(std::string name, int begin, int end)
{
	Vector<SpriteFrame*> animFrames;
	for (int index = begin; index <= end; index++)
	{
		char buffer[20] = { 0 };
		sprintf(buffer, "%d.png", index);

		std::string str = name + buffer;

		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	auto animatonFunc = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animFrames.clear();

	auto aniamte = Animate::create(animatonFunc);
	aniamte->retain();

	return aniamte;
}

void Dragon::Move(Vec2 vec)
{
	if (m_sprite->getActionByTag(TAG_ACTION_STAND))
	{
		m_sprite->stopAllActionsByTag(TAG_ACTION_STAND);
	}
	if (!m_sprite->getActionByTag(TAG_ACTION_WALK))
	{
		SetDirect(vec);
		float _time = m_distance / 70.0;
		int count_repeat = _time + 1;
		switch (m_currentDirect)
		{
		case 0:
			//animate = Animate::create(createAnimation("_dragon_00", 160, 191));
			//moveTo = MoveTo::create(3, Vec2(m_sprite->getPositionX() + Distance, m_sprite->getPositionY() - Distance));
		{
			auto move = MoveTo::create(_time, vec);
			auto animate = Repeat::create(ActionDragon("_dragon_00", 160, 191), count_repeat);
			auto spawn = Spawn::create(move, animate, nullptr);
			spawn->setTag(TAG_ACTION_WALK);
			m_sprite->runAction(spawn);

			break;
		}

		case 1:
			/*animate = Animate::create(createAnimation("_dragon_00", 128, 159));
			moveTo = MoveTo::create(3, Vec2(m_sprite->getPositionX() + Distance, m_sprite->getPositionY()));*/
		{
			auto move = MoveTo::create(_time, vec);
			auto animate = Repeat::create(ActionDragon("_dragon_00", 128, 159), count_repeat);
			auto spawn = Spawn::create(move, animate, nullptr);
			spawn->setTag(TAG_ACTION_WALK);
			m_sprite->runAction(spawn);
			break;
		}

		case 2:
			/*animate = Animate::create(createAnimation("_dragon_00", 96, 123));
			moveTo = MoveTo::create(3, Vec2(m_sprite->getPositionX() + Distance, m_sprite->getPositionY() + Distance));
			*/
		{
			auto move = MoveTo::create(_time, vec);
			auto animate = Repeat::create(ActionDragon("_dragon_00", 96, 123), count_repeat);
			auto spawn = Spawn::create(move, animate, nullptr);
			spawn->setTag(TAG_ACTION_WALK);
			m_sprite->runAction(spawn);
			break;
		}

		case 3:
			/*animate = Animate::create(createAnimation("_dragon_00", 64, 95));
			moveTo = MoveTo::create(3, Vec2(m_sprite->getPositionX(), m_sprite->getPositionY() + Distance));*/
		{
			auto move = MoveTo::create(_time, vec);
			auto animate = Repeat::create(ActionDragon("_dragon_00", 64, 95), count_repeat);
			auto spawn = Spawn::create(move, animate, nullptr);
			spawn->setTag(TAG_ACTION_WALK);
			m_sprite->runAction(spawn);
			break;
		}

		case 4:
			/*animate = Animate::create(createAnimation("_dragon_00", 32, 63));
			moveTo = MoveTo::create(3, Vec2(m_sprite->getPositionX() - Distance, m_sprite->getPositionY() + Distance));*/
		{
			auto move = MoveTo::create(_time, vec);
			auto animate = Repeat::create(ActionDragon("_dragon_00", 32, 63), count_repeat);
			auto spawn = Spawn::create(move, animate, nullptr);
			spawn->setTag(TAG_ACTION_WALK);
			m_sprite->runAction(spawn);
			break;
		}

		case 5:
			//animate = Animate::create(createAnimation("_dragon_00", 0, 31));
			//moveTo = MoveTo::create(3, Vec2(m_sprite->getPositionX() - Distance, m_sprite->getPositionY()));
		{
			auto move = MoveTo::create(_time, vec);
			auto animate = Repeat::create(ActionDragon("_dragon_00", 0, 31), count_repeat);
			auto spawn = Spawn::create(move, animate, nullptr);
			spawn->setTag(TAG_ACTION_WALK);
			m_sprite->runAction(spawn);
			break;
		}

		case 6:
			//animate = Animate::create(createAnimation("_dragon_00", 224, 255));
			//moveTo = MoveTo::create(3, Vec2(m_sprite->getPositionX() - Distance, m_sprite->getPositionY() - Distance));
		{
			auto move = MoveTo::create(_time, vec);
			auto animate = Repeat::create(ActionDragon("_dragon_00", 224, 255), count_repeat);
			auto spawn = Spawn::create(move, animate, nullptr);
			spawn->setTag(TAG_ACTION_WALK);
			m_sprite->runAction(spawn);
			break;
		}

		case 7:
			//animate = Animate::create(createAnimation("_dragon_00", 192, 223));
			//moveTo = MoveTo::create(3, Vec2(m_sprite->getPositionX(), m_sprite->getPositionY() - Distance));
		{
			auto move = MoveTo::create(_time, vec);
			auto animate = Repeat::create(ActionDragon("_dragon_00", 192, 223), count_repeat);
			auto spawn = Spawn::create(move, animate, nullptr);
			spawn->setTag(TAG_ACTION_WALK);
			m_sprite->runAction(spawn);
			break;
		}

		default:
			break;
		}
	}
	//else 
	//{
	//	m_sprite->runAction(m_sprite->getActionByTag(TAG_ACTION_WALK));
	//}
	
}

void Dragon::Attack(Human *hm, float dt)
{
	if (m_sprite->getActionByTag(TAG_ACTION_WALK))
	{
		m_sprite->stopAllActionsByTag(TAG_ACTION_WALK);
	}
	//switch (m_currentDirect)
	//{
	//case 0:
	//	fire->setPosition(Vec2(m_sprite->getPositionX() + Fire, m_sprite->getPositionY() + Fire));
	//	break;
	//case 1:
	//	fire->setPosition(Vec2(m_sprite->getPositionX(), m_sprite->getPositionY() + Fire));
	//	break;
	//case 2:
	//	fire->setPosition(Vec2(m_sprite->getPositionX() - Fire, m_sprite->getPositionY() + Fire));
	//	break;
	//case 3:
	//	fire->setPosition(Vec2(m_sprite->getPositionX(), m_sprite->getPositionY() + Fire));
	//	break;
	//case 4:
	//	fire->setPosition(Vec2(m_sprite->getPositionX() - Fire, m_sprite->getPositionY() - Fire));
	//	break;
	//case 5:
	//	fire->setPosition(Vec2(m_sprite->getPositionX() - Fire, m_sprite->getPositionY()));
	//	break;
	//case 6:
	//	fire->setPosition(Vec2(m_sprite->getPositionX() + Fire, m_sprite->getPositionY() - Fire));
	//	break;
	//case 7:
	//	fire->setPosition(Vec2(m_sprite->getPositionX() + Fire, m_sprite->getPositionY()));
	//	break;

	//default:
	//	break;
	//}
	//static float count = 2.0;
	//if (count == 2)
	//{
		fire->setPosition(hm->GetPosition());
		auto animate = ActionDragon("red0", 0, 2);
		fire->runAction(animate);
		fire->setVisible(true);
		//count = 0;
	//}
	//count += dt;
}

Sprite * Dragon::GetSpriteFire()
{
	if (!fire)
		return fire;
	return nullptr;
}


