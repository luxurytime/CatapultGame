#include "StoryGameScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "EndScene.h"
#include "Character.h"
#include <math.h>

using namespace CocosDenshion;


static int ppp1;
static bool isBgmp;

USING_NS_CC;

Scene* StoryGame::createScene(int p1, bool b)
{
	ppp1 = p1;
	isBgmp = b;
	// 'scene' is an autorelease object
	//auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Point(0, -800));

	// 'layer' is an autorelease object
	auto layer = StoryGame::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool StoryGame::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	pp1 = ppp1;
	isBgm = isBgmp;

	winJ = true;

	label = Label::createWithTTF("BulletNumber = 5", "fonts/STHUPO.ttf", 24);
	label->setPosition((Vec2(origin.x + label->getContentSize().width / 2, origin.y + visibleSize.height - label->getContentSize().height - 50)));
	this->addChild(label, 5);

	bullet1 = NULL;
	bullet2 = NULL;
	bullet3 = NULL;
	bullet4 = NULL;
	bullet5 = NULL;
	bulletNum = 5;
	//addplayer
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



	addPlayer(origin.x + visibleSize.width / 4, 0);
	player[0]->getCharaSpr()->setTag(0);

	preloadMusic();
	playBgm();

	addmap();
	addHpBar();
	addEnemy();
	addListener();
	addEdge();
	scheduleUpdate();

	return true;
}
void StoryGame::addmap() {
	//map = cocos2d::experimental::TMXTiledMap::create("storymap.tmx");
	map = TMXTiledMap::create("res/storymap.tmx");
	//layer = map->layerNamed("enemy1");
	//CCLOG("%d", layer->tileGIDAt(ccp(9, 5)));
	map->setScale(0.58);
	map->setPhysicsBody(PhysicsBody::createEdgeBox(map->getContentSize()));
	addChild(map, 1);

	////´ÓTMXÖÐ»ñÈ¡enemy1¶ÔÏó²ã
	//TMXObjectGroup* enemy1Objects = map->getObjectGroup("enemy1");
	//ValueVector enemy1Container = enemy1Objects->getObjects();
	//for (auto obj3 : enemy1Container) {
	//	ValueMap values3 = obj3.asValueMap();
	//	int x3 = values3.at("x").asInt() ;
	//	int y3 = values3.at("y").asInt() + 200 ;
	//	enemy1 = Sprite::create("res/enemy1.png");

	//	enemy1->setPosition(x3, y3);
	//	enemy1->setPhysicsBody(PhysicsBody::createBox(enemy1->getContentSize()));
	//	enemy1->getPhysicsBody()->setDynamic(false);
	//	enemy1->getPhysicsBody()->setContactTestBitmask(1);
	//	enemy1->setTag(9);
	//	enemy1->setVisible(true);
	//	ActionInterval * move = MoveBy::create(1, ccp(-200, 0));
	//	ActionInterval * move1 = MoveBy::create(1, ccp(200,0));  
	//	FiniteTimeAction* seq = Sequence::create(move,move1,NULL);  
	//	ActionInterval * repeatForever =RepeatForever::create((ActionInterval* )seq);  
	//	enemy1->runAction(repeatForever); 

	//	enemy1container.pushBack(enemy1);
	//	map->addChild(enemy1, 1);
	//	//CCLOG("enemy1%d",enemy1->);
	//}

	//´ÓTMXÖÐ»ñÈ¡ground¶ÔÏó²ã
	TMXObjectGroup* groundObjects = map->getObjectGroup("ground");
	ValueVector groundContainer = groundObjects->getObjects();

	for (auto obj1 : groundContainer) {
		ValueMap values1 = obj1.asValueMap();
		int x1 = values1.at("x").asInt() + 48;
		int y1 = values1.at("y").asInt() + 145;
		brick = Sprite::create("res/brick.png");
		brick->setPosition(x1, y1);
		//player[t]->getCharaSpr()->setPhysicsBody(PhysicsBody::createBox(player[t]->getCharaSpr()->getContentSize()));
		brick->setPhysicsBody(PhysicsBody::createBox(brick->getContentSize()));
		brick->getPhysicsBody()->setDynamic(false);
		brick->getPhysicsBody()->setContactTestBitmask(1);
		brickcontainer.pushBack(brick);
		brick->setTag(10);
		CCLOG("%d", brick->getTag());
		map->addChild(brick, 1);
	}
	//´ÓTMXÖÐ»ñÈ¡pipe¶ÔÏó²ã
	TMXObjectGroup* pipeObjects = map->getObjectGroup("pipe");
	ValueVector pipeContainer = pipeObjects->getObjects();
	for (auto obj2 : pipeContainer) {
		ValueMap values2 = obj2.asValueMap();
		int x2 = values2.at("x").asInt() + 48;
		int y2 = values2.at("y").asInt() + 270;
		pipe = Sprite::create("res/pipe.png");
		pipe->setPosition(x2, y2);

		//player[t]->getCharaSpr()->setPhysicsBody(PhysicsBody::createBox(player[t]->getCharaSpr()->getContentSize()));
		pipe->setPhysicsBody(PhysicsBody::createBox(pipe->getContentSize()));
		pipe->getPhysicsBody()->setDynamic(false);
		pipe->getPhysicsBody()->setContactTestBitmask(1);
		pipe->setTag(10);
		pipecontainer.pushBack(pipe);
		map->addChild(pipe, 1);
	}

}

