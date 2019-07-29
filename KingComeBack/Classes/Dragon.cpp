#include "Dragon.h"



Dragon::Dragon(Layer * _layer2D)
{
	screenSize = Director::getInstance()->getVisibleSize();
	// test sprite
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("dragon.plist", "dragon.png");

	spriteBlood = Sprite::create("loadingBarHouse.png");

	m_sprite = Sprite::createWithSpriteFrameName("_dragon_000.png");

	m_sprite->setScale(1.5);
	m_sprite->setPosition(screenSize.width / 2, screenSize.height / 2);

	spriteBlood->setAnchorPoint(Vec2(0,0));
	spriteBlood->setPosition(Vec2(m_sprite ->getPositionX(), m_sprite ->getPositionY()+100));
	blood = new Blood(1000);

	bodyA = PhysicsBody::createBox(m_sprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	
	bodyA->setGravityEnable(false);

	bodyA->setCategoryBitmask(16);
	bodyA->setCollisionBitmask(5);

	bodyA->setDynamic(true);
	m_sprite->setPhysicsBody(bodyA);

	//m_sprite->setCameraMask(2);

	_layer2D->addChild(spriteBlood, 10);
	_layer2D->addChild(m_sprite,10);


	Animate* animate = Animate::create(createAnimation("_dragon_00", 0,120));

	animate->retain();

	m_sprite->runAction(Repeat::create(animate,1));
}

Dragon::~Dragon()
{
}


void Dragon::Init(int)
{
}

void Dragon::Died()
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

Blood* Dragon::getBlood()
{
	return blood;
}

void Dragon::handleBloodBar()
{
	spriteBlood->setScaleX(blood->getBlood()/1000);
}

void Dragon::createFire(Layer * _layer2D)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fire.plist", "fire.png");
	fire = Sprite::createWithSpriteFrameName("red00.png");
	fire->setPosition(m_sprite->getPosition());
	fire->setVisible(false);
	_layer2D->addChild(fire);
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

void Dragon::updatePositionloodBar()
{
	spriteBlood->setPosition(m_sprite->getPositionX(), m_sprite->getPositionY() + 100);
}


