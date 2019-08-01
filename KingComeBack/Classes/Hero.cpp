#include "Hero.h"

Hero::Hero(Layer * _layer2D)
{
	screenSize = Director::getInstance()->getVisibleSize();
	// test sprite
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hero.plist", "hero.png");

	const int numberSprite = 4;
	const int maxWord = 50;

	
	m_sprite = Sprite::createWithSpriteFrameName("walk_00000.png");

	// Thiết lập vị trí của gameSprite tại vị trí (300, 300). Đây cũng chính là vị trí của Animation trên Screen.
	m_sprite->setScale(0.7);
	m_sprite->setPosition(screenSize.width / 2, screenSize.height / 2);
	
	//bodyA = PhysicsBody::createBox(m_sprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	
	MyBodyParser::getInstance()->parseJsonFile("hero_body.json");
	auto bodyA = MyBodyParser::getInstance()->bodyFormJson(m_sprite, "HeroPhysicBody", PhysicsMaterial(0, 0, 0));
	bodyA->setGravityEnable(false);

	bodyA->setCategoryBitmask(8);
	bodyA->setCollisionBitmask(21);
	bodyA->setRotationEnable(false);
	bodyA->setDynamic(true);
	m_sprite->setPhysicsBody(bodyA);


	Init(1);
	//m_sprite->setCameraMask(2);
	_layer2D->addChild(m_sprite,10);

	state = true;
}

Hero::~Hero()
{
}

void Hero::Init(int d)
{
	blood = new Blood(500.0,1000.0);
	damage = new Damage(100, 150, 200);	

	SetBlood(500.0f);
	SetAmor(50.0f);
	SetDame(60.0f);
	setStrength(30.0f);
}

void Hero::Attack(Human*, float)
{
	
}

void Hero::Update(float dt) {

}



void Hero::Move(Vec2 vec)
{
}

void Hero::Died()
{
}

Animation * Hero::createAnimation(std::string frefixName, int pFrame, float delay)
{
	Vector<SpriteFrame*> animFrames;


	for (int index = 0; index <= pFrame; index++)
	{
		
	
		char buffer[20] = { 0 };
	

		sprintf(buffer, "%d.png", index);

		std::string str = frefixName + buffer;


		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		

		animFrames.pushBack(frame);
		
	}
	auto animatonFunc = Animation::createWithSpriteFrames(animFrames, delay);
	
	animFrames.clear();
	return animatonFunc;
}




void Hero::moveR(int directMove, int x , int y)
{
	
	tempPositinSprite.x = m_sprite->getPosition().x + x;
	tempPositinSprite.y = m_sprite->getPosition().y + y;
	
	char buffer[20] = { 0 };
	sprintf(buffer, "walk_%d000", directMove);
	std::string str = buffer;
	//m_sprite->runAction( mListAction[2] );
	animaton = Hero::createAnimation(str, 7, 0.1f);
	Animate* animate = Animate::create(animaton);
	animate->retain();
	m_sprite->stopAllActions();
	auto moveto = MoveTo::create(1.5,Vec2( tempPositinSprite.x, tempPositinSprite.y));

	moveto->setTag(0);
	m_sprite->runAction(moveto);
	
	m_sprite->runAction(Repeat::create(animate, 1));



//	m_sprite->setPosition(tempPositinSprite.x, tempPositinSprite.y);
}



int Hero::getDirect()
{
	return direct;
}

void Hero::setDirect(int i)
{
	direct = i;
}

void  Hero::getAttack(int directAttack)
{
	char buffer[20] = { 0 };
	sprintf(buffer, "attack_%d000", directAttack);
	std::string str = buffer;
		
	//m_sprite->runAction( mListAction[2] );
	animaton = Hero::createAnimation(str, 9, 0.1f);
	Animate* animate = Animate::create(animaton);
	animate->retain();
	m_sprite->runAction(Repeat::create(animate, 1));
		
}

Vec2  Hero::getPositionHero()
{
	return  m_sprite->getPosition();
}


void Hero::skillAnimation( Layer* l, int type)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skill.plist", "Skill.png");
	switch (type)
	{
	case 1:
	{
		getAttack(direct);
		skill_1 = Sprite::createWithSpriteFrameName("skill1_064.png");
		skill_1->setScale(1);
		skill_1->setPosition(m_sprite->getPosition());
		skill_1->setCameraMask(2);
		l->addChild(skill_1);
		auto animationSkill_1 = createSkillAnimation(64, 81);
		Animate* animate_1 = Animate::create(animationSkill_1);
		animate_1->retain();
		m_sprite->stopAllActions();
		skill_1->runAction(Repeat::create(animate_1, 1));
		break;
	}
	case 2:
	{
		getAttack(direct);
		skill_2 = Sprite::createWithSpriteFrameName("skill1_093.png");
		skill_2->setScale(1);
		skill_2->setCameraMask(2);
		l->addChild(skill_2);

		switch (direct)
		{
		case 0:
			//skill_2->setPosition(m_sprite->getPositionX() + DISTANCE_SKILL_1, m_sprite->getPositionY() - DISTANCE_SKILL_1);
			skill_2->setPosition(m_sprite->getPositionX() + 50, m_sprite->getPositionY() - 50);
			moveto = MoveTo::create(1.5, Vec2(m_sprite->getPositionX() + DISTANCE_SKILL_2, m_sprite->getPositionY() - DISTANCE_SKILL_2));
			break;
		case 1:
			//	skill_2->setPosition(m_sprite->getPositionX() + DISTANCE_SKILL_1, m_sprite->getPositionY() );
			skill_2->setPosition(m_sprite->getPositionX() + 50, m_sprite->getPositionY());
			moveto = MoveTo::create(1.5, Vec2(m_sprite->getPositionX() + DISTANCE_SKILL_2, m_sprite->getPositionY()));
			break;
		case 2:
			skill_2->setPosition(m_sprite->getPositionX() + 50, m_sprite->getPositionY()+ 50);
			//	skill_2->setPosition(m_sprite->getPositionX() + DISTANCE_SKILL_2, m_sprite->getPositionY() + DISTANCE_SKILL_2);
			moveto = MoveTo::create(1.5, Vec2(m_sprite->getPositionX() + DISTANCE_SKILL_2, m_sprite->getPositionY()+ DISTANCE_SKILL_2));
			break;
		case 3:
			skill_2->setPosition(m_sprite->getPositionX(), m_sprite->getPositionY() + 50);
			//	skill_2->setPosition(m_sprite->getPositionX() , m_sprite->getPositionY() + DISTANCE_SKILL_1);
			moveto = MoveTo::create(1.5, Vec2(m_sprite->getPositionX(), m_sprite->getPositionY() + DISTANCE_SKILL_2));
			break;
		case 4:
			skill_2->setPosition(m_sprite->getPositionX() - 50, m_sprite->getPositionY() + 50);
			//	skill_2->setPosition(m_sprite->getPositionX() - DISTANCE_SKILL_1, m_sprite->getPositionY() + DISTANCE_SKILL_1);
			moveto = MoveTo::create(1.5, Vec2(m_sprite->getPositionX() - DISTANCE_SKILL_2, m_sprite->getPositionY() + DISTANCE_SKILL_2));
			break;
		case 5:
			skill_2->setPosition(m_sprite->getPositionX() - 50, m_sprite->getPositionY());
			//	skill_2->setPosition(m_sprite->getPositionX() - DISTANCE_SKILL_1, m_sprite->getPositionY());
			moveto = MoveTo::create(1.5, Vec2(m_sprite->getPositionX() - DISTANCE_SKILL_2, m_sprite->getPositionY()));
			break;
		case 6:
			skill_2->setPosition(m_sprite->getPositionX() - 50, m_sprite->getPositionY() - 50);
			//	skill_2->setPosition(m_sprite->getPositionX() - DISTANCE_SKILL_1 , m_sprite->getPositionY() - DISTANCE_SKILL_1);
			moveto = MoveTo::create(1.5, Vec2(m_sprite->getPositionX() - DISTANCE_SKILL_2, m_sprite->getPositionY() - DISTANCE_SKILL_2));
			break;
		case 7:
			skill_2->setPosition(m_sprite->getPositionX(), m_sprite->getPositionY() - 50);
			//	skill_2->setPosition(m_sprite->getPositionX() , m_sprite->getPositionY() - DISTANCE_SKILL_1);
			moveto = MoveTo::create(1.5, Vec2(m_sprite->getPositionX(), m_sprite->getPositionY() - DISTANCE_SKILL_2));
			break;

		default:
			break;
		}

		auto animationSkill_2 = createSkillAnimation(93, 108);

		Animate* animate_2 = Animate::create(animationSkill_2);

		animate_2->retain();
		//	m_sprite->stopAllActions();

		skill_2->runAction(moveto);

		skill_2->runAction(Repeat::create(animate_2, 1));

		break;
		
	}
	default:
		break;
	}
	
}

Animation * Hero::createSkillAnimation(int begin, int end)
{

	Vector<SpriteFrame*> animFrames;


	for (int index = begin; index <= end; index++)
	{

		char buffer[20] = { 0 };

		sprintf(buffer, "%d.png", index);

		std::string str = "skill1_0";
		str = str + buffer;

		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);

		animFrames.pushBack(frame);
		//	str = "skill_0";

	}
	auto animaton = Animation::createWithSpriteFrames(animFrames, 0.1f);

	return animaton;
}

void Hero::diedHero(int directDied)
{
	char buffer[20] = { 0 };
	sprintf(buffer, "death_%d000", directDied);
	std::string str = buffer;

	//m_sprite->runAction( mListAction[2] );
	auto animaton = Hero::createAnimation(str, 7, 0.1f);
	Animate* animate = Animate::create(animaton);
	animate->retain();
	m_sprite->stopAllActions();
	m_sprite->runAction(Repeat::create(animate, 1));
}

Blood * Hero::getBlood()
{
	return blood;
}

void Hero::createBloodSprite(Layer * l)
{
	spriteBlood = Sprite::create("bloodBar.png");
	spriteBlood->setAnchorPoint(Vec2(0,0));
	spriteBlood->setPosition(322,98);
	l->addChild(spriteBlood,1);

	spriteMana = Sprite::create("bloodBar.png");
	

	spriteMana->setAnchorPoint(Vec2(0, 0));
	spriteMana->setPosition(322, 70);
	l->addChild(spriteMana, 1);

	spriteGreen = Sprite::create("bloodBar.png");

	spriteGreen->setAnchorPoint(Vec2(0, 0));
	spriteGreen->setPosition(322, 40);
	l->addChild(spriteGreen, 1);
}

void Hero::handleBloodBar()
{
	float per = blood->getBlood()/1000;
	spriteBlood->setScaleX(per);
	if (blood->getBlood()<=0) {
		spriteBlood->setVisible(false);
	}
	else {
		spriteBlood->setVisible(true);
	}
}

float Hero::getStrength()
{
	return m_strength;
}

void Hero::setStrength(float _strength)
{
	m_strength = _strength;
}

bool Hero::getState()
{
	return state;
}

void Hero::setState(bool state)
{
	this->state = state;
}

Damage * Hero::getDamage()
{
	return damage;
}