void StoryGame::addEnemy() {


	enemy1 = Sprite::create("res/enemy1.png");
	enemy1->setPosition(900, 450);
	enemy1->setPhysicsBody(PhysicsBody::createBox(enemy1->getContentSize()));
	enemy1->getPhysicsBody()->setDynamic(false);
	enemy1->getPhysicsBody()->setContactTestBitmask(1);
	enemy1->setTag(9);
	enemy1->setVisible(true);
	ActionInterval * move = MoveBy::create(1, ccp(-200, 0));
	ActionInterval * move1 = MoveBy::create(1, ccp(200, 0));
	FiniteTimeAction* seq = Sequence::create(move, move1, NULL);
	ActionInterval * repeatForever = RepeatForever::create((ActionInterval*)seq);
	enemy1->runAction(repeatForever);
	map->addChild(enemy1, 1);

	enemy2 = Sprite::create("res/enemy2.png");
	enemy2->setPosition(1900, 800);
	enemy2->setPhysicsBody(PhysicsBody::createBox(enemy2->getContentSize()));
	enemy2->getPhysicsBody()->setDynamic(false);
	enemy2->getPhysicsBody()->setContactTestBitmask(1);
	enemy2->setTag(8);
	enemy2->setVisible(true);
	ActionInterval * move2 = MoveBy::create(1, ccp(-200, 0));
	ActionInterval * move12 = MoveBy::create(1, ccp(200, 0));
	FiniteTimeAction* seq2 = Sequence::create(move2, move12, NULL);
	ActionInterval * repeatForever2 = RepeatForever::create((ActionInterval*)seq2);
	enemy2->runAction(repeatForever2);
	map->addChild(enemy2, 1);

	enemy3 = Sprite::create("res/enemy3.png");
	enemy3->setPosition(3500, 150);
	enemy3->setPhysicsBody(PhysicsBody::createBox(enemy3->getContentSize()));
	enemy3->getPhysicsBody()->setDynamic(false);
	enemy3->getPhysicsBody()->setContactTestBitmask(1);
	enemy3->setTag(7);
	enemy3->setVisible(true);
	ActionInterval * move3 = MoveBy::create(1, ccp(-1000, 0));
	ActionInterval * move13 = MoveBy::create(1, ccp(1000, 0));
	FiniteTimeAction* seq3 = Sequence::create(move3, move13, NULL);
	ActionInterval * repeatForever3 = RepeatForever::create((ActionInterval*)seq3);
	enemy3->runAction(repeatForever3);
	map->addChild(enemy3, 1);

	enemy4 = Sprite::create("res/enemy4.png");
	enemy4->setPosition(4700, 800);
	enemy4->setPhysicsBody(PhysicsBody::createBox(enemy4->getContentSize()));
	enemy4->getPhysicsBody()->setDynamic(false);
	enemy4->getPhysicsBody()->setContactTestBitmask(1);
	enemy4->setTag(6);
	enemy4->setVisible(true);
	ActionInterval * move4 = MoveBy::create(1, ccp(-500, 0));
	ActionInterval * move14 = MoveBy::create(1, ccp(500, 0));
	FiniteTimeAction* seq4 = Sequence::create(move4, move14, NULL);
	ActionInterval * repeatForever4 = RepeatForever::create((ActionInterval*)seq4);
	enemy4->runAction(repeatForever4);
	map->addChild(enemy4, 1);

	enemy5 = Sprite::create("res/enemy.png");
	enemy5->setPosition(7000, 800);
	enemy5->setPhysicsBody(PhysicsBody::createBox(enemy5->getContentSize()));
	enemy5->getPhysicsBody()->setDynamic(false);
	enemy5->getPhysicsBody()->setContactTestBitmask(1);
	enemy5->setTag(5);
	enemy5->setVisible(true);
	ActionInterval * move5 = MoveBy::create(1, ccp(0, -300));
	ActionInterval * move15 = MoveBy::create(1, ccp(0, 300));
	FiniteTimeAction* seq5 = Sequence::create(move5, move15, NULL);
	ActionInterval * repeatForever5 = RepeatForever::create((ActionInterval*)seq5);
	enemy5->runAction(repeatForever5);
	map->addChild(enemy5, 1);


	enemy6 = Sprite::create("res/boss.png");
	enemy6->setScale(-1, 1);
	enemy6->setPosition(10000, 150);
	enemy6->setPhysicsBody(PhysicsBody::createBox(enemy6->getContentSize()));
	enemy6->getPhysicsBody()->setDynamic(false);
	enemy6->getPhysicsBody()->setContactTestBitmask(1);
	enemy6->setTag(3);
	enemy6->setVisible(true);
	ActionInterval * move6 = MoveBy::create(2, ccp(0, 400));
	ActionInterval * actionmoveback = move6->reverse();
	FiniteTimeAction* seq6 = Sequence::create(move6, actionmoveback, NULL);
	ActionInterval * repeatForever6 = RepeatForever::create((ActionInterval*)seq6);
	enemy6->runAction(repeatForever6);
	map->addChild(enemy6, 1);
}

