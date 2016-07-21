#include "cocos2d.h"
#include <string>
#include "Artillery.h"
#include "Pistol.h"
#include "Knight.h"
#include "Staff.h"
using namespace std;

USING_NS_CC;

class Games : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();


	// implement the "static create()" method manually
	CREATE_FUNC(Games);

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
	void bullet1fire();
	void bullet2fire();

	void preloadMusic();
	void playBgm();

	
	Sprite* addPlayer(int x);// 添加玩家, x=横坐标
	void addEdge();// 添加边界框
	void addListener();// 添加监听器
	void getFrameAction();// 获得帧动画动作

	void addHpBar();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	bool onTouchBegan(Touch *touch, cocos2d::Event *event);

	void onTouchEnded(Touch *touch, cocos2d::Event *event);

	void onTouchMoved(Touch *touch, cocos2d::Event *event);

	bool onConcactBegan(PhysicsContact& contact);

	void powerRoll(float dt);

	void shootStone(float power, float direction, Vec2 loc);

	void damage(int damage, int player);


private:

	/////////////
	//////////////
	///////////////
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Vector<SpriteFrame*> walk;
	cocos2d::Vector<SpriteFrame*> dead;

	Sprite* player[2];
	//Sprite* player2;

	Sprite* bullet1;
	Sprite* bullet2;

	Sprite* sp1;
	Sprite* sp2;
	Sprite* sp;
	Sprite* test;

	CCProgressTimer* powerBar;

	CCProgressTimer* hp1;

	CCProgressTimer* hp2;

	bool powerDir;

	int currentPlayer;          //正在回合的玩家
	
};
