#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "EndScene.h"
#include <math.h>

using namespace CocosDenshion;

USING_NS_CC;

void Games::setPhysicsWorld(PhysicsWorld* world) { m_world = world; }

static int ppp1;
static int ppp2;
static bool isBgmp;

Games::Games()
	: m_world(NULL)
{

}

Games::~Games()
{
}

Scene* Games::createScene(int p1, int p2, bool b)
{
	ppp1 = p1;
	ppp2 = p2;
	isBgmp = b;

	//auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Point(0, -800));
	//scene->getPhysicsWorld()->setAutoStep(false);

	auto layer = Games::create(scene->getPhysicsWorld());

	scene->addChild(layer);

	return scene;
}

Games* Games::create(PhysicsWorld* world)
{
	Games* pRet = new Games();
	if (pRet && pRet->init(world))
	{
		return pRet;
	}
	pRet = NULL;
	return NULL;
}

bool Games::init(PhysicsWorld* world)
{
	if (!Layer::init())
	{
		return false;
	}
	m_world = world;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	pp1 = ppp1;
	pp2 = ppp2;
	isBgm = isBgmp;

	winJ = true;

	Sprite* background = Sprite::create("back2.jpg");
	background->setScale(0.65);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);

	auto label = LabelTTF::create("MainMenu", "Marker Felt.ttf", 48);
	auto menuItem = MenuItemLabel::create(label);
	auto menu = Menu::create(menuItem, nullptr);
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	});
	menu->setPosition(Vec2::ZERO);
	menuItem->setPosition(visibleSize.width*0.2, visibleSize.height*0.9);
	//addChild(menu, 1);

	initPlayers();
	initMap();
	initFrames();
	initCd();
	addEdge();



	preloadMusic();
	playBgm();


	addListener();

	bullet1 = NULL;
	bullet2 = NULL;
	defend1 = NULL;
	defend2 = NULL;
	magic1 = NULL;
	magic2 = NULL;


	scheduleUpdate();

	m_world->setAutoStep(false);

	return true;
}

void Games::initFrames(){
	boom.reserve(9);
	auto frame1 = SpriteFrame::create("3/image 3.png", Rect(0, 0, 300, 300));
	auto frame2 = SpriteFrame::create("3/image 4.png", Rect(0, 0, 300, 300));
	auto frame3 = SpriteFrame::create("3/image 5.png", Rect(0, 0, 300, 300));
	auto frame4 = SpriteFrame::create("3/image 6.png", Rect(0, 0, 300, 300));
	auto frame5 = SpriteFrame::create("3/image 7.png", Rect(0, 0, 300, 300));
	auto frame6 = SpriteFrame::create("3/image 8.png", Rect(0, 0, 300, 300));
	auto frame7 = SpriteFrame::create("3/image 9.png", Rect(0, 0, 300, 300));
	auto frame8 = SpriteFrame::create("3/image 10.png", Rect(0, 0, 300, 300));
	auto frame9 = SpriteFrame::create("3/image 11.png", Rect(0, 0, 300, 300));
	boom.pushBack(frame1);
	boom.pushBack(frame2);
	boom.pushBack(frame3);
	boom.pushBack(frame4);
	boom.pushBack(frame5);
	boom.pushBack(frame6);
	boom.pushBack(frame7);
	boom.pushBack(frame8);
	boom.pushBack(frame9);


	defend.reserve(12);
	auto dfframe1 = SpriteFrame::create("2/image  (1).png", Rect(0, 0, 192, 192));
	auto dfframe2 = SpriteFrame::create("2/image  (2).png", Rect(0, 0, 192, 192));
	auto dfframe3 = SpriteFrame::create("2/image  (3).png", Rect(0, 0, 192, 192));
	auto dfframe4 = SpriteFrame::create("2/image  (4).png", Rect(0, 0, 192, 192));
	auto dfframe5 = SpriteFrame::create("2/image  (5).png", Rect(0, 0, 192, 192));
	auto dfframe6 = SpriteFrame::create("2/image  (6).png", Rect(0, 0, 192, 192));
	auto dfframe7 = SpriteFrame::create("2/image  (7).png", Rect(0, 0, 192, 192));
	auto dfframe8 = SpriteFrame::create("2/image  (8).png", Rect(0, 0, 192, 192));
	auto dfframe9 = SpriteFrame::create("2/image  (9).png", Rect(0, 0, 192, 192));
	auto dfframe10 = SpriteFrame::create("2/image  (10).png", Rect(0, 0, 192, 192));
	auto dfframe11 = SpriteFrame::create("2/image  (11).png", Rect(0, 0, 192, 192));
	auto dfframe12 = SpriteFrame::create("2/image  (12).png", Rect(0, 0, 192, 192));
	defend.pushBack(dfframe1);
	defend.pushBack(dfframe2);
	defend.pushBack(dfframe3);
	defend.pushBack(dfframe4);
	defend.pushBack(dfframe5);
	defend.pushBack(dfframe6);
	defend.pushBack(dfframe7);
	defend.pushBack(dfframe8);
	defend.pushBack(dfframe9);
	defend.pushBack(dfframe10);
	defend.pushBack(dfframe11);
	defend.pushBack(dfframe12);
}