void StoryGame::addEdge(){
	auto edge = Sprite::create();
	edge->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.0f, 0.0f, 0.5f), 5.0f);
	edgeBody->setDynamic(false);
	edgeBody->setCategoryBitmask(0x0011);
	edgeBody->setCollisionBitmask(0x0011);
	edgeBody->setContactTestBitmask(0x0100);
	edge->setPhysicsBody(edgeBody);
	edge->setTag(100);
	addChild(edge, 1);
}

void StoryGame::addHpBar(){
	sp1 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	sp2 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* sp = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(610, 362, 4, 16)));

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

	//ÑªÌõ2
	hp2 = ProgressTimer::create(sp);
	hp2->setScaleX(90);
	hp2->setAnchorPoint(Vec2(0, 0));
	hp2->setType(ProgressTimerType::BAR);
	hp2->setBarChangeRate(Point(1, 0));
	hp2->setMidpoint(Point(1, 0));
	hp2->setPercentage(100);
	hp2->setVisible(false);
	hp2->setPosition(Vec2(origin.x + visibleSize.width / 2 + 21 * hp2->getContentSize().width, origin.y + visibleSize.height - 2 * hp2->getContentSize().height));
	addChild(hp2, 4);
	sp2->setAnchorPoint(Vec2(0, 0));
	sp2->setVisible(false);
	sp2->setPosition(Vec2(origin.x + visibleSize.width / 2 + 18 * hp2->getContentSize().width + 1.5, origin.y + visibleSize.height - sp2->getContentSize().height));
	addChild(sp2, 3);
	sp2->setFlipX(true);
}

void StoryGame::preloadMusic() {
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm1.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("shoot.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("move.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("shout.mp3");
}

void StoryGame::playBgm() {
	if (isBgm)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm1.mp3", true);
	}
}

