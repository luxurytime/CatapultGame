#include "cocos2d.h"
#include <string>
#include "Artillery.h"
#include "Pistol.h"
#include "Knight.h"
#include "Staff.h"
#include "Boy.h"
using namespace std;

USING_NS_CC;

class Games : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	//virtual void onEnter();


	// implement the "static create()" method manually
	CREATE_FUNC(Games);

	/////////////////////
	/////////////////////
	/////////////////////






	//¼ÆËãÉËº¦
	//void damageCal(Character*, int damage);


	//Õâ¸öº¯ÊýÃ¿Ò»Ö¡¶¼µ÷ÓÃÒ»´Î£¬¸ù¾ÝÐèÒªÌí¼ÓÄÚÈÝ£¬Èç»ñµÃÕ¨µ¯ÔÚÄ³¸öÊ±¿ÌµÄÎ»ÖÃ
	virtual void update(float dt) override;

	virtual void onBack(Ref* ref);


	void preloadMusic();
	void playBgm();


	void addEdge();// Ìí¼Ó±ß½ç¿ò
	void addListener();// Ìí¼Ó¼àÌýÆ÷
	void addHpBar();



	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	bool isKeyPressed(EventKeyboard::KeyCode keyCode);

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);





	/*bool onTouchBegan(Touch *touch, cocos2d::Event *event);

	void onTouchEnded(Touch *touch, cocos2d::Event *event);

	void onTouchMoved(Touch *touch, cocos2d::Event *event);*/

	bool onConcactBegan(PhysicsContact& contact);







	void setPlayTag(int i, int t)
	{
		playTag[i] = t;
	}

	void bullet1fire(float x, float y);
	void bullet2fire(float x, float y);

	void playerdefend1();
	void playerdefend2();

	void damage(float damage, int player);

	void initPlayers();
	void initMap();
	void addObstacle(string filename, float x, float y);

	void moveDistance();
	void win();


private:

	/////////////
	//////////////
	///////////////
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;


	Character* player[2];
	int playTag[2];

	Sprite* bullet1;
	Sprite* bullet2;

	Sprite* defend1;
	Sprite* defend2;
	Sprite* defend11;
	Sprite* defend22;

	bool isBlooding1;
	bool isBlooding2;

	Sprite* bulletBoom1;
	Sprite* bulletBoom2;

	//bool canMove;

	CCProgressTimer* powerBar;

	CCProgressTimer* hp1;

	CCProgressTimer* hp2;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

	cocos2d::Vector<SpriteFrame*> boom;
	cocos2d::Vector<SpriteFrame*> defend;

};
