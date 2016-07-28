#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "EndScene.h"
#include <math.h>

using namespace CocosDenshion;



USING_NS_CC;

Scene* Games::createScene()
{
	//auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Point(0, -800));
	//scene->getPhysicsWorld()->setAutoStep(false);

	auto layer = Games::create();

	scene->addChild(layer);

	return scene;
}

bool Games::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = Sprite::create("Background_1.png");
	background->setScale(1.1);
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
	addEdge();



	preloadMusic();
	////playBgm();


	addListener();
	//addHpBar();

	bullet1 = NULL;
	bullet2 = NULL;
	defend1 = NULL;
	defend2 = NULL;



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


	scheduleUpdate();






	return true;
}

void Games::initPlayers(){
	player[0] = new Boy();
	player[1] = new Boy();

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
	Sprite* sp1 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* sp2 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* sp = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(610, 362, 4, 16)));

	//血条1
	hp1 = ProgressTimer::create(sp);
	hp1->setScaleX(90);
	hp1->setAnchorPoint(Vec2(0, 0));
	hp1->setType(ProgressTimerType::BAR);
	hp1->setBarChangeRate(Point(1, 0));
	hp1->setMidpoint(Point(0, 1));
	hp1->setPercentage(100);
	hp1->setPosition(Vec2(origin.x + 14 * hp1->getContentSize().width, origin.y + visibleSize.height - 2 * hp1->getContentSize().height));
	addChild(hp1, 4);
	sp1->setAnchorPoint(Vec2(0, 0));
	sp1->setPosition(Vec2(origin.x + hp1->getContentSize().width, origin.y + visibleSize.height - sp1->getContentSize().height));
	addChild(sp1, 3);

	//血条2
	hp2 = ProgressTimer::create(sp);
	hp2->setScaleX(90);
	hp2->setAnchorPoint(Vec2(0, 0));
	hp2->setType(ProgressTimerType::BAR);
	hp2->setBarChangeRate(Point(1, 0));
	hp2->setMidpoint(Point(1, 0));
	hp2->setPercentage(100);
	hp2->setPosition(Vec2(origin.x + visibleSize.width / 2 + 21 * hp2->getContentSize().width, origin.y + visibleSize.height - 2 * hp2->getContentSize().height));
	addChild(hp2, 4);
	sp2->setAnchorPoint(Vec2(0, 0));
	sp2->setPosition(Vec2(origin.x + visibleSize.width / 2 + 18 * hp2->getContentSize().width + 1.5, origin.y + visibleSize.height - sp2->getContentSize().height));
	addChild(sp2, 3);
	sp2->setFlipX(true);
}


