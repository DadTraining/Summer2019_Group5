#include "HudGold.h"

HudGold::HudGold()
{
}


HudGold::~HudGold()
{
}

HudGold * HudGold::createLayer(const std::string& msg, cocos2d::Vec2 msgPos, cocos2d::Color3B color, cocos2d::Size size, cocos2d::Vec2 anchorPoint)
{
	HudGold* hudMessage = new HudGold();
	if (hudMessage && hudMessage->initWithMessage(msg, msgPos, color, size, anchorPoint))
	{
		hudMessage->autorelease();
		return hudMessage;
	}

	CC_SAFE_DELETE(hudMessage);
	return NULL;

}

bool HudGold::initWithMessage(const std::string & msg, Vec2 msgPos, Color3B color, Size size, Vec2 anchorPoint)
{
	_messageLabel = cocos2d::Label::createWithTTF(msg.c_str(), "fonts/arial.ttf", 1);
	_messageLabel->setColor(cocos2d::Color3B(255, 215, 0));
	_messageLabel->setPosition(msgPos);
	this->addChild(_messageLabel, 1);

	//set properties for LayerColor
	this->setColor(color);
	this->setContentSize(size);
	this->setAnchorPoint(anchorPoint);

	return true;
}

//void HudGold::initOptions(const std::string & _message)
//{
//	_messageLabel = cocos2d::Label::createWithTTF(_message, "fonts/arial.ttf", 10);
//	_messageLabel->setColor(cocos2d::Color3B::BLACK);
//
//	addChild(_messageLabel, 1);
//
//	_messageLabel->setPosition(cocos2d::Vec2(Director::getInstance()->getVisibleSize().width,
//		Director::getInstance()->getVisibleSize().height));
//}

void HudGold::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, bool transformUpdated)
{
}
