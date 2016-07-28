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

	//��������λ�ã�Ҫ����init��Ӽ��������÷���touch->getLocation().xΪ�������X���꣬Yͬ��
	//bool onTouchBegan(Touch *touch, Event *unused_event);

	//���¹�����ť�󣬷����̿�ʼ�ڶ�
	//virtual void onAttack(Ref* ref);

	//ȷ������󣬷�����ֹͣ����������ʼ����
	//virtual void onDirection(Ref* ref);

	//ȷ��������ը��Ͷ��
	//virtual void onPower(Ref* ref);

	//��ȡը�����
	int fallPointCal();

	//�ж��ӵ��Ƿ����е��ˣ���һ������Ϊ��㣬�ڶ���Ϊ��ը��Χ
	bool isAttacked(int fallPoint, int range);

	//�����˺�
	//void damageCal(Character*, int damage);

	//�غϽ�����������ң�ͬʱ�趨��ť��Enable������
	void changePlayer();

	//�������ÿһ֡������һ�Σ�������Ҫ������ݣ�����ը����ĳ��ʱ�̵�λ��
	virtual void update(float dt) override;

	virtual void onBack(Ref* ref);

	//���ӵ�
	void bullet1fire();
	void bullet2fire();

	void preloadMusic();
	void playBgm();


	Sprite* addPlayer(int x, int t);// ������, x=������
	void addEdge();// ��ӱ߽��
	void addListener();// ��Ӽ�����
	void getFrameAction();// ���֡��������
	void getFrameAction2();// ���֡��������

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

	void setPlayTag(int i, int t)
	{
		playTag[i] = t;
	}


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

	Sprite* bullet2;

	Sprite* enemy;
	Sprite* brick;
	Sprite* pipe;

	TMXTiledMap* map;
	Vector<Sprite*> brickcontainer;
	Vector<Sprite*> pipecontainer;
	Vector<Sprite*> enemy1container;
	void addmap();
		
	Sprite* test;

	CCProgressTimer* powerBar;

	CCProgressTimer* hp1;



	bool powerDir;

	int currentPlayer;          //���ڻغϵ����

	bool already;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

};
