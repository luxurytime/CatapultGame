#ifndef __BOY_H__
#define __BOY_H__

#include "Character.h"
#include "cocos2d.h"

USING_NS_CC;

class Boy : public Character {
public:
	Boy()
	{
		auto texture = Director::getInstance()->getTextureCache()->addImage("$lucia_forward.png");
		auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(10, 10, 48, 81)));
		auto player = Sprite::createWithSpriteFrame(frame0);
		setCharaSpr(player);

		Vector<SpriteFrame*> walk;
		walk.reserve(9);
		for (int i = 0; i < 8; i++) {
			walk.pushBack(SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(68 * i + 10, 10, 48, 81))));
		}
		walk.pushBack(frame0);
		setWalkFrame(walk);

		Vector<SpriteFrame*> dead;
		auto texture2 = Director::getInstance()->getTextureCache()->addImage("$lucia_dead.png");
		dead.reserve(23);
		for (int i = 0; i < 22; i++) {
			auto frame = SpriteFrame::createWithTexture(texture2, CC_RECT_PIXELS_TO_POINTS(Rect(79 * i, 0, 79, 90)));
			dead.pushBack(frame);
		}
		dead.pushBack(frame0);
		setDeadFrame(dead);
	}

};

#endif