void Games::initPlayers(){
	if (pp1 == 0)
	{
		player[0] = new Girl();
	}
	else if (pp1 == 1)
	{
		player[0] = new Boy();
	}
	else if (pp1 == 2)
	{
		player[0] = new Dog();
	}

	if (pp2 == 0)
	{
		player[1] = new Girl();
	}
	else if (pp2 == 1)
	{
		player[1] = new Boy();
	}
	else if (pp2 == 2)
	{
		player[1] = new Dog();
	}

	//player[0]->getCharaSpr()->setPosition(origin.x + visibleSize.width / 4, player[0]->getCharaSpr()->getContentSize().height / 2);
	player[0]->getCharaSpr()->setPosition(origin.x + visibleSize.width / 8, visibleSize.height / 2);
	player[0]->getCharaSpr()->setTag(0);
	player[0]->getCharaSpr()->getPhysicsBody()->setCategoryBitmask(0x0001);
	player[0]->getCharaSpr()->getPhysicsBody()->setCollisionBitmask(0x0001);
	player[0]->getCharaSpr()->getPhysicsBody()->setContactTestBitmask(0x0001);
	addChild(player[0]->getCharaSpr(), 2);

	//player[1]->getCharaSpr()->setPosition(origin.x + visibleSize.width / 4 * 3, player[1]->getCharaSpr()->getContentSize().height / 2);
	player[1]->getCharaSpr()->setPosition(origin.x + visibleSize.width / 4 * 3, visibleSize.height / 2);
	player[1]->getCharaSpr()->setTag(1);
	player[1]->getCharaSpr()->setFlipX(true);
	player[1]->setIsRight(false);
	player[1]->getCharaSpr()->getPhysicsBody()->setCategoryBitmask(0x0010);
	player[1]->getCharaSpr()->getPhysicsBody()->setCollisionBitmask(0x0010);
	player[1]->getCharaSpr()->getPhysicsBody()->setContactTestBitmask(0x0010);
	addChild(player[1]->getCharaSpr(), 2);
}

void Games::initMap(){

	auto ground = Sprite::create("Ground.png");
	ground->setScaleX(1.1);
	ground->setScaleY(0.5);
	ground->setPosition(visibleSize.width / 2, 22.5);
	auto groundBody = PhysicsBody::createBox(ground->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 0.0f));
	groundBody->setDynamic(false);
	groundBody->setCategoryBitmask(0x0011);
	groundBody->setCollisionBitmask(0x0011);
	groundBody->setContactTestBitmask(0x0011);
	ground->setPhysicsBody(groundBody);
	ground->setTag(3);
	addChild(ground, 2);

	//addObstacle("Platform_long(5).png", 500, 100);
	addObstacle("Platform_long(4).png", 350, 200);
	addObstacle("Platform_long(3).png", 700, 200);
	//addObstacle("Platform_square(3).png", 45, 45);
	//addObstacle("Platform_square(3).png", 135, 45);
	addObstacle("Platform_long(1).png", 200, 320);
	addObstacle("Platform_long(6).png", 540, 400);
	addObstacle("Platform_long(6).png", 870, 200);
	addObstacle("Platform_long(6).png", 90, 200);

	addHpBar();

}

void Games::initCd(){

	if (pp1 == 0)
	{
		cool1 = Sprite::create("Skill/SKill_22.png");
		active1 = Sprite::create("Skill/SKill_2.png");
	}
	else if (pp1 == 1)
	{
		cool1 = Sprite::create("Skill/SKill_11.png");
		active1 = Sprite::create("Skill/SKill_1.png");
	}
	else if (pp1 == 2)
	{
		cool1 = Sprite::create("Skill/SKill_33.png");
		active1 = Sprite::create("Skill/SKill_3.png");
	}

	if (pp2 == 0)
	{
		cool2 = Sprite::create("Skill/SKill_22.png");
		active2 = Sprite::create("Skill/SKill_2.png");
	}
	else if (pp2 == 1)
	{
		cool2 = Sprite::create("Skill/SKill_11.png");
		active2 = Sprite::create("Skill/SKill_1.png");
	}
	else if (pp2 == 2)
	{
		cool2 = Sprite::create("Skill/SKill_33.png");
		active2 = Sprite::create("Skill/SKill_3.png");
	}

	cool1->setScale(0.8);
	active1->setScale(0.8);
	
	cool1->setPosition(50, visibleSize.height - 110);
	addChild(cool1, 0);
	cd1 = ProgressTimer::create(active1);
	cd1->setType(ProgressTimerType::RADIAL);
	cd1->setPercentage(100);
	//cd1->setPosition(visibleSize.width / 4, visibleSize.height * 3 / 4);
	cd1->setPosition(50, visibleSize.height-110);
	addChild(cd1, 1);
	cd1->setScale(0.8);

	cool2->setScale(0.8);
	active2->setScale(0.8);

	cool2->setPosition(visibleSize.width - 50, visibleSize.height - 110);
	addChild(cool2, 0);
	cd2 = ProgressTimer::create(active2);
	cd2->setType(ProgressTimerType::RADIAL);
	cd2->setPercentage(100);
	cd2->setPosition(visibleSize.width-50, visibleSize.height - 110);
	addChild(cd2, 1);
	cd2->setScale(0.8);
}

