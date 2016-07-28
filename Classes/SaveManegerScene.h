#include "cocos2d.h"

USING_NS_CC;

class SaveManeger : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void onBgm(Ref* ref);

	virtual void onEff(Ref* ref);

	// implement the "static create()" method manually
	CREATE_FUNC(SaveManeger);

private:
	MenuItemImage* bgm;

	MenuItemImage* eff;

	bool bgmSel;

	bool effSel;

};

