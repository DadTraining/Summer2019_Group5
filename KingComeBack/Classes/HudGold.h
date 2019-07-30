#pragma once
#ifndef  __HUD_h__
#define  __HUD_h__

#include "cocos2d.h"

USING_NS_CC;

class HudGold : public cocos2d::LayerColor
{
public:
	HudGold();
	virtual ~HudGold();

	static HudGold* createLayer(const std::string& msg, cocos2d::Vec2 msgPos, cocos2d::Color3B color, cocos2d::Size size, cocos2d::Vec2 anchorPoint);
	virtual bool initWithMessage(const std::string& msg, Vec2 msgPos, Color3B color, Size size, Vec2 anchorPoint);
	//void initOptions(const std::string& _message);
	virtual void draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform,
		bool transformUpdated);
	inline virtual cocos2d::Label* getMessageLabel() { return _messageLabel; };

	CREATE_FUNC(HudGold);
protected:
private:
	cocos2d::Label* _messageLabel;
};

#endif // __HUD_h__