Sprite* StoryGame::addPlayer(int x, int t)
{
	player[t]->getCharaSpr()->setScale(1.0, 1.0);
	player[t]->getCharaSpr()->setPosition(Vec2(x, origin.y + player[t]->getCharaSpr()->getContentSize().height / 2 + altitude));
	player[t]->getCharaSpr()->setPhysicsBody(PhysicsBody::createBox(player[t]->getCharaSpr()->getContentSize(), PhysicsMaterial(0.1f, 0.1, 0.0f)));
	player[t]->getCharaSpr()->getPhysicsBody()->setContactTestBitmask(1);
	player[t]->getCharaSpr()->getPhysicsBody()->setDynamic(true);
	player[t]->getCharaSpr()->getPhysicsBody()->setRotationEnable(false);
	addChild(player[t]->getCharaSpr(), 3);

	return player[t]->getCharaSpr();
}

//void StoryGame::addEnemy() {
//	enemy = Sprite::create("enemy1.png");
//	enemy->setScale(0.5);
//	enemy->setPosition(440, 400);
//	addChild(enemy, 2);
//
//}

void StoryGame::addListener()
{

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(StoryGame::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(StoryGame::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);


	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(StoryGame::onConcactBegan, this);
	_eventDispatcher->addEventListenerWithFixedPriority(contactListener, 1);

}


void StoryGame::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

	keys[keyCode] = true;

	auto animation = Animation::createWithSpriteFrames(player[0]->getWalkFrame(), 0.05f);
	auto animate = Animate::create(animation);
	MoveBy* move;
	MoveBy* move2;
	int movedis = 20;
	switch (keyCode)
	{

	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		SimpleAudioEngine::getInstance()->playEffect("move.mp3");
		move = MoveBy::create(0.4, Point(30, 0));
		move2 = MoveBy::create(0.4, Point(-30, 0));

		if (player[0]->getJumpNum() == 0) {
			player[0]->getCharaSpr()->runAction(animate);
		}


		player[0]->getCharaSpr()->runAction(MoveBy::create(0.4, Point(-30, 0)));

		this->schedule(schedule_selector(StoryGame::moveContine), 0.3f);
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		SimpleAudioEngine::getInstance()->playEffect("move.mp3");
		move = MoveBy::create(0.4, Point(-30, 0));
		if (player[0]->getJumpNum() == 0) {
			player[0]->getCharaSpr()->runAction(animate);
		}

		if (player[0]->getCharaSpr()->getPositionX() < 240) {
			player[0]->getCharaSpr()->runAction(MoveBy::create(0.4, Point(30, 0)));
		}
		else if (map->getPositionX() >= -4500) {
			map->runAction(MoveBy::create(0.4, Point(-30, 0)));
			//enemy->runAction(MoveBy::create(0.4, Point(-30, 0)));
		}
		else {
			player[0]->getCharaSpr()->runAction(MoveBy::create(0.4, Point(30, 0)));
		}

		this->schedule(schedule_selector(StoryGame::moveContine), 0.3f);
		break;

		//case cocos2d::EventKeyboard::KeyCode::KEY_W:
		//	move = MoveBy::create(0.4, Point(0, 200));
		//	player[0]->getCharaSpr()->runAction(move);
		//	this->schedule(schedule_selector(StoryGame::moveContine), 0.3f);

		//	break;

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
		if (bulletNum != 0 && bullet1 == NULL){
			SimpleAudioEngine::sharedEngine()->playEffect("shoot.mp3");
			if (player[0]->getJumpNum() == 0) {
				if (player[0]->getIsRight()) {
					bulletfire(1000, 0);
				}
				else {
					bulletfire(-1000, 0);
				}
			}
			else {
				if (player[0]->getIsRight()) {
					bulletfire(1000, -1000);
				}
				else {
					bulletfire(-1000, -1000);
				}
			}
		}
		//CCLOG("(%f,%f,%f,%f,%f,%f)", player[0]->getCharaSpr()->getPositionX(),enemy1->getPositionX(), enemy2->getPositionX(), enemy3->getPositionX(), enemy4->getPositionX(), enemy5->getPositionX());
		//CCLOG("(%f", map->getPositionX());
		break;
	case EventKeyboard::KeyCode::KEY_K:
		bulletNum = 5;
		break;
	case EventKeyboard::KeyCode::KEY_L:
		if (bulletNum == 5) {
			bulletNum = 0;
			damage(5, 0);
		}
		break;
	default:
		break;
	}
}

