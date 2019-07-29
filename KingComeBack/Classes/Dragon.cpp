#include "Dragon.h"



Dragon::Dragon(Layer * _layer2D)
{
	screenSize = Director::getInstance()->getVisibleSize();
	// test sprite
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("dragon.plist", "dragon.png");
	spriteBlood = Sprite::create("loadingBarHouse.png");
	
	// Định nghĩa hằng. 
	const int numberSprite = 4;
	const int maxWord = 50;

	// Tạo Sprite sử dụng hình ảnh đầu tiên là mysprite0.png. Ở đây Animation của mình sẽ dùng Sprite này làm Sprite đầu tiên.
	m_sprite = Sprite::createWithSpriteFrameName("_dragon_000.png");
	// Thiết lập vị trí của gameSprite tại vị trí (300, 300). Đây cũng chính là vị trí của Animation trên Screen.
	m_sprite->setScale(1.5);
	m_sprite->setPosition(screenSize.width / 2, screenSize.height / 2);

	spriteBlood->setAnchorPoint(Vec2(0,0));
	spriteBlood->setPosition(Vec2(m_sprite ->getPositionX(), m_sprite ->getPositionY()+100));
	blood = new Blood(1000);
	//Thêm gameSprite vào Scene.
	bodyA = PhysicsBody::createBox(m_sprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	//bodyA->setContactTestBitmask(true);
	bodyA->setGravityEnable(false);
	//bodyA->setContactTestBitmask(BITMASK_LAYER_UI);
	bodyA->setCategoryBitmask(16);
	bodyA->setCollisionBitmask(5);

	bodyA->setDynamic(true);
	m_sprite->setPhysicsBody(bodyA);

	//m_sprite->setCameraMask(2);
	_layer2D->addChild(spriteBlood, 10);
	_layer2D->addChild(m_sprite,10);





	Animate* animate = Animate::create(createAnimation("_dragon_00", 0,120));
	animate->retain();

	m_sprite->runAction(RepeatForever::create(animate));
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



