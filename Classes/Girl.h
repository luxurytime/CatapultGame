#ifndef __GIRL_H__
#define __GIRL_H__

#include "Character.h"
#include "cocos2d.h"

USING_NS_CC;

class Girl : public Character {
public:
	Girl()
	{
		auto texture = Director::getInstance()->getTextureCache()->addImage("davis_1.png");
		auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 79.25, 81.25)));
		auto player = Sprite::createWithSpriteFrame(frame0);
		player->setScale(0.8);
		setCharaSpr(player);

		auto playerBody = PhysicsBody::createBox(player->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 0.0f));
		playerBody->setRotationEnable(false);
		player->setPhysicsBody(playerBody);

		Vector<SpriteFrame*> walk;
		walk.reserve(5);
		for (int i = 0; i < 4; i++) {
			walk.pushBack(SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(79.25 * i, 0, 79.25, 81.25))));
		}
		walk.pushBack(frame0);
		setWalkFrame(walk);

		Vector<SpriteFrame*> dead;
		auto texture2 = Director::getInstance()->getTextureCache()->addImage("$lucia_dead.png");
		dead.reserve(23);
		for (int i = 0; i < 7; i++) {
			//auto frame = SpriteFrame::createWithTexture(texture2, CC_RECT_PIXELS_TO_POINTS(Rect(79 * i, 0, 79, 90)));
			auto frame = SpriteFrame::createWithTexture(texture2, CC_RECT_PIXELS_TO_POINTS(Rect(79 * i, 0, 79, 81)));
			dead.pushBack(frame);
		}
		dead.pushBack(frame0);
		setDeadFrame(dead);


		setIsRight(true);
		setSpeed(200);
		setJumpNum(0);
		setMoveDis(0);

	}

};

#endif