void Games::addObstacle(string filename, float x, float y){
	auto obstacle = Sprite::create(filename);
	obstacle->setPosition(x, y);
	Size a(obstacle->getContentSize().width, 3);
	auto obstacleBody = PhysicsBody::createBox(a, PhysicsMaterial(1.0f, 0.0f, 0.0f));
	obstacleBody->setPositionOffset(Vec2(0, obstacle->getContentSize().height / 2));
	obstacleBody->setDynamic(false);
	obstacleBody->setCategoryBitmask(0x0011);
	obstacleBody->setCollisionBitmask(0x0011);
	obstacleBody->setContactTestBitmask(0x0011);
	obstacle->setPhysicsBody(obstacleBody);
	obstacle->setTag(3);
	addChild(obstacle, 2);

	auto obstacle_down = Sprite::create();
	obstacle_down->setPosition(x, y);
	Size b(obstacle->getContentSize().width, obstacle->getContentSize().height - 6);
	auto obstacleDownBody = PhysicsBody::createBox(b, PhysicsMaterial(1.0f, 0.0f, 0.0f));
	obstacleDownBody->setDynamic(false);
	obstacleDownBody->setCategoryBitmask(0x0011);
	obstacleDownBody->setCollisionBitmask(0x0011);
	obstacleDownBody->setContactTestBitmask(0x0100);
	obstacle_down->setPhysicsBody(obstacleDownBody);
	obstacle_down->setTag(7);
	addChild(obstacle_down, 2);

}


void Games::addHpBar(){
	Sprite* sp1 = Sprite::create("HP_1.png");
	Sprite* sp2 = Sprite::create("HP_3.png");
	Sprite* sp = Sprite::create("HP_2.png");

	//血条1
	hp1 = ProgressTimer::create(sp);
	//hp1->setScaleX(90);
	hp1->setAnchorPoint(Vec2(0, 0));
	hp1->setType(ProgressTimerType::BAR);
	hp1->setBarChangeRate(Point(1, 0));
	hp1->setMidpoint(Point(0, 1));
	hp1->setPercentage(100);
	//hp1->setPosition(Vec2(origin.x + 14 * hp1->getContentSize().width, origin.y + visibleSize.height - 2 * hp1->getContentSize().height));
	
	addChild(hp1, 1);
	sp1->setAnchorPoint(Vec2(0, 0));
	
	//sp1->setPosition(Vec2(origin.x + hp1->getContentSize().width, origin.y + visibleSize.height - sp1->getContentSize().height));
	addChild(sp1, 0);

	hp1->setPosition(Vec2(origin.x + 112, origin.y + visibleSize.height - 50));
	sp1->setPosition(Vec2(origin.x + 10, origin.y + visibleSize.height - sp1->getContentSize().height));

	//血条2
	hp2 = ProgressTimer::create(sp);
	//hp2->setScaleX(90);
	hp2->setAnchorPoint(Vec2(0, 0));
	hp2->setType(ProgressTimerType::BAR);
	hp2->setBarChangeRate(Point(1, 0));
	hp2->setMidpoint(Point(1, 0));
	hp2->setPercentage(100);
	hp2->setPosition(Vec2(origin.x + visibleSize.width / 2 + 21 * hp2->getContentSize().width, origin.y + visibleSize.height - 2 * hp2->getContentSize().height));
	addChild(hp2, 1);
	sp2->setAnchorPoint(Vec2(0, 0));
	sp2->setPosition(Vec2(origin.x + visibleSize.width / 2 + 18 * hp2->getContentSize().width + 1.5, origin.y + visibleSize.height - sp2->getContentSize().height));
	addChild(sp2, 0);


	hp2->setPosition(Vec2(origin.x + visibleSize.width/2+112+10, origin.y + visibleSize.height - 50));
	sp2->setPosition(Vec2(origin.x + visibleSize.width/2 +32+10, origin.y + visibleSize.height - sp1->getContentSize().height));
	//sp2->setFlipX(true);
}


