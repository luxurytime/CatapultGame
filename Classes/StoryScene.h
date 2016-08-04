#include "cocos2d.h"

USING_NS_CC;

class Story : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void onEnter();

	void addChara();

	void flyAway();

	void levelDown();

	virtual void onStart(Ref* ref);

	// implement the "static create()" method manually
	CREATE_FUNC(Story);

	bool onTouchBegan(Touch *touch, cocos2d::Event *event);

	bool isBgm;

private:
	Sprite* charac[3];

	MenuItemImage* level[4];

	Sprite* levelMon[4];

	int current;

	int selected;

	int pl;

	Sprite* p1;

};

