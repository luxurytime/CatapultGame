#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	virtual void onStart(Ref* ref);

	virtual void onVS(Ref* ref);
	virtual void onStage(Ref* ref);
	virtual void onUp(Ref* ref);

	bool onTouchBegan(Touch *touch, cocos2d::Event *event);

	void onTouchEnded(Touch *touch, cocos2d::Event *event);

	void onMouseMove(Event* event);

	void largerItem(int i);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	MenuItemImage* startMenuItem;

	Rect menuRect[5];

	Vec2 starPos[5];

	Sprite* star[5];

	Vec2 starPos2[5];

	Sprite* star2[5];
	
	int currentMenu;

	bool mode_sel;

	float startPos;

	Sprite* modeSel;
	MenuItemImage* mode1;
	MenuItemImage* mode2;
	MenuItemImage* bac;

};

#endif // __HELLOWORLD_SCENE_H__
