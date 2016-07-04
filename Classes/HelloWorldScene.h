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

	void onMouseMove(Event* event);

	void largerItem(MenuItemImage* item, int i);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	MenuItemImage* startMenuItem;
};

#endif // __HELLOWORLD_SCENE_H__