void Games::preloadMusic() {
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("shoot.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("move.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("shout.mp3");
}

void Games::playBgm() {
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3", true);
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

	auto changestate = CallFunc::create([&]() {
		defend1->removeFromParent();
		defend1 = NULL;
	});

	auto changestate1 = CallFunc::create([&]() {
		defend2->removeFromParent();
		defend2 = NULL;
	});

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

	case cocos2d::EventKeyboard::KeyCode::KEY_J:
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
		//playerdefend1();
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_Y:
		damage(10, 0);
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_U:
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

	case cocos2d::EventKeyboard::KeyCode::KEY_L:
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
	case cocos2d::EventKeyboard::KeyCode::KEY_K:
		//playerdefend2();
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_I:
		damage(10, 1);
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_O:
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

	static float defend1time = 0;
	static float defend2time = 0;

	/*for (int i = 0; i < 3; ++i)
	{
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->step(1 / 180.0f);
	}*/

	if (isKeyPressed(EventKeyboard::KeyCode::KEY_A) && (!isKeyPressed(EventKeyboard::KeyCode::KEY_D))) {
		player[0]->getCharaSpr()->setFlipX(true);
		player[0]->setIsRight(false);
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_D) && (!isKeyPressed(EventKeyboard::KeyCode::KEY_A))) {
		player[0]->getCharaSpr()->setFlipX(false);
		player[0]->setIsRight(true);
	}
	if (defend1 != NULL){

		defend1->setPosition(player[0]->getCharaSpr()->getPosition());

		/*if (player[0]->getIsRight()) {
		defend1->setPosition(Vec2(player[0]->getCharaSpr()->getPosition().x + player[0]->getCharaSpr()->getContentSize().width / 2 + defend1->getContentSize().width / 2, player[0]->getCharaSpr()->getPosition().y));
		}
		else {
		defend1->setPosition(Vec2(player[0]->getCharaSpr()->getPosition().x - player[0]->getCharaSpr()->getContentSize().width / 2 - defend1->getContentSize().width / 2, player[0]->getCharaSpr()->getPosition().y));
		}*/
		//defend1time += dt;
		//if (defend1time > 2) {
		//	defend1time = 0;
		//	defend1->removeFromParent();
		//	defend1 = NULL;	
		//}
	}


	if (defend2 != NULL){
		defend2->setPosition(player[1]->getCharaSpr()->getPosition());
		/*if (player[1]->getIsRight()) {
		defend2->setPosition(Vec2(player[1]->getCharaSpr()->getPosition().x + player[1]->getCharaSpr()->getContentSize().width / 2 + defend2->getContentSize().width / 2, player[1]->getCharaSpr()->getPosition().y));
		}
		else {
		defend2->setPosition(Vec2(player[1]->getCharaSpr()->getPosition().x - player[1]->getCharaSpr()->getContentSize().width / 2 - defend2->getContentSize().width / 2, player[1]->getCharaSpr()->getPosition().y));
		}
		defend2time += dt;
		if (defend2time > 2) {
		defend2time = 0;
		defend2->removeFromParent();
		defend2 = NULL;
		}*/
	}





	if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) && (!isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW))) {
		player[1]->getCharaSpr()->setFlipX(true);
		player[1]->setIsRight(false);
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) && (!isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW))) {
		player[1]->getCharaSpr()->setFlipX(false);
		player[1]->setIsRight(true);
	}


	if (player[0]->getCharaSpr()->getPositionY() < origin.y){
		player[0]->getCharaSpr()->setPosition(player[0]->getCharaSpr()->getPositionX(), visibleSize.height - player[0]->getCharaSpr()->getContentSize().height / 2);
	}
	if (player[1]->getCharaSpr()->getPositionY() < origin.y){
		player[1]->getCharaSpr()->setPosition(player[1]->getCharaSpr()->getPositionX(), visibleSize.height - player[1]->getCharaSpr()->getContentSize().height / 2);
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
	*/

	auto walkAnimate0 = Animate::create(Animation::createWithSpriteFrames(player[0]->getWalkFrame(), 0.05f));
	auto walkAnimate1 = Animate::create(Animation::createWithSpriteFrames(player[1]->getWalkFrame(), 0.05f));
	auto deadAnimate0 = Animate::create(Animation::createWithSpriteFrames(player[0]->getDeadFrame(), 0.1f));
	auto deadAnimate1 = Animate::create(Animation::createWithSpriteFrames(player[1]->getDeadFrame(), 0.1f));

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

			bulletBoom1 = Sprite::create();
			bulletBoom1->setPosition(loc);
			addChild(bulletBoom1, 3);

			auto changestate = CallFunc::create([&]() {
				bulletBoom1->removeFromParent();
				bulletBoom1 = NULL;
			});

			bulletBoom1->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(boom, 0.09f)), changestate, NULL));


			bullet2->removeFromParent();
			bullet2 = NULL;
			if (tagA == 0 || tagB == 0) {
				SimpleAudioEngine::sharedEngine()->playEffect("shout.mp3");
				damage(-20, 0);
			}
			else {

			}
		}
	}



	if (tagA == 4 || tagB == 4) {
		if (bullet1 != NULL){
			Vec2 loc = bullet1->getPosition();
			bulletBoom2 = Sprite::create();
			bulletBoom2->setPosition(loc);
			addChild(bulletBoom2, 3);

			auto changestate = CallFunc::create([&]() {
				bulletBoom2->removeFromParent();
				bulletBoom2 = NULL;
			});

			bulletBoom2->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(boom, 0.09f)), changestate, NULL));
			bullet1->removeFromParent();
			bullet1 = NULL;
			if (tagA == 1 || tagB == 1) {
				SimpleAudioEngine::sharedEngine()->playEffect("shout.mp3");
				damage(-20, 1);
			}
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
		bullet1 = Sprite::create("Ball.png");
		bullet1->setTag(4);
		if (player[0]->getIsRight()) {
			bullet1->setPosition(Vec2(player[0]->getCharaSpr()->getPosition().x + player[0]->getCharaSpr()->getContentSize().width / 2 + bullet1->getContentSize().width / 2, player[0]->getCharaSpr()->getPosition().y));
		}
		else {
			bullet1->setPosition(Vec2(player[0]->getCharaSpr()->getPosition().x - player[0]->getCharaSpr()->getContentSize().width / 2 - bullet1->getContentSize().width / 2, player[0]->getCharaSpr()->getPosition().y));
		}
		addChild(bullet1, 2);
		bullet1->setPhysicsBody(PhysicsBody::createCircle(bullet1->getContentSize().width / 2, PhysicsMaterial(0.0f, 0.0f, 0.0f)));
		bullet1->getPhysicsBody()->setVelocity(Vec2(x, y));
		bullet1->getPhysicsBody()->setCategoryBitmask(0x10110);
		bullet1->getPhysicsBody()->setCollisionBitmask(0x10110);
		bullet1->getPhysicsBody()->setContactTestBitmask(0x10110);
		bullet1->getPhysicsBody()->setGravityEnable(false);
	}
}