bool StoryGame::isKeyPressed(EventKeyboard::KeyCode keyCode)
{
	if (keys[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}

void StoryGame::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	keys[keyCode] = false;

	if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		this->unschedule(schedule_selector(StoryGame::moveContine));
	}
}


void StoryGame::onKeyPressedContinue(EventKeyboard::KeyCode keyCode)
{
	int offsetX = 0, offsetY = 0;
	int offsetX2 = 0, offsetY2 = 0;

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_A:
		offsetX = 20;

		player[0]->getCharaSpr()->runAction(MoveBy::create(0.4, Point(-30, 0)));

		break;
	case EventKeyboard::KeyCode::KEY_D:
		offsetX = -20;
		if (player[0]->getCharaSpr()->getPositionX() <= 240) {
			player[0]->getCharaSpr()->runAction(MoveBy::create(0.4, Point(30, 0)));
		}
		else if (map->getPositionX() >= -4500) {
			map->runAction(MoveBy::create(0.4, Point(-30, 0)));
			//enemy->runAction(MoveBy::create(0.4, Point(-30, 0)));
		}
		else {
			player[0]->getCharaSpr()->runAction(MoveBy::create(0.4, Point(30, 0)));
		}
		break;

	default:
		offsetY = offsetX = 0;
		offsetX2 = offsetY2 = 0;
		break;
	}
	auto animate = Animate::create(Animation::createWithSpriteFrames(player[0]->getWalkFrame(), 0.04f));

	if (player[0]->getJumpNum() == 0) {
		player[0]->getCharaSpr()->runAction(animate);
	}
}



void StoryGame::moveContine(float dt)
{
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_A)) {
		onKeyPressedContinue(EventKeyboard::KeyCode::KEY_A);
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_D)) {
		onKeyPressedContinue(EventKeyboard::KeyCode::KEY_D);
	}
}




