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
	bodyA->setCollisionBitmask(21);
	bodyA->setRotationEnable(false);
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
	float x = m_sprite -> getPosition().x;
	
	float y = m_sprite->getPosition().y;

	// Lặp để đọc numberSprite ảnh trong file format
	for (int index = 0; index <= pFrame; index++)
	{
		
		x += index;
		y ;
		char buffer[20] = { 0 };
		// Lấy sprite frame name
		sprintf(buffer, "%d.png", index);

		std::string str = frefixName + buffer;

		// Tạo 1 khung, lấy ra từ bộ đệm SpriteFrameCache có tên là spriteFrameByName;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		
		//	auto frame = SpriteFrame::create(str, Rect(x, y, m_sprite->getContentSize().width, m_sprite->getContentSize().height));
			// Push frame.
		//	log("frame %s", frame->getRect().size);
		//frame->setRect(Rect(x,y, m_sprite->getContentSize().width, m_sprite->getContentSize().height));
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
	animaton = Hero::createAnimation(str, 7, 0.09f);
	Animate* animate = Animate::create(animaton);
	animate->retain();
	m_sprite->stopAllActions();
	auto moveto = MoveTo::create(1.5,Vec2( tempPositinSprite.x, tempPositinSprite.y));
	m_sprite->runAction(moveto);
	
	m_sprite->runAction(Repeat::create(animate, 2));

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
	animaton = Hero::createAnimation(str, 9, 0.01f);
	Animate* animate = Animate::create(animaton);
	animate->retain();

	m_sprite->runAction(Repeat::create(animate, 1));
		
}

Vec2  Hero::getPositionHero()
{
	return  m_sprite->getPosition();
}
