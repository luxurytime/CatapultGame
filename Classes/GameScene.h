#include "cocos2d.h"
#include <string>
#include "Artillery.h"
#include "Pistol.h"
#include "Knight.h"
#include "Staff.h"
#include "Boy.h"
#include "Girl.h"
#include "Gay.h"
#include "Dog.h"

using namespace std;

USING_NS_CC;

class Games : public cocos2d::Layer
{
public:

	void setPhysicsWorld(PhysicsWorld * world);

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene(int p1, int p2, bool b);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(PhysicsWorld* world);

	//virtual void onEnter();


	// implement the "static create()" method manually
	static Games* create(PhysicsWorld* world);
	//CREATE_FUNC(Games);

	/////////////////////
	/////////////////////
	/////////////////////



	virtual void update(float dt) override;

	virtual void onBack(Ref* ref);


	void preloadMusic();
	void playBgm();


	void addEdge();
	void addListener();
	void addHpBar();



	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	bool isKeyPressed(EventKeyboard::KeyCode keyCode);

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);





	/*bool onTouchBegan(Touch *touch, cocos2d::Event *event);

	void onTouchEnded(Touch *touch, cocos2d::Event *event);

	void onTouchMoved(Touch *touch, cocos2d::Event *event);*/

	bool onConcactBegan(PhysicsContact& contact);


	void bullet1fire(float x, float y);
	void bullet2fire(float x, float y);

	void playerdefend1();
	void playerdefend2();

	void playermagic1();
	void playermagic2();

	void damage(float damage, int player);

	void initPlayers();
	void initFrames();
	void initMap();
	void addObstacle(string filename, float x, float y);
	void initCd();

	void moveDistance();
	void win();

	void winFrame();

	


private:
	Games();
	~Games();

	PhysicsWorld* m_world;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	Character* player[2];

	Sprite* bullet1;
	Sprite* bullet2;

	Sprite* defend1;
	Sprite* defend2;

	Sprite* magic1;
	Sprite* magic2;

	Sprite* bulletBoom1;
	Sprite* bulletBoom2;

	CCProgressTimer* hp1;
	CCProgressTimer* hp2;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

	cocos2d::Vector<SpriteFrame*> boom;
	cocos2d::Vector<SpriteFrame*> defend;

	Sprite* cool1;
	Sprite* active1;
	CCProgressTimer* cd1;

	Sprite* cool2;
	Sprite* active2;
	CCProgressTimer* cd2;

	int pp1;
	int pp2;
	bool isBgm;

	bool winJ;

};