bool StoryGame::onConcactBegan(PhysicsContact& contact) {
	Sprite* spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	Sprite* spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();
	if (spriteA == NULL || spriteB == NULL) return false;
	int tagA = spriteA->getTag();
	int tagB = spriteB->getTag();

	auto animate = Animate::create(Animation::createWithSpriteFrames(player[0]->getDeadFrame(), 0.1f));


	if ((tagA == 0 && tagB == 10) || (tagB == 0 && tagA == 10)) {
		player[0]->setJumpNum(0);
	}
	//if ((tagA == 0 && tagB == 2) || (tagA == 2 && tagB == 0)) {
	//	damage(-1, 0);
	//	bullet1->removeFromParent();
	//	bullet1 = NULL;
	//}


	if ((tagA == 10 && tagB == 2) || (tagA == 2 && tagB == 10)) {
		bullet1->removeFromParent();
		bullet1 = NULL;
		CCLOG("success");
	}
	if ((tagA == 10 && tagB == 4) || (tagA == 4 && tagB == 10)) {
		bullet2->removeFromParent();
		bullet2 = NULL;

		CCLOG("success");
	}
	if ((tagA == 0 && tagB == 4) || (tagA == 4 && tagB == 0)) {
		bullet2->removeFromParent();
		bullet2 = NULL;
		damage(-10, 0);
		CCLOG("success");
	}

	if ((tagA == 10 && tagB == 14) || (tagA == 14 && tagB == 10)) {
		bullet3->removeFromParent();
		bullet3 = NULL;

		CCLOG("success");
	}
	if ((tagA == 0 && tagB == 14) || (tagA == 14 && tagB == 0)) {
		bullet3->removeFromParent();
		bullet3 = NULL;
		damage(-10, 0);
		CCLOG("success");
	}

	if ((tagA == 10 && tagB == 24) || (tagA == 24 && tagB == 10)) {
		bullet4->removeFromParent();
		bullet4 = NULL;

		CCLOG("success");
	}
	if ((tagA == 0 && tagB == 24) || (tagA == 24 && tagB == 0)) {
		bullet4->removeFromParent();
		bullet4 = NULL;
		damage(-10, 0);
		CCLOG("success");
	}
	if ((tagA == 100 && tagB == 11) || (tagA == 11 && tagB == 100)) {
		bullet5->removeFromParent();
		bullet5 = NULL;
		CCLOG("success");
	}
	if ((tagA == 11 && tagB == 2) || (tagA == 2 && tagB == 11)) {
		bullet1->removeFromParent();
		bullet1 = NULL;
		bullet5->removeFromParent();
		bullet5 = NULL;
		CCLOG("success");
	}
	if ((tagA == 100 && tagB == 2) || (tagA == 2 && tagB == 100)) {
		bullet1->removeFromParent();
		bullet1 = NULL;
		CCLOG("success");
	}
	if ((tagA == 9 && tagB == 0) || (tagA == 0 && tagB == 9)) {
		//Blink* blink = Blink::create(1, 4);
		//player[0]->getCharaSpr()->runAction(blink);
		damage(-10, 0);
		CCLOG("success1");
	}
	if ((tagA == 11 && tagB == 0) || (tagA == 0 && tagB == 11)) {
		bullet5->removeFromParent();
		bullet5 = NULL;
		damage(-10, 0);
		CCLOG("success");
	}
	//if ((tagA == 3 && tagB == 2) || (tagA == 2 && tagB == 3)) {
	//	bullet1->removeFromParent();
	//	bullet1 = NULL;
	//	damage(-5, 1);
	//	CCLOG("success");
	//}
	if ((tagA == 9 && tagB == 2) || (tagA == 2 && tagB == 9)) {
		bullet1->removeFromParent();
		bullet1 = NULL;
		enemy1HP--;
		if (enemy1HP == 0) {
			enemy1->removeFromParent();
		}
		CCLOG("success");
	}
	if ((tagA == 8 && tagB == 2) || (tagA == 2 && tagB == 8)) {
		bullet1->removeFromParent();
		bullet1 = NULL;
		enemy2HP--;
		if (enemy2HP == 0) {
			enemy2->removeFromParent();
		}
		CCLOG("success");
	}
	if ((tagA == 7 && tagB == 2) || (tagA == 2 && tagB == 7)) {
		bullet1->removeFromParent();
		bullet1 = NULL;
		enemy3HP--;
		if (enemy3HP == 0) {
			enemy3->removeFromParent();
		}
		CCLOG("success");
	}
	if ((tagA == 7 && tagB == 0) || (tagA == 0 && tagB == 7)) {
		damage(-10, 0);
		CCLOG("success");
	}
	if ((tagA == 6 && tagB == 2) || (tagA == 2 && tagB == 6)) {
		bullet1->removeFromParent();
		bullet1 = NULL;
		enemy4HP--;
		if (enemy4HP == 0) {
			enemy4->removeFromParent();
		}
		CCLOG("success");
	}
	if ((tagA == 5 && tagB == 2) || (tagA == 2 && tagB == 5)) {
		bullet1->removeFromParent();
		bullet1 = NULL;
		enemy5HP--;
		if (enemy5HP == 0) {
			enemy5->removeFromParent();
		}
		CCLOG("success");
	}
	if ((tagA == 3 && tagB == 2) || (tagA == 2 && tagB == 3)) {
		if (bullet1 != NULL) {
			bullet1->removeFromParent();
			bullet1 = NULL;
			damage(-5, 1);
		}
		if (hp2->getPercentage() <= 0) {
			enemy6->removeFromParent();
			enemy6 = NULL;
		}
	}
	return true;
}

void StoryGame::onBack(Ref* ref)
{
	Director::getInstance()->replaceScene(CCTransitionProgressOutIn::create(1.0f, HelloWorld::createScene()));
}


