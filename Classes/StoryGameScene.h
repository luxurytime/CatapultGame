#include "cocos2d.h"
#include <string>
#include "Artillery.h"
#include "Pistol.h"
#include "Knight.h"
#include "Staff.h"
#include "Boy.h"
#include "Girl.h"
#include "Dog.h"
#include "Gay.h"

using namespace std;

USING_NS_CC;

class StoryGame : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene(int p1, bool b);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	//virtual void onEnter();


	// implement the "static create()" method manually
	CREATE_FUNC(StoryGame);

	/////////////////////
	/////////////////////
	/////////////////////

	//检测鼠标点击位置，要现在init添加监听器，用法：touch->getLocation().x为鼠标点击的X坐标，Y同理
	//bool onTouchBegan(Touch *touch, Event *unused_event);

	//按下攻击按钮后，方向盘开始摆动
	//virtual void onAttack(Ref* ref);

	//确定方向后，方向盘停止，力量条开始滑动
	//virtual void onDirection(Ref* ref);

	//确定力量后，炸弹投出
	//virtual void onPower(Ref* ref);

	//获取炸弹落点
	int fallPointCal();

	//判断子弹是否命中敌人，第一个参数为落点，第二个为爆炸范围
	bool isAttacked(int fallPoint, int range);

	//计算伤害
	//void damageCal(Character*, int damage);

	//回合结束，更换玩家，同时设定按钮的Enable等特性
	void changePlayer();

	//这个函数每一帧都调用一次，根据需要添加内容，如获得炸弹在某个时刻的位置
	virtual void update(float dt) override;

	virtual void onBack(Ref* ref);

	//射子弹
	void bulletfire(float x, float y);

	void preloadMusic();
	void playBgm();


	Sprite* addPlayer(int x, int t);// 添加玩家, x=横坐标
	void addEdge();// 添加边界框
	void addListener();// 添加监听器
	void getFrameAction();// 获得帧动画动作
	void getFrameAction2();// 获得帧动画动作

	void addHpBar();


	void addEnemy();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	bool isKeyPressed(EventKeyboard::KeyCode keyCode);

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void onKeyPressedContinue(EventKeyboard::KeyCode keyCode);

	void moveContine(float dt);

	bool onConcactBegan(PhysicsContact& contact);

	void powerRoll(float dt);

	void shootStone(float power, float direction, Vec2 loc);

	void damage(int damage, int player);

	void end();

	void moveDistance();
	void setPlayTag(int i, int t)
	{
		playTag[i] = t;
	}

	void winFrame();


private:

	/////////////
	//////////////
	///////////////
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	//cocos2d::Vector<SpriteFrame*> walk;
	//cocos2d::Vector<SpriteFrame*> dead;
	const int altitude = 70;
	cocos2d::Vector<SpriteFrame*> walk2;
	cocos2d::Vector<SpriteFrame*> dead2;

	Character* player[2];
	int playTag[2];
	//Sprite* player2;

	Sprite* bullet1;
	int bulletNum;
	Sprite* bullet2;
	Sprite* bullet3;
	Sprite* bullet4;
	Sprite* bullet5;



	Sprite* enemy1;
	int enemy1HP = 3;
	Sprite* enemy2;
	int enemy2HP = 3;
	Sprite* enemy3;
	int enemy3HP = 4;
	Sprite* enemy4;
	int enemy4HP = 3;
	Sprite* enemy5;
	int enemy5HP = 3;
	Sprite* enemy6;
	int enemy6HP = 100;

	Sprite* brick;
	Sprite* pipe;
	bool blinkValue = false;
	TMXTiledMap* map;
	TMXLayer* layer;
	Vector<Sprite*> brickcontainer;
	Vector<Sprite*> pipecontainer;
	Vector<Sprite*> enemy1container;
	void addmap();

	Sprite* test;

	CCProgressTimer* powerBar;

	CCProgressTimer* hp1;
	CCProgressTimer* hp2;

	Sprite* sp1;
	Sprite* sp2;

	Label* label;

	bool powerDir;

	int currentPlayer;          //正在回合的玩家

	bool already;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

	int pp1;
	bool isBgm;

	bool winJ;

};
