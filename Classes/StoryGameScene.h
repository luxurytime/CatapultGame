#include "cocos2d.h"
#include <string>
#include "Artillery.h"
#include "Pistol.h"
#include "Knight.h"
#include "Staff.h"
#include "Boy.h"
using namespace std;

USING_NS_CC;

class StoryGame : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	//virtual void onEnter();


	// implement the "static create()" method manually
	CREATE_FUNC(StoryGame);

	/////////////////////
	/////////////////////
	/////////////////////

	void preloadMusic();
	void playBgm();


	Sprite* addPlayer(int x, int t);// 添加玩家, x=横坐标
	void addEdge();// 添加边界框
	void addListener();// 添加监听器
	void getFrameAction();// 获得帧动画动作

	void addHpBar();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	bool isKeyPressed(EventKeyboard::KeyCode keyCode);

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void onKeyPressedContinue(EventKeyboard::KeyCode keyCode);

	void moveContine(float dt);
	void update(float dt);

	void addmap();

private:

	/////////////
	//////////////
	///////////////
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Vector<SpriteFrame*> walk2;
	cocos2d::Vector<SpriteFrame*> dead2;
	//cocos2d::experimental::TMXTiledMap * map;
	TMXTiledMap* map;
	Vector<Sprite*> brickcontainer;
	Vector<Sprite*> pipecontainer;

	CCProgressTimer* powerBar;

	CCProgressTimer* hp1;
	Character* player[2];
	int playTag[2];


	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

};
