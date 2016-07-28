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

	bool onTouchBegan(Touch *touch, cocos2d::Event *event);

	///////////////////////////////////
	///////////////////////////////////
	///////////////////////////////////

	//bool onTouchBegan(Touch *touch, Event *unused_event);

	int getPos(float x);

	void addChara();

	void reAddChara();

	void flyAway();

	void addMap();

	void flyMap();

private:

	Sprite* charac[3];

	Sprite* maps[3];

	Sprite* red;
	Sprite* blue;

	int selected;
	//Sprite* bigC[4];

	int player1;
	int player2;

	int current;

	//////////////
	//////////////
	//////////////
	//Arms selectedArm;
	//Character selectedCharacter;

	Sprite* p1;
	Sprite* p2;

	MenuItemImage* startMenuItem;


};
