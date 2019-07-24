#include "Item.h"

Item::Item(Layer * layer, int ID)
{
	this->Init(ID); 

	//layer->addChild(menuItemImage);
	//auto listenerItem = EventListenerTouchOneByOne::create();
	//listenerItem->onTouchBegan = [=](Touch *_touch, Event *_event) {
	//	if (this->getSprite()->getBoundingBox().containsPoint(_touch->getLocation()))
	//	{
	//		this->SetPosition();
	//		return true;
	//	}
	//	return false;
	//};
	//scene->getEventDispatcher.
}

Item::~Item()
{
}

void Item::Init(int ID)
{
	screenSize = Director::getInstance()->getVisibleSize();

	switch (ID)
	{
	case 0:
		m_itemAttribute = ID_ITEM_STRENGTH;
		m_dame = 100;
		break;
	case 1:
		m_itemAttribute = ID_ITEM_AGILITY;
		m_dame = 98;
		break;
	case 2:
		m_itemAttribute = ID_ITEM_INTELIGENT;
		m_dame = 120;
		break;
	default:
		break;
	}
	menuItemImage = MenuItemImage::create("axe.png", "axe.png", [&](Ref *ref) {
		menuItemImage->setPosition(screenSize.width / 2, screenSize.height / 2);
	});
	m_state = ID_STATE_WAREHOUSE;
}

void Item::Died()
{
}

int Item::SetState(int state)
{
	m_state = state;
	return m_state;
}

void Item::SetPosition(Ref *ref)
{
	if (m_state == ID_STATE_EQUIPMENT)
	{
		this->m_sprite->setPosition(screenSize.width / 1.8, screenSize.height / 2);
	}
}

MenuItemImage * Item::getMenuItemImage()
{
	return menuItemImage;
}
