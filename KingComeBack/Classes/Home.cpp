#include "Home.h"

Home::Home()
{

}

Home::~Home()
{

}

void Home::SetButton(ui::Button * _button)
{
	m_button = _button;
}

ui::Button * Home::GetButton()
{
	return m_button;
}