void Games::preloadMusic() {
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm11.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("shoot.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("move.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("shout.mp3");
}

void Games::playBgm() {
	if (isBgm)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm11.mp3", true);
	}
}

void Games::addEdge(){
	auto edge = Sprite::create();
	edge->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	Size b;
	b.setSize(visibleSize.width, visibleSize.height + 6 * player[0]->getCharaSpr()->getContentSize().height);
	auto edgeBody = PhysicsBody::createEdgeBox(b, PhysicsMaterial(0.0f, 0.0f, 0.0f), 10.0f);
	//auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.0f, 0.0f, 0.5f), 5.0f);
	edgeBody->setDynamic(false);
	edgeBody->setCategoryBitmask(0x0011);
	edgeBody->setCollisionBitmask(0x0011);
	edgeBody->setContactTestBitmask(0x0100);
	edge->setPhysicsBody(edgeBody);
	edge->setTag(2);
	addChild(edge, 1);
}

void Games::addListener()
{

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Games::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Games::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);


	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Games::onConcactBegan, this);
	_eventDispatcher->addEventListenerWithFixedPriority(contactListener, 1);


	//auto listener = EventListenerTouchOneByOne::create(); 
	//listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	//listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	//listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


void Games::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

	keys[keyCode] = true;

	auto animate0 = Animate::create(Animation::createWithSpriteFrames(player[0]->getWalkFrame(), 0.05f));
	auto animate1 = Animate::create(Animation::createWithSpriteFrames(player[1]->getWalkFrame(), 0.05f));





	switch (keyCode)
	{

		//player1
	case cocos2d::EventKeyboard::KeyCode::KEY_A:

		player[0]->getCharaSpr()->stopAllActions();
		if (player[0]->getJumpNum() == 0){
			SimpleAudioEngine::sharedEngine()->playEffect("move.mp3");
			player[0]->getCharaSpr()->runAction(RepeatForever::create(animate0));
		}
		if (isKeyPressed(EventKeyboard::KeyCode::KEY_D)){
			Director::sharedDirector()->getActionManager()->pauseTarget(player[0]->getCharaSpr());
		}
		player[0]->setMoveDis(player[0]->getMoveDis() - player[0]->getSpeed());
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		player[0]->getCharaSpr()->stopAllActions();
		if (player[0]->getJumpNum() == 0){
			SimpleAudioEngine::sharedEngine()->playEffect("move.mp3");
			player[0]->getCharaSpr()->runAction(RepeatForever::create(animate0));
		}
		if (isKeyPressed(EventKeyboard::KeyCode::KEY_A)){
			Director::sharedDirector()->getActionManager()->pauseTarget(player[0]->getCharaSpr());
		}
		player[0]->setMoveDis(player[0]->getMoveDis() + player[0]->getSpeed());
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		player[0]->getCharaSpr()->stopAllActions();
		if (player[0]->getJumpNum() == 0) {
			player[0]->getCharaSpr()->getPhysicsBody()->setVelocity(Vec2(player[0]->getCharaSpr()->getPhysicsBody()->getVelocity().x, 400));
			player[0]->setJumpNum(player[0]->getJumpNum() + 1);
		}
		else {
			if (player[0]->getJumpNum() == 1) {
				player[0]->getCharaSpr()->getPhysicsBody()->setVelocity(Vec2(player[0]->getCharaSpr()->getPhysicsBody()->getVelocity().x, 400));
				player[0]->setJumpNum(player[0]->getJumpNum() + 1);
			}
		}
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_G:
		if (bullet1 == NULL){
			SimpleAudioEngine::sharedEngine()->playEffect("shoot.mp3");
			if (player[0]->getJumpNum() == 0) {
				if (player[0]->getIsRight()) {
					bullet1fire(400, 0);
				}
				else {
					bullet1fire(-400, 0);
				}
			}
			else {
				if (player[0]->getIsRight()) {
					bullet1fire(400, -400);
				}
				else {
					bullet1fire(-400, -400);
				}
			}
		}
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_H:
		if (cd1->getPercentage() == 100) {
			cd1->setPercentage(0);
			if (pp1 == 0)
			{
				damage(25, 0);
			}
			else if (pp1 == 1)
			{
				playermagic1();
			}
			else if (pp1 == 2)
			{
				playerdefend1();
			}
			
			
			auto cdAct = ProgressTo::create(8.0, 100);
			cd1->runAction(cdAct);
		}
		break;


		//player2
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:

		player[1]->getCharaSpr()->stopAllActions();
		if (player[1]->getJumpNum() == 0){
			SimpleAudioEngine::sharedEngine()->playEffect("move.mp3");
			player[1]->getCharaSpr()->runAction(RepeatForever::create(animate1));
		}
		if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)){
			Director::sharedDirector()->getActionManager()->pauseTarget(player[1]->getCharaSpr());
		}


		player[1]->setMoveDis(player[1]->getMoveDis() - player[1]->getSpeed());
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:

		player[1]->getCharaSpr()->stopAllActions();
		if (player[1]->getJumpNum() == 0){
			SimpleAudioEngine::sharedEngine()->playEffect("move.mp3");
			player[1]->getCharaSpr()->runAction(RepeatForever::create(animate1));
		}
		if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)){
			Director::sharedDirector()->getActionManager()->pauseTarget(player[1]->getCharaSpr());
		}


		player[1]->setMoveDis(player[1]->getMoveDis() + player[1]->getSpeed());
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:

		player[1]->getCharaSpr()->stopAllActions();
		if (player[1]->getJumpNum() == 0) {
			player[1]->getCharaSpr()->getPhysicsBody()->setVelocity(Vec2(player[1]->getCharaSpr()->getPhysicsBody()->getVelocity().x, 400));
			player[1]->setJumpNum(player[1]->getJumpNum() + 1);
		}
		else {
			if (player[1]->getJumpNum() == 1) {
				player[1]->getCharaSpr()->getPhysicsBody()->setVelocity(Vec2(player[1]->getCharaSpr()->getPhysicsBody()->getVelocity().x, 400));
				player[1]->setJumpNum(player[1]->getJumpNum() + 1);
			}
		}


		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_K:
		if (bullet2 == NULL){
			SimpleAudioEngine::sharedEngine()->playEffect("shoot.mp3");
			if (player[1]->getJumpNum() == 0) {
				if (player[1]->getIsRight()) {
					bullet2fire(400, 0);
				}
				else {
					bullet2fire(-400, 0);
				}
			}
			else {
				if (player[1]->getIsRight()) {
					bullet2fire(400, -400);
				}
				else {
					bullet2fire(-400, -400);
				}
			}
		}

		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_L:
		if (cd2->getPercentage() == 100) {
			cd2->setPercentage(0);
			if (pp2 == 0)
			{
				damage(25, 1);
			}
			else if (pp2 == 1)
			{
				playermagic2();
			}
			else if (pp2 == 2)
			{
				playerdefend2();
			}

			
			auto cdAct = ProgressTo::create(8.0, 100);
			cd2->runAction(cdAct);
		}

		break;

	default:
		break;
	}
}

