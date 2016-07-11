#include "cocos2d.h"
#include <string>
using namespace std;
#include "Artillery.h"
#include "Pistol.h"
#include "Knight.h"
#include "Staff.h"

USING_NS_CC;

class Select : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	virtual void onStart(Ref* ref);

	void onMouseMove(Event* event);
	// implement the "static create()" method manually
	CREATE_FUNC(Select);

	///////////////////////////////////
	///////////////////////////////////
	///////////////////////////////////

	//检测鼠标点击位置，要现在init添加监听器，用法：touch->getLocation().x为鼠标点击的X坐标，Y同理
	//点击人物和武器相应位置后，在大框中显示那个人物或武器
	bool onTouchBegan(Touch *touch, Event *unused_event);

private:

	//////////////
	//////////////
	//////////////
	Arms selectedArm;
	Character selectedCharacter;


};
