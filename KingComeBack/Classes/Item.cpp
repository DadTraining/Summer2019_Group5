#include "Item.h"

Item::Item()
{
}

Item::Item(int ID)
{
	this->Init(ID); 
	
	//layer->addChild(m_button,5);
	//m_button->setCameraMask(4);
}

Item::~Item()
{

}

void Item::Init(int ID)
{

	screenSize = Director::getInstance()->getVisibleSize();

	if (ID == ID_HP)
	{
		m_button = ui::Button::create("item/potionRed.png", "");
	}
	else if (ID == ID_MP)
	{
		m_button = ui::Button::create("item/potionBlue.png", "");
	}
	else if (ID == ID_WEAPON)
	{
		m_button = ui::Button::create("item/sword.png", "");
		m_dame = 100;
	}
	else if (ID == ID_HELMET)
	{
		m_button = ui::Button::create("item/helmet.png", "");
		m_hp = 200;
		m_mp = 100;
	}
	else if (ID == ID_ARMOR)
	{
		m_button = ui::Button::create("item/armor.png", "");
		m_armor = 10;
	}
	else if (ID == ID_SHIELD)
	{
		m_button = ui::Button::create("item/armor.png");
	}
	if (ID == ID_ARMOR || ID == ID_WEAPON || ID == ID_HELMET)
	{
		m_itemAttribute = rand() % 3 + 1;
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
}

void Item::Died()
{

}
int Item::GetState()
{
	return m_state;
}
void Item::SetState(int state)
{
	m_state = state;
}

Vec2 Item::getPrePosition()
{
	return prePosition;
}

void Item::setPrePosition(Vec2 _pos)
{
	prePosition = _pos;
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
	if (id_equip == ID_WEAPON)
	{
		if (m_state == ID_STATE_HOME)
		{
			m_button->setPosition(Vec2(screenSize.width / 1.785, screenSize.height / 1.735));
			m_state = ID_STATE_EQUIPMENT;
		}
		else if (m_state == ID_STATE_EQUIPMENT)
		{
			m_button->setPosition(prePosition);
			m_state = ID_STATE_HOME;
		}
	}
	if (id_equip == ID_HELMET)
	{

		if (m_state == ID_STATE_HOME)
		{
			m_button->setPosition(Vec2(screenSize.width / 1.642, screenSize.height / 1.39));
			m_state = ID_STATE_EQUIPMENT;
		}
		else if (m_state == ID_STATE_EQUIPMENT)
		{
			m_button->setPosition(prePosition);
			m_state = ID_STATE_HOME;
		}
	}
	if (id_equip == ID_ARMOR)
	{
		if (m_state == ID_STATE_HOME)
		{
			m_button->setPosition(Vec2(screenSize.width / 1.63, screenSize.height / 1.6));
			m_state = ID_STATE_EQUIPMENT;
		}
		else if (m_state == ID_STATE_EQUIPMENT)
		{
			m_button->setPosition(prePosition);
			m_state = ID_STATE_HOME;
		}
	}
}