bool Games::isKeyPressed(EventKeyboard::KeyCode keyCode)
{
	if (keys[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}

void Games::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	keys[keyCode] = false;

	auto animate0 = Animate::create(Animation::createWithSpriteFrames(player[0]->getWalkFrame(), 0.05f));
	auto animate1 = Animate::create(Animation::createWithSpriteFrames(player[1]->getWalkFrame(), 0.05f));

	switch (keyCode) {

		//player1
	case cocos2d::EventKeyboard::KeyCode::KEY_A:

		player[0]->setMoveDis(player[0]->getMoveDis() + player[0]->getSpeed());
		if (isKeyPressed(EventKeyboard::KeyCode::KEY_D)) {
			if (player[0]->getJumpNum() == 0) {
				player[0]->getCharaSpr()->stopAllActions();
				player[0]->getCharaSpr()->runAction(RepeatForever::create(animate0));
			}

		}
		else {
			player[0]->getCharaSpr()->stopAllActions();
		}


		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:


		player[0]->setMoveDis(player[0]->getMoveDis() - player[0]->getSpeed());

		if (isKeyPressed(EventKeyboard::KeyCode::KEY_A) == 1) {
			if (player[0]->getJumpNum() == 0) {
				player[0]->getCharaSpr()->stopAllActions();
				player[0]->getCharaSpr()->runAction(RepeatForever::create(animate0));
			}
		}
		else {
			player[0]->getCharaSpr()->stopAllActions();
		}
		break;

		//player2
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:

		player[1]->setMoveDis(player[1]->getMoveDis() + player[1]->getSpeed());


		if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
			if (player[1]->getJumpNum() == 0) {
				player[1]->getCharaSpr()->stopAllActions();
				player[1]->getCharaSpr()->runAction(RepeatForever::create(animate1));
			}

		}
		else {
			player[1]->getCharaSpr()->stopAllActions();
		}

		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:


		player[1]->setMoveDis(player[1]->getMoveDis() - player[1]->getSpeed());


		if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) == 1) {
			if (player[1]->getJumpNum() == 0) {
				player[1]->getCharaSpr()->stopAllActions();
				player[1]->getCharaSpr()->runAction(RepeatForever::create(animate1));
			}
		}
		else {
			player[1]->getCharaSpr()->stopAllActions();
		}


		break;
	default:
		break;
	}
}


