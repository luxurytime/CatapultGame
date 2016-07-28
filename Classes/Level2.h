#include "cocos2d.h"
#include "Boy.h"
#include <string>

using namespace std;

USING_NS_CC;

class Level2 : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	//virtual void onEnter();


	// implement the "static create()" method manually
	CREATE_FUNC(Level2);

	//�������ÿһ֡������һ�Σ�������Ҫ������ݣ�����ը����ĳ��ʱ�̵�λ��
	virtual void update(float dt) override;

	virtual void onBack(Ref* ref);

	void preloadMusic();

	void playBgm();

	Sprite* addPlayer(int x, int t);// ������, x=������

	void addListener();// ��Ӽ�����

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	bool isKeyPressed(EventKeyboard::KeyCode keyCode);

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void onKeyPressedContinue(EventKeyboard::KeyCode keyCode);

	void moveContine(float dt);

	void addmap();


private:

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	Character* player[2];

	TMXTiledMap* map;
	Sprite* brick;
	Vector<Sprite*> brickcontainer;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

};
