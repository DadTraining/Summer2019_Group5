#include "Dragon.h"



Dragon::Dragon(Layer * _layer2D)
{
	screenSize = Director::getInstance()->getVisibleSize();
	// test sprite
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("dragon.plist", "dragon.png");
	
	// Định nghĩa hằng. 
	const int numberSprite = 4;
	const int maxWord = 50;

	// Tạo Sprite sử dụng hình ảnh đầu tiên là mysprite0.png. Ở đây Animation của mình sẽ dùng Sprite này làm Sprite đầu tiên.
	m_sprite = Sprite::createWithSpriteFrameName("wyvern_composite_09.png");
	// Thiết lập vị trí của gameSprite tại vị trí (300, 300). Đây cũng chính là vị trí của Animation trên Screen.
	m_sprite->setScale(2);
	m_sprite->setPosition(screenSize.width / 2, screenSize.height / 2);
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
	_layer2D->addChild(m_sprite,10);


	Vector<SpriteFrame*> animFrames;
	//init attack
	for (int i = 10; i <= 40; i++) {
		//	if (i==1||i==3||i==5||i==7) continue;
		char buffer[200] = { 0 };
		sprintf(buffer, "wyvern_composite_%d.png", i);
		std::string str = buffer;
		//animaton = Hero::createAnimation(str, 9, 0.1f);

		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);

		animFrames.pushBack(frame);

	}


	Animate* animate = Animate::create(Animation::createWithSpriteFrames(animFrames, 0.5f));
	animate->retain();

	m_sprite->runAction(RepeatForever::create(animate));
}

Dragon::~Dragon()
{
}

void Dragon::Init(int d)
{

		

}

void Dragon::Attack()
{
}

void Dragon::Update(float)
{
}

void Dragon::Move(Vec2 vec)
{
}

void Dragon::Died()
{
}