void Games::update(float dt){


	for (int i = 0; i < 3; ++i)
	{
		//Director::getInstance()->getRunningScene()->getPhysicsWorld()->step(1 / 180.0f);
		m_world->step(1 / 180.0f);
	}

	if (isKeyPressed(EventKeyboard::KeyCode::KEY_A) && (!isKeyPressed(EventKeyboard::KeyCode::KEY_D))) {
		player[0]->getCharaSpr()->setFlipX(true);
		player[0]->setIsRight(false);
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_D) && (!isKeyPressed(EventKeyboard::KeyCode::KEY_A))) {
		player[0]->getCharaSpr()->setFlipX(false);
		player[0]->setIsRight(true);
	}

	if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) && (!isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW))) {
		player[1]->getCharaSpr()->setFlipX(true);
		player[1]->setIsRight(false);
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) && (!isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW))) {
		player[1]->getCharaSpr()->setFlipX(false);
		player[1]->setIsRight(true);
	}


	if (defend1 != NULL){
		defend1->setPosition(player[0]->getCharaSpr()->getPosition());
	}
	if (defend2 != NULL){
		defend2->setPosition(player[1]->getCharaSpr()->getPosition());
	}

	moveDistance();
	win();

}

void Games::moveDistance() {
	player[0]->getCharaSpr()->getPhysicsBody()->setVelocity(Vec2(player[0]->getMoveDis(), player[0]->getCharaSpr()->getPhysicsBody()->getVelocity().y));
	player[1]->getCharaSpr()->getPhysicsBody()->setVelocity(Vec2(player[1]->getMoveDis(), player[1]->getCharaSpr()->getPhysicsBody()->getVelocity().y));
}

bool Games::onConcactBegan(PhysicsContact& contact) {
	Sprite* spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	Sprite* spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();
	int tagA = spriteA->getTag();
	int tagB = spriteB->getTag();

	log("tagA:%d  tagB:%d", tagA, tagB);

	/*
	player[0] 0
	player[1] 1
	edge      2
	obsatle   3
	bullet1   4
	bullet2   5
	obsatle_down 7
	defend1 8
	defend2 8
	magic1 9
	magic2 10
	*/

	auto walkAnimate0 = Animate::create(Animation::createWithSpriteFrames(player[0]->getWalkFrame(), 0.05f));
	auto walkAnimate1 = Animate::create(Animation::createWithSpriteFrames(player[1]->getWalkFrame(), 0.05f));

	if ((tagA == 0 && tagB == 3) || (tagB == 0 && tagA == 3)){
		player[0]->setJumpNum(0);
		if (isKeyPressed(EventKeyboard::KeyCode::KEY_A) || isKeyPressed(EventKeyboard::KeyCode::KEY_D)) {
			player[0]->getCharaSpr()->stopAllActions();
			player[0]->getCharaSpr()->runAction(RepeatForever::create(walkAnimate0));
		}
	}

	if ((tagA == 1 && tagB == 3) || (tagB == 1 && tagA == 3)){
		player[1]->setJumpNum(0);
		if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) || isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
			player[1]->getCharaSpr()->stopAllActions();
			player[1]->getCharaSpr()->runAction(RepeatForever::create(walkAnimate1));
		}
	}

	if (tagA == 5 || tagB == 5) {
		if (bullet2 != NULL){
			Vec2 loc = bullet2->getPosition();

			bulletBoom2 = Sprite::create();
			bulletBoom2->setPosition(loc);
			addChild(bulletBoom2, 3);

			auto changestate = CallFunc::create([&]() {
				bulletBoom2->removeFromParent();
				bulletBoom2 = NULL;
				bullet2 = NULL;
			});

			bulletBoom2->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(boom, 0.09f)), changestate, NULL));


			bullet2->removeFromParent();

			if (tagA == 0 || tagB == 0) {
				SimpleAudioEngine::sharedEngine()->playEffect("shout.mp3");
				damage(-25, 0);
			}
		}
	}



	if (tagA == 4 || tagB == 4) {
		if (bullet1 != NULL){
			Vec2 loc = bullet1->getPosition();
			bulletBoom1 = Sprite::create();
			bulletBoom1->setPosition(loc);
			addChild(bulletBoom1, 3);

			auto changestate = CallFunc::create([&]() {
				bulletBoom1->removeFromParent();
				bulletBoom1 = NULL;
				bullet1 = NULL;
			});

			bulletBoom1->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(boom, 0.09f)), changestate, NULL));
			bullet1->removeFromParent();

			if (tagA == 1 || tagB == 1) {
				SimpleAudioEngine::sharedEngine()->playEffect("shout.mp3");
				damage(-25, 1);
			}
		}
	}

	if (tagA == 9 || tagB == 9) {
		if (tagA == 1 || tagB == 1) {
			SimpleAudioEngine::sharedEngine()->playEffect("shout.mp3");
			damage(-25, 1);
		}
		if (magic1 != NULL) {
			magic1->removeFromParent();
			magic1 = NULL;
		}
	}

	if (tagA == 10 || tagB == 10) {
		if (tagA == 0 || tagB == 0) {
			SimpleAudioEngine::sharedEngine()->playEffect("shout.mp3");
			damage(-25, 0);
		}
		if (magic2 != NULL) {
			magic2->removeFromParent();
			magic2 = NULL;
		}
		
	}

	return true;
}