void StoryGame::bulletfire(float x, float y){
	if (bulletNum != 0 && bullet1 == NULL) {
		bulletNum--;

		bullet1 = Sprite::create("Ball.png");
		if (player[0]->getIsRight()) {
			bullet1->setPosition(Vec2(player[0]->getCharaSpr()->getPosition().x + player[0]->getCharaSpr()->getContentSize().width / 2 + bullet1->getContentSize().width / 2, player[0]->getCharaSpr()->getPosition().y));
		}
		else {
			bullet1->setPosition(Vec2(player[0]->getCharaSpr()->getPosition().x - player[0]->getCharaSpr()->getContentSize().width / 2 - bullet1->getContentSize().width / 2, player[0]->getCharaSpr()->getPosition().y));
		}
		addChild(bullet1, 2);
		bullet1->setPhysicsBody(PhysicsBody::createCircle(bullet1->getContentSize().width / 2, PhysicsMaterial(0.0f, 0.0f, 0.0f)));
		bullet1->setTag(2);
		bullet1->getPhysicsBody()->setVelocity(Vec2(x, y));
		//bullet1->getPhysicsBody()->setCategoryBitmask(0x10110);
		//bullet1->getPhysicsBody()->setCollisionBitmask(0x10110);
		bullet1->getPhysicsBody()->setContactTestBitmask(1);

		bullet1->getPhysicsBody()->setGravityEnable(false);
		CCLOG("%d,%d", bullet1->getTag(), pipe->getTag());
	}
}

void StoryGame::damage(int damage, int player)
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

