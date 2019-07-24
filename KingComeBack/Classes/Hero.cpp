#include "Hero.h"



Hero::Hero(Layer * _layer2D)
{
	screenSize = Director::getInstance()->getVisibleSize();
	// test sprite
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hero.plist", "hero.png");
	
	// Định nghĩa hằng. 
	const int numberSprite = 4;
	const int maxWord = 50;

	// Tạo Sprite sử dụng hình ảnh đầu tiên là mysprite0.png. Ở đây Animation của mình sẽ dùng Sprite này làm Sprite đầu tiên.
	m_sprite = Sprite::createWithSpriteFrameName("walk_00000.png");
	// Thiết lập vị trí của gameSprite tại vị trí (300, 300). Đây cũng chính là vị trí của Animation trên Screen.
	m_sprite->setScale(0.5);
	m_sprite->setPosition(screenSize.width / 2, screenSize.height / 2);
	//Thêm gameSprite vào Scene.
	bodyA = PhysicsBody::createBox(m_sprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	//bodyA->setContactTestBitmask(true);
	bodyA->setGravityEnable(false);
	//bodyA->setContactTestBitmask(BITMASK_LAYER_UI);
	bodyA->setCategoryBitmask(8);
	bodyA->setCollisionBitmask(5);

	bodyA->setDynamic(true);
	m_sprite->setPhysicsBody(bodyA);

	//m_sprite->setCameraMask(2);
	_layer2D->addChild(m_sprite,10);

//	Init(1);
}

Hero::~Hero()
{
}

void Hero::Init(int d)
{

	//init attack
	for (int i = 0; i <= 7; i++) {
	//	if (i==1||i==3||i==5||i==7) continue;
		char buffer[20] = { 0 };
		sprintf(buffer, "walk_%d000", i);
		std::string str = buffer;
		animaton = Hero::createAnimation(str, 9, 0.1f);
		Animate* animate = Animate::create(animaton);
		animate->retain();
		
		mListAction[i] = Repeat::create(animate, 1);
		
	}

}

void Hero::Attack()
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

	// Lặp để đọc numberSprite ảnh trong file format
	for (int index = 0; index <= pFrame; index++)
	{
		

		char buffer[20] = { 0 };
		// Lấy sprite frame name
		sprintf(buffer, "%d.png", index);

		std::string str = frefixName + buffer;

		// Tạo 1 khung, lấy ra từ bộ đệm SpriteFrameCache có tên là spriteFrameByName;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		// Push frame.
		animFrames.pushBack(frame);
	}
	auto animatonFunc = Animation::createWithSpriteFrames(animFrames, delay);
	animFrames.clear();
	return animatonFunc;
}




void Hero::moveRight_1()
{
	tempPositinSprite.x = m_sprite->getPosition().x;
	tempPositinSprite.y = m_sprite->getPosition().y;
	m_sprite->setPosition(tempPositinSprite.x + 2, tempPositinSprite.y - 2);

	animaton = Hero::createAnimation("walk_0000", 7, 0.1f);
	Animate* animate = Animate::create(animaton);
	animate->retain();
	// Chạy Acction animation với số lần lặp vô hạn.
	m_sprite->runAction(Repeat::create(animate, 2));
}

void Hero::moveRight0()
{
	//gameSprite->setFlippedX(false);
	tempPositinSprite.x = m_sprite->getPosition().x;
	tempPositinSprite.y = m_sprite->getPosition().y;
	m_sprite->setPosition(tempPositinSprite.x + 2, tempPositinSprite.y);
	
	animaton = Hero::createAnimation("walk_1000", 7, 0.1f);
	Animate* animate = Animate::create(animaton);
	animate->retain();
	// Chạy Acction animation với số lần lặp vô hạn.
	m_sprite->runAction(Repeat::create(animate, 2));
}

void Hero::moveRight1()
{
	tempPositinSprite.x = m_sprite->getPosition().x;
	tempPositinSprite.y = m_sprite->getPosition().y;
	m_sprite->setPosition(tempPositinSprite.x + 2, tempPositinSprite.y + 2);
	
	animaton = Hero::createAnimation("walk_2000", 7, 0.1f);
	Animate* animate = Animate::create(animaton);
	animate->retain();
	// Chạy Acction animation với số lần lặp vô hạn.
	m_sprite->runAction(Repeat::create(animate, 2));
}

void Hero::moveLeft_1()
{
	tempPositinSprite.x = m_sprite->getPosition().x;
	tempPositinSprite.y = m_sprite->getPosition().y;
	m_sprite->setPosition(tempPositinSprite.x - 2, tempPositinSprite.y - 2);

	animaton = Hero::createAnimation("walk_6000", 7, 0.1f);
	Animate* animate = Animate::create(animaton);
	animate->retain();
	// Chạy Acction animation với số lần lặp vô hạn.
	m_sprite->runAction(Repeat::create(animate, 2));
}

void Hero::moveLeft0()
{
	tempPositinSprite.x = m_sprite->getPosition().x;
	tempPositinSprite.y = m_sprite->getPosition().y;
	m_sprite->setPosition(tempPositinSprite.x - 2, tempPositinSprite.y );

	animaton = Hero::createAnimation("walk_5000", 7, 0.1f);
	Animate* animate = Animate::create(animaton);
	animate->retain();
	// Chạy Acction animation với số lần lặp vô hạn.
	m_sprite->runAction(Repeat::create(animate, 2));
}

void Hero::moveLeft1()
{
	tempPositinSprite.x = m_sprite->getPosition().x;
	tempPositinSprite.y = m_sprite->getPosition().y;
	m_sprite->setPosition(tempPositinSprite.x - 2, tempPositinSprite.y + 2);

	animaton = Hero::createAnimation("walk_4000", 7, 0.1f);
	Animate* animate = Animate::create(animaton);
	animate->retain();
	// Chạy Acction animation với số lần lặp vô hạn.
	m_sprite->runAction(Repeat::create(animate, 2));
}

void Hero::upTo()
{
	tempPositinSprite.x = m_sprite->getPosition().x;
	tempPositinSprite.y = m_sprite->getPosition().y;
	m_sprite->setPosition(tempPositinSprite.x , tempPositinSprite.y + 2);

	animaton = Hero::createAnimation("walk_3000", 7, 0.1f);
	Animate* animate = Animate::create(animaton);
	animate->retain();
	// Chạy Acction animation với số lần lặp vô hạn.
	m_sprite->runAction(Repeat::create(animate, 2));
}

void Hero::downTo()
{
	tempPositinSprite.x = m_sprite->getPosition().x;
	tempPositinSprite.y = m_sprite->getPosition().y;
	m_sprite->setPosition(tempPositinSprite.x, tempPositinSprite.y - 2);

	animaton = Hero::createAnimation("walk_7000", 7, 0.1f);
	Animate* animate = Animate::create(animaton);
	animate->retain();
	// Chạy Acction animation với số lần lặp vô hạn.
	m_sprite->runAction(Repeat::create(animate, 2));
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
	animaton = Hero::createAnimation(str, 7, 0.01f);
	Animate* animate = Animate::create(animaton);
	animate->retain();
	//Chạy Acction animation với số lần lặp vô hạn.
	m_sprite->runAction(Repeat::create(animate, 1));
		
}