void Games::onBack(Ref* ref)
{
	Director::getInstance()->replaceScene(CCTransitionProgressOutIn::create(1.0f, HelloWorld::createScene()));
}

void Games::bullet1fire(float x, float y){
	if (bullet1 == NULL) {
		bullet1 = Sprite::create("image 1.png");
		bullet1->setTag(4);
		if (player[0]->getIsRight()) {
			bullet1->setPosition(Vec2(player[0]->getCharaSpr()->getPosition().x + player[0]->getCharaSpr()->getContentSize().width / 2 + bullet1->getContentSize().width / 2, player[0]->getCharaSpr()->getPosition().y));
		}
		else {
			bullet1->setPosition(Vec2(player[0]->getCharaSpr()->getPosition().x - player[0]->getCharaSpr()->getContentSize().width / 2 - bullet1->getContentSize().width / 2, player[0]->getCharaSpr()->getPosition().y));
		}
		addChild(bullet1, 2);
		bullet1->setPhysicsBody(PhysicsBody::createCircle(bullet1->getContentSize().width / 8, PhysicsMaterial(0.0f, 0.0f, 0.0f)));
		bullet1->getPhysicsBody()->setVelocity(Vec2(x, y));
		bullet1->getPhysicsBody()->setCategoryBitmask(0x10110);
		bullet1->getPhysicsBody()->setCollisionBitmask(0x10110);
		bullet1->getPhysicsBody()->setContactTestBitmask(0x10110);
		bullet1->getPhysicsBody()->setGravityEnable(false);
	}
}

void Games::bullet2fire(float x, float y){


	if (bullet2 == NULL) {
		bullet2 = Sprite::create("image 1.png");
		bullet2->setFlipX(true);
		bullet2->setTag(5);
		if (player[1]->getIsRight()) {
			bullet2->setPosition(Vec2(player[1]->getCharaSpr()->getPosition().x + player[1]->getCharaSpr()->getContentSize().width / 2 + bullet2->getContentSize().width / 2, player[1]->getCharaSpr()->getPosition().y));
		}
		else {
			bullet2->setPosition(Vec2(player[1]->getCharaSpr()->getPosition().x - player[1]->getCharaSpr()->getContentSize().width / 2 - bullet2->getContentSize().width / 2, player[1]->getCharaSpr()->getPosition().y));
		}
		addChild(bullet2, 2);
		bullet2->setPhysicsBody(PhysicsBody::createCircle(bullet2->getContentSize().width / 8, PhysicsMaterial(0.0f, 0.0f, 0.0f)));
		bullet2->getPhysicsBody()->setVelocity(Vec2(x, y));
		bullet2->getPhysicsBody()->setContactTestBitmask(0x01101);
		bullet2->getPhysicsBody()->setContactTestBitmask(0x01101);
		bullet2->getPhysicsBody()->setContactTestBitmask(0x01101);
		bullet2->getPhysicsBody()->setGravityEnable(false);
	}
}

void Games::playerdefend1(){

	auto changestate = CallFunc::create([&]() {
		defend1->removeFromParent();
		defend1 = NULL;
	});

	if (defend1 == NULL) {
		defend1 = Sprite::create();
		defend1->setAnchorPoint(Vec2(0.5, 0.5));
		defend1->setPosition(player[0]->getCharaSpr()->getPosition());
		defend1->setTag(8);

		addChild(defend1, 3);
		Size m(player[0]->getCharaSpr()->getContentSize().width * 2, player[0]->getCharaSpr()->getContentSize().height);
		auto defend1Body = PhysicsBody::createBox(player[0]->getCharaSpr()->getContentSize()*1.5, PhysicsMaterial(0.0f, 0.0f, 0.0f));
		defend1Body->setDynamic(false);
		defend1Body->setPositionOffset(Vec2(100, 100));
		defend1Body->setCategoryBitmask(0x01000);
		defend1Body->setCollisionBitmask(0x01000);
		defend1Body->setContactTestBitmask(0x01000);
		defend1->setPhysicsBody(defend1Body);

		defend1->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(defend, 0.09f)), changestate, NULL));
	}
}

void Games::playerdefend2(){
	auto changestate1 = CallFunc::create([&]() {
		defend2->removeFromParent();
		defend2 = NULL;
	});

	if (defend2 == NULL) {
		defend2 = Sprite::create();
		defend2->setAnchorPoint(Vec2(0.5, 0.5));
		defend2->setPosition(player[1]->getCharaSpr()->getPosition());
		defend2->setTag(8);

		addChild(defend2, 3);
		Size m(player[1]->getCharaSpr()->getContentSize().width * 2, player[1]->getCharaSpr()->getContentSize().height);
		auto defend2Body = PhysicsBody::createBox(player[1]->getCharaSpr()->getContentSize()*1.5, PhysicsMaterial(0.0f, 0.0f, 0.0f));
		defend2Body->setDynamic(false);
		defend2Body->setPositionOffset(Vec2(100, 100));
		defend2Body->setCategoryBitmask(0x10000);
		defend2Body->setCollisionBitmask(0x10000);
		defend2Body->setContactTestBitmask(0x10000);
		defend2->setPhysicsBody(defend2Body);

		defend2->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(defend, 0.09f)), changestate1, NULL));
	}
}

void Games::playermagic1(){
	if (magic1 == NULL) {
		magic1 = Sprite::create("image 3.png");
		auto ballbody = PhysicsBody::createCircle(magic1->getContentSize().width / 2, PhysicsMaterial(1.0f, 0.0f, 0.0f));
		ballbody->setContactTestBitmask(0x11111);
		magic1->setPhysicsBody(ballbody);
		magic1->setTag(9);
		magic1->setPosition(player[1]->getCharaSpr()->getPositionX(), visibleSize.height - magic1->getContentSize().height);
		addChild(magic1, 3);
	}
}

void Games::playermagic2(){
	if (magic2 == NULL) {
		magic2 = Sprite::create("image 3.png");
		auto ballbody = PhysicsBody::createCircle(magic2->getContentSize().width / 2, PhysicsMaterial(1.0f, 0.0f, 0.0f));
		ballbody->setContactTestBitmask(0x11111);
		magic2->setPhysicsBody(ballbody);
		magic2->setTag(10);
		magic2->setPosition(player[0]->getCharaSpr()->getPositionX(), visibleSize.height - magic2->getContentSize().height);
		addChild(magic2, 3);
	}

}

void Games::damage(float damage, int player)
{
	if (player == 0) {
		float tmpdamage = damage;
		float preBlood = hp1->getPercentage();
		if (hp1->getPercentage() + damage < 0) {
			tmpdamage = -hp1->getPercentage();
		}
		else if (hp1->getPercentage() + damage > 100) {
			tmpdamage = 100 - hp1->getPercentage();
		}
		auto updateHP = ProgressTo::create(0.5, (hp1->getPercentage() + tmpdamage));
		hp1->runAction(updateHP);

	}
	else if (player == 1){
		if (hp2->getPercentage() + damage < 0) {
			damage = -hp2->getPercentage();
		}
		else if (hp2->getPercentage() + damage > 100) {
			damage = 100 - hp2->getPercentage();
		}
		auto updateHP = ProgressTo::create(0.5, (hp2->getPercentage() + damage));
		hp2->runAction(updateHP);
	}


}

void Games::win(){
	if (hp1->getPercentage() <= 0) {
		winFrame();
		//Director::getInstance()->replaceScene(End::createScene());
	}
	else if (hp2->getPercentage() <= 0) {
		winFrame();
		//Director::getInstance()->replaceScene(End::createScene());
	}
}

void Games::winFrame()
{
	if (winJ == true)
	{
		Sprite* a = Sprite::create("black7.png");
		a->setPosition(480, 320);
		addChild(a, 5);
		Sprite* b = Sprite::create("guang.png");
		b->setPosition(1440, 270);
		addChild(b, 6);
		CCMoveTo* bm = CCMoveTo::create(0.3f, ccp(480, 270));
		b->runAction(bm);
		if (hp2->getPercentage()) {
			Sprite* c = Sprite::create("2p.png");
			c->setPosition(-480, 270);
			addChild(c, 7);
			CCMoveTo* cm = CCMoveTo::create(0.3f, ccp(480, 270));
			c->runAction(cm);
		}
		else {
			Sprite* c = Sprite::create("1p.png");
			c->setPosition(-480, 270);
			addChild(c, 7);
			CCMoveTo* cm = CCMoveTo::create(0.3f, ccp(480, 270));
			c->runAction(cm);
		}
		winJ = false;

		MenuItemImage* label0 = MenuItemImage::create("Return.png", "Return.png");
		auto menuItem = MenuItemLabel::create(label0);
		auto menu = Menu::create(menuItem, nullptr);
		menuItem->setCallback([&](cocos2d::Ref *sender) {
			auto scene = HelloWorld::createScene();
			HelloWorld* temp = HelloWorld::create();
			temp->isBgm = isBgm;
			scene->addChild(temp);
			Director::getInstance()->replaceScene(scene);
		});
		menu->setPosition(Vec2::ZERO);
		menuItem->setScale(0.15);
		menuItem->setAnchorPoint(Vec2(0, 1));
		menuItem->setPosition(visibleSize.width / 2-90,200);
		addChild(menu, 6);
	}
	
}