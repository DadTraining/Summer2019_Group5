#include "Item.h"

Item::Item()
{
}

Item::Item(Layer * layer, int ID)
{
	this->Init(ID); 
	if (ID == HP)
	{
		m_button = ui::Button::create("potionRed.png", "");
	}
	else if (ID == MP)
	{
		m_button = ui::Button::create("potionBlue.png", "");
	}
	else if (ID == WEAPON)
	{
		m_button = ui::Button::create("sword.png", "sword_press");
	}
	m_state = ID_STATE_HOME;
	m_button->addTouchEventListener([=](Ref *sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			this->ItemIsClick(ID);
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	layer->addChild(m_button,5);
	//m_button->setCameraMask(4);
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

ui::Button * Item::getButton()
{
	return m_button;
}

void Item::retain()
{
	delete this;
}

void Item::ItemIsClick(int id_equip)
{
	auto prePosition = m_button->getPosition();
	if (id_equip == WEAPON)
	{
		if (m_state == ID_STATE_HOME)
		{
			m_button->setPosition(Vec2(screenSize.width / 1.85, screenSize.height / 1.81));
			m_state = ID_STATE_EQUIPMENT;
		}
		else if (m_state == ID_STATE_EQUIPMENT)
		{

		}
	}
}
