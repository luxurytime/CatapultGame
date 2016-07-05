#include "cocos2d.h"
#include <string>
using namespace std;

USING_NS_CC;

class Select : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	virtual void onStart(Ref* ref);


	// implement the "static create()" method manually
	CREATE_FUNC(Select);

private:

};
