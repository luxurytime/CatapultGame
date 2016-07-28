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

	//¼ì²âÊó±êµã»÷Î»ÖÃ£¬ÒªÏÖÔÚinitÌí¼Ó¼àÌýÆ÷£¬ÓÃ·¨£ºtouch->getLocation().xÎªÊó±êµã»÷µÄX×ø±ê£¬YÍ¬Àí
	//bool onTouchBegan(Touch *touch, Event *unused_event);

	//°´ÏÂ¹¥»÷°´Å¥ºó£¬·½ÏòÅÌ¿ªÊ¼°Ú¶¯
	//virtual void onAttack(Ref* ref);

	//È·¶¨·½Ïòºó£¬·½ÏòÅÌÍ£Ö¹£¬Á¦Á¿Ìõ¿ªÊ¼»¬¶¯
	//virtual void onDirection(Ref* ref);

	//È·¶¨Á¦Á¿ºó£¬Õ¨µ¯Í¶³ö
	//virtual void onPower(Ref* ref);

	//»ñÈ¡Õ¨µ¯Âäµã
	int fallPointCal();

	//ÅÐ¶Ï×Óµ¯ÊÇ·ñÃüÖÐµÐÈË£¬µÚÒ»¸ö²ÎÊýÎªÂäµã£¬µÚ¶þ¸öÎª±¬Õ¨·¶Î§
	bool isAttacked(int fallPoint, int range);

	//¼ÆËãÉËº¦
	//void damageCal(Character*, int damage);

	//»ØºÏ½áÊø£¬¸ü»»Íæ¼Ò£¬Í¬Ê±Éè¶¨°´Å¥µÄEnableµÈÌØÐÔ
	void changePlayer();

	//Õâ¸öº¯ÊýÃ¿Ò»Ö¡¶¼µ÷ÓÃÒ»´Î£¬¸ù¾ÝÐèÒªÌí¼ÓÄÚÈÝ£¬Èç»ñµÃÕ¨µ¯ÔÚÄ³¸öÊ±¿ÌµÄÎ»ÖÃ
	virtual void update(float dt) override;

	virtual void onBack(Ref* ref);

	//Éä×Óµ¯
	void bullet1fire();
	void bullet2fire();

	void preloadMusic();
	void playBgm();


	Sprite* addPlayer(int x, int t);// Ìí¼ÓÍæ¼Ò, x=ºá×ø±ê
	void addEdge();// Ìí¼Ó±ß½ç¿ò
	void addListener();// Ìí¼Ó¼àÌýÆ÷
	void getFrameAction();// »ñµÃÖ¡¶¯»­¶¯×÷
	void getFrameAction2();// »ñµÃÖ¡¶¯»­¶¯×÷

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

	int currentPlayer; 

	bool already;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

};