void StoryGame::update(float dt){

	char s[100];
	sprintf(s, "BulletNumber = %d", bulletNum);
	label->setString(s);

	if (isKeyPressed(EventKeyboard::KeyCode::KEY_A) == false &&
		isKeyPressed(EventKeyboard::KeyCode::KEY_D) == false &&
		isKeyPressed(EventKeyboard::KeyCode::KEY_W) == false)
	{
		player[0]->getCharaSpr()->stopAllActions();
		map->stopAllActions();
		//enemy->stopAllActions();
	}

	if (isKeyPressed(EventKeyboard::KeyCode::KEY_A) && (!isKeyPressed(EventKeyboard::KeyCode::KEY_D))) {
		player[0]->getCharaSpr()->setFlipX(true);
		player[0]->setIsRight(false);
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_D) && (!isKeyPressed(EventKeyboard::KeyCode::KEY_A))) {
		player[0]->getCharaSpr()->setFlipX(false);
		player[0]->setIsRight(true);
	}

	if (player[0]->getCharaSpr()->getPositionY() < origin.y){
		player[0]->getCharaSpr()->setPosition(player[0]->getCharaSpr()->getPositionX(), visibleSize.height - player[0]->getCharaSpr()->getContentSize().height / 2);
	}

	//if (map->getPositionX() <= 0 && map->getPositionX() >= -450) {
	//Sprite * bullet3 = Sprite::create("Ball.png");
	//bullet3->setPosition(300,300);
	//addChild(bullet3);
	//bullet2 = Sprite::create("ball.png");
	//bullet2->setScale(0.5);
	//bullet2->setTag(4);
	//bullet2->setPosition(Vec2(0.58* (enemy1->getPosition().x - enemy1->getContentSize().width / 2 - bullet2->getContentSize().width / 2), 0.58*(enemy1->getPosition().y)));
	//addChild(bullet2, 3);
	//bullet2->setPhysicsBody(PhysicsBody::createCircle(bullet2->getContentSize().width / 2));
	//MoveTo* moveto = MoveTo::create(2, Vec2(player[0]->getCharaSpr()->getPositionX(), player[0]->getCharaSpr()->getPositionY()));
	//bullet2->runAction(moveto);
	//bullet2->getPhysicsBody()->setContactTestBitmask(1);
	//bullet2->getPhysicsBody()->setGravityEnable(true);
	//}
	if (bullet2 == NULL && enemy2 != NULL) {
		bullet2 = Sprite::create("ball.png");
		bullet2->setTag(4);
		bullet2->setPosition(enemy2->getPosition());
		map->addChild(bullet2, 3);
		bullet2->setPhysicsBody(PhysicsBody::createCircle(bullet2->getContentSize().width / 2));
		bullet2->getPhysicsBody()->setContactTestBitmask(1);
		MoveTo* moveto = MoveTo::create(1, Vec2(-map->getPositionX() + 1000, 0));
		bullet2->runAction(moveto);
		bullet2->getPhysicsBody()->setGravityEnable(true);
	}
	//if (map->getPositionX() <= -1220 && map->getPositionX() >= -2000) {

	//}
	if (bullet4 == NULL && enemy4 != NULL) {
		bullet4 = Sprite::create("ball.png");
		bullet4->setTag(24);
		bullet4->setPosition(enemy4->getPosition());
		map->addChild(bullet4, 3);
		bullet4->setPhysicsBody(PhysicsBody::createCircle(bullet4->getContentSize().width / 2));
		MoveTo* moveto = MoveTo::create(1, Vec2(-map->getPositionX() + 2000, 0));
		bullet4->runAction(moveto);
		bullet4->getPhysicsBody()->setContactTestBitmask(1);
		bullet4->getPhysicsBody()->setGravityEnable(true);
	}
	if (bullet3 == NULL && enemy5 != NULL) {
		bullet3 = Sprite::create("ball.png");
		bullet3->setTag(14);
		bullet3->setPosition(enemy5->getPosition());
		map->addChild(bullet3, 3);
		bullet3->setPhysicsBody(PhysicsBody::createCircle(bullet3->getContentSize().width / 2));
		MoveTo* moveto = MoveTo::create(1, Vec2(-map->getPositionX() + 3000, 0));
		bullet3->runAction(moveto);
		bullet3->getPhysicsBody()->setContactTestBitmask(1);
		bullet3->getPhysicsBody()->setGravityEnable(true);
	}
	//if (enemy1->getPositionX() - player[0]->getCharaSpr()->getPositionX() <= 646 || bullet2 == NULL) {

	//}
	//if (enemy2->getPositionX() - player[0]->getCharaSpr()->getPositionX() <= 1562) {

	//}
	//if (enemy3->getPositionX() - player[0]->getCharaSpr()->getPositionX() <= 3219) {

	//}
	//if (enemy4->getPositionX() - player[0]->getCharaSpr()->getPositionX() <= 4240) {

	//}
	//if (enemy5->getPositionX() - player[0]->getCharaSpr()->getPositionX() <= 6576) {

	//}

	if (map->getPositionX() <= -5000) {
		hp2->setVisible(true);
		sp2->setVisible(true);
		if (bullet5 == NULL && enemy6 != NULL)  {
			bullet5 = Sprite::create("res/enemy1.png");
			bullet5->setScale(0.8);
			bullet5->setPosition(enemy6->getPosition());
			map->addChild(bullet5, 2);
			bullet5->setPhysicsBody(PhysicsBody::createCircle(bullet5->getContentSize().width / 2, PhysicsMaterial(0.0f, 0.0f, 0.0f)));
			bullet5->setTag(11);
			bullet5->getPhysicsBody()->setVelocity(Vec2(-800, 0));
			//bullet1->getPhysicsBody()->setCategoryBitmask(0x10110);
			//bullet1->getPhysicsBody()->setCollisionBitmask(0x10110);
			bullet5->getPhysicsBody()->setContactTestBitmask(1);

			bullet5->getPhysicsBody()->setGravityEnable(false);
		}
	}


	end();
}
void StoryGame::end() {
	if (hp1->getPercentage() <= 0) {
		winFrame();
		//Director::getInstance()->replaceScene(CCTransitionProgressOutIn::create(1.0f, HelloWorld::createScene()));
	}
	else if (hp2->getPercentage() <= 0) {
		winFrame();
		//Director::getInstance()->replaceScene(CCTransitionProgressOutIn::create(1.0f, HelloWorld::createScene()));
	}

}

void StoryGame::winFrame()
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
		menuItem->setPosition(visibleSize.width / 2 - 90, 200);
		addChild(menu, 6);
	}

}