void Games::bullet2fire(float x, float y){


	if (bullet2 == NULL) {
		bullet2 = Sprite::create("Ball.png");
		bullet2->setTag(5);
		if (player[1]->getIsRight()) {
			bullet2->setPosition(Vec2(player[1]->getCharaSpr()->getPosition().x + player[1]->getCharaSpr()->getContentSize().width / 2 + bullet2->getContentSize().width / 2, player[1]->getCharaSpr()->getPosition().y));
		}
		else {
			bullet2->setPosition(Vec2(player[1]->getCharaSpr()->getPosition().x - player[1]->getCharaSpr()->getContentSize().width / 2 - bullet2->getContentSize().width / 2, player[1]->getCharaSpr()->getPosition().y));
		}
		addChild(bullet2, 2);
		bullet2->setPhysicsBody(PhysicsBody::createCircle(bullet2->getContentSize().width / 2, PhysicsMaterial(0.0f, 0.0f, 0.0f)));
		bullet2->getPhysicsBody()->setVelocity(Vec2(x, y));
		bullet2->getPhysicsBody()->setContactTestBitmask(0x01101);
		bullet2->getPhysicsBody()->setContactTestBitmask(0x01101);
		bullet2->getPhysicsBody()->setContactTestBitmask(0x01101);
		bullet2->getPhysicsBody()->setGravityEnable(false);
	}
}

void Games::playerdefend1(){
	if (defend1 == NULL){
		defend1 = Sprite::create("defend.png");
		defend1->setScaleX(0.2);
		defend1->setScaleY(0.05);
		defend1->setTag(8);
		if (player[0]->getIsRight()) {
			defend1->setPosition(Vec2(player[0]->getCharaSpr()->getPosition().x + player[0]->getCharaSpr()->getContentSize().width / 2 + defend1->getContentSize().width / 2, player[0]->getCharaSpr()->getPosition().y));
		}
		else {
			defend1->setPosition(Vec2(player[0]->getCharaSpr()->getPosition().x - player[0]->getCharaSpr()->getContentSize().width / 2 - defend1->getContentSize().width / 2, player[0]->getCharaSpr()->getPosition().y));
		}
		addChild(defend1, 2);
		defend1->setPhysicsBody(PhysicsBody::createBox(defend1->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f)));
		defend1->getPhysicsBody()->setDynamic(false);
		defend1->getPhysicsBody()->setCategoryBitmask(0x01000);
		defend1->getPhysicsBody()->setCollisionBitmask(0x01000);
		defend1->getPhysicsBody()->setContactTestBitmask(0x01000);
	}
}

void Games::playerdefend2(){
	if (defend2 == NULL){
		defend2 = Sprite::create("defend.png");
		defend2->setScaleX(0.2);
		defend2->setScaleY(0.05);
		defend2->setTag(8);
		if (player[1]->getIsRight()) {
			defend2->setPosition(Vec2(player[1]->getCharaSpr()->getPosition().x + player[1]->getCharaSpr()->getContentSize().width / 2 + defend2->getContentSize().width / 2, player[1]->getCharaSpr()->getPosition().y));
		}
		else {
			defend2->setPosition(Vec2(player[1]->getCharaSpr()->getPosition().x - player[1]->getCharaSpr()->getContentSize().width / 2 - defend2->getContentSize().width / 2, player[1]->getCharaSpr()->getPosition().y));
		}
		addChild(defend2, 2);
		defend2->setPhysicsBody(PhysicsBody::createBox(defend2->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f)));
		defend2->getPhysicsBody()->setDynamic(false);
		defend2->getPhysicsBody()->setCategoryBitmask(0x10000);
		defend2->getPhysicsBody()->setCollisionBitmask(0x10000);
		defend2->getPhysicsBody()->setContactTestBitmask(0x10000);
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
		Director::getInstance()->replaceScene(End::createScene());
	}
	else if (hp2->getPercentage() <= 0) {
		Director::getInstance()->replaceScene(End::createScene());
	}
}