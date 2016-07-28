#include "StoryGameScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "EndScene.h"
#include <math.h>

using namespace CocosDenshion;




USING_NS_CC;

Scene* StoryGame::createScene()
{
	// 'scene' is an autorelease object
	//auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Point(0, -98));

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

	bullet1 = NULL;
	bullet2 = NULL;

	//addplayer
	player[0] = new Boy();
	addPlayer(origin.x + visibleSize.width / 4, 0);
	player[0]->getCharaSpr()->setTag(1);

	//preloadMusic();
	//playBgm();

	addmap();
	addHpBar();
	addEnemy();
	addListener();

	scheduleUpdate();

	return true;
}
void StoryGame::addmap() {
	//map = cocos2d::experimental::TMXTiledMap::create("storymap.tmx");
	map = TMXTiledMap::create("res/storymap.tmx");
	map->setScale(0.58);
	
	addChild(map, 1);

	//从TMX中获取ground对象层
	TMXObjectGroup* groundObjects = map->getObjectGroup("ground");
	ValueVector groundContainer = groundObjects->getObjects();
	for (auto obj1 : groundContainer) {
		ValueMap values1 = obj1.asValueMap();
		int x1 = values1.at("x").asInt() + 48;
		int y1 = values1.at("y").asInt() + 141;
		brick = Sprite::create("brick.png");
		brick->setPosition(x1, y1);
		
		//player[t]->getCharaSpr()->setPhysicsBody(PhysicsBody::createBox(player[t]->getCharaSpr()->getContentSize()));
		brick->setPhysicsBody(PhysicsBody::createBox(brick->getContentSize()));
		brick->setTag(2);
		brick->getPhysicsBody()->setDynamic(false);
		brickcontainer.pushBack(brick);
		map->addChild(brick, 1);
	}
	//从TMX中获取pipe对象层
	TMXObjectGroup* pipeObjects = map->getObjectGroup("pipe");
	ValueVector pipeContainer = pipeObjects->getObjects();
	for (auto obj2 : pipeContainer) {
		ValueMap values2 = obj2.asValueMap();
		int x2 = values2.at("x").asInt() + 48;
		int y2 = values2.at("y").asInt() + 270;
		pipe = Sprite::create("pipe.png");
		pipe->setPosition(x2, y2);
		
		//player[t]->getCharaSpr()->setPhysicsBody(PhysicsBody::createBox(player[t]->getCharaSpr()->getContentSize()));
		pipe->setPhysicsBody(PhysicsBody::createBox(pipe->getContentSize()));
		pipe->setTag(2);
		pipe->getPhysicsBody()->setDynamic(false);
		pipecontainer.pushBack(pipe);
		map->addChild(pipe, 1);
	}
	////从TMX中获取enemy1对象层
	//TMXObjectGroup* enemy1Objects = map->getObjectGroup("enemy1");
	//ValueVector enemy1Container = pipeObjects->getObjects();
	//for (auto obj3 : enemy1Container) {
	//	ValueMap values3 = obj3.asValueMap();
	//	int x3 = values3.at("x").asInt() ;
	//	int y3 = values3.at("y").asInt() ;
	//	Sprite* enemy1 = Sprite::create("enemy1.png");

	//	enemy1->setPosition(x3, y3);
	//	//player[t]->getCharaSpr()->setPhysicsBody(PhysicsBody::createBox(player[t]->getCharaSpr()->getContentSize()));
	//	enemy1->setPhysicsBody(PhysicsBody::createBox(enemy1->getContentSize()));
	//	enemy1->getPhysicsBody()->setDynamic(false);
	//	enemy1container.pushBack(enemy1);
	//	map->addChild(enemy1, 1);

	//	
	//}
}

void StoryGame::addHpBar(){
	Sprite* sp1 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
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
}


void StoryGame::preloadMusic() {
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("shoot.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("move.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("shout.mp3");
}

void StoryGame::playBgm() {
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3", true);
}

Sprite* StoryGame::addPlayer(int x, int t)
{
	player[t]->getCharaSpr()->setScale(1.0, 1.0);
	player[t]->getCharaSpr()->setPosition(Vec2(x, origin.y + player[t]->getCharaSpr()->getContentSize().height / 2 + altitude));
	player[t]->getCharaSpr()->setPhysicsBody(PhysicsBody::createBox(player[t]->getCharaSpr()->getContentSize(),PhysicsMaterial(0.1f, 0.1, 0.0f)));
	player[t]->getCharaSpr()->getPhysicsBody()->setContactTestBitmask(1);
	player[t]->getCharaSpr()->getPhysicsBody()->setDynamic(true);
	player[t]->getCharaSpr()->getPhysicsBody()->setRotationEnable(false);
	addChild(player[t]->getCharaSpr(), 3);

	return player[t]->getCharaSpr();
}

void StoryGame::addEnemy() {
	enemy = Sprite::create("enemy1.png");
	enemy->setScale(0.5);
	enemy->setPosition(440,400);
	addChild(enemy, 2);

}

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
		move = MoveBy::create(0.4, Point(20, 0));
		move2 = MoveBy::create(0.4, Point(-20, 0));

		player[0]->getCharaSpr()->setScale(-1.0, 1.0);
		player[0]->getCharaSpr()->runAction(animate);

		
		player[0]->getCharaSpr()->runAction(MoveBy::create(0.4, Point(-20, 0)));
		
		this->schedule(schedule_selector(StoryGame::moveContine), 0.3f);
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		SimpleAudioEngine::getInstance()->playEffect("move.mp3");
		player[0]->getCharaSpr()->setScale(1.0, 1.0);
		move = MoveBy::create(0.4, Point(-20, 0));
		player[0]->getCharaSpr()->runAction(animate);

		if (player[0]->getCharaSpr()->getPositionX() < 240) {
			player[0]->getCharaSpr()->runAction(MoveBy::create(0.4, Point(20, 0)));
		}
		else if (map->getPositionX() >= -4300) {
			map->runAction(MoveBy::create(0.4, Point(-20, 0)));
			enemy->runAction(MoveBy::create(0.4, Point(-20, 0)));
		} else {
			player[0]->getCharaSpr()->runAction(MoveBy::create(0.4, Point(20, 0)));
		}

		this->schedule(schedule_selector(StoryGame::moveContine), 0.3f);
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		move = MoveBy::create(0.4, Point(0, 200));
		player[0]->getCharaSpr()->runAction(move);
		this->schedule(schedule_selector(StoryGame::moveContine), 0.3f);
		CCLOG("player X:%f", player[0]->getCharaSpr()->getPositionX());
		CCLOG("map X:%f", map->getPositionX());
		CCLOG("player Y:%f", player[0]->getCharaSpr()->getPositionY()); 
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_J:
		SimpleAudioEngine::getInstance()->playEffect("shoot.mp3");
		bullet1fire();
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
	
		player[0]->getCharaSpr()->runAction(MoveBy::create(0.4, Point(-20, 0)));
	
		break;
	case EventKeyboard::KeyCode::KEY_D:
		offsetX = -20;
		if (player[0]->getCharaSpr()->getPositionX() <= 240) {
			player[0]->getCharaSpr()->runAction(MoveBy::create(0.4, Point(20, 0)));
		}
		else if (map->getPositionX() >= -4300) {
			map->runAction(MoveBy::create(0.4, Point(-20, 0)));
			enemy->runAction(MoveBy::create(0.4, Point(-20, 0)));
		}
		else {
			player[0]->getCharaSpr()->runAction(MoveBy::create(0.4, Point(20, 0)));
		}
		break;
	default:
		offsetY = offsetX = 0;
		offsetX2 = offsetY2 = 0;
		break;
	}
	auto animate = Animate::create(Animation::createWithSpriteFrames(player[0]->getWalkFrame(), 0.04f));

	//auto moveTo = MoveTo::create(0.3, Vec2(map->getPositionX() + offsetX, map->getPositionY() + offsetY));
	//map->runAction(moveTo);
	//enemy->runAction(MoveTo::create(0.3, Vec2(enemy->getPositionX() + offsetX, enemy->getPositionY() + offsetY)));
	player[0]->getCharaSpr()->runAction(animate);
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
	int tagA = spriteA->getTag();
	int tagB = spriteB->getTag();

	auto animate = Animate::create(Animation::createWithSpriteFrames(player[0]->getDeadFrame(), 0.1f));
	//tiledmap 的setTag没用...
	if (tagA == 2 && tagB == 4) {
		bullet2->removeFromParent();
		bullet2 = NULL;
	}
	if (tagA == 4 && tagB == 1) {
		bullet2->removeFromParent();
		damage(-1,0);
		bullet2 = NULL;
	}

	return true;
}

void StoryGame::onBack(Ref* ref)
{
	Director::getInstance()->replaceScene(CCTransitionProgressOutIn::create(1.0f, HelloWorld::createScene()));
}


void StoryGame::bullet1fire(){
	if (bullet1 == NULL) {
		bullet1 = Sprite::create("bullet1.png");
		bullet1->setScale(0.5);
		bullet1->setTag(3);
		bullet1->setPosition(Vec2(player[0]->getCharaSpr()->getPosition().x + player[0]->getCharaSpr()->getContentSize().width / 2 + bullet1->getContentSize().width / 2, player[0]->getCharaSpr()->getPosition().y));
		addChild(bullet1, 3);
		bullet1->setPhysicsBody(PhysicsBody::createCircle(bullet1->getContentSize().width / 2));
		bullet1->getPhysicsBody()->setVelocity(Vec2(1000, 0));
		bullet1->getPhysicsBody()->setContactTestBitmask(1);
		bullet1->getPhysicsBody()->setGravityEnable(false);
	}
}


void StoryGame::damage(int damage, int player)
{
	if (player == 0) {
		if (hp1->getPercentage() + damage > 0 && hp1->getPercentage() + damage <= 100) {
			hp1->setPercentage(hp1->getPercentage() + damage);
		}
		else if (hp1->getPercentage() + damage <= 0) {
			hp1->setPercentage(0);
			Director::getInstance()->replaceScene(End::createScene());
		}
		else {
			hp1->setPercentage(100);
		}
		// 实现血量渐渐变化
		auto updateHP = ProgressTo::create(0.2, (hp1->getPercentage() + damage));
		hp1->runAction(updateHP);
	}


}

void StoryGame::update(float dt){
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_A) == false &&
		isKeyPressed(EventKeyboard::KeyCode::KEY_D) == false &&
		isKeyPressed(EventKeyboard::KeyCode::KEY_W) == false)
	{
		player[0]->getCharaSpr()->stopAllActions();
		map->stopAllActions();
		enemy->stopAllActions();
	}
	Director::getInstance()->getRunningScene()->getPhysicsWorld()->setAutoStep(false);

	for (int i = 0; i < 3; ++i) {
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->step(1 / 180.0f);
	}
	if ((enemy->getPositionX() - player[0]->getCharaSpr()->getPositionX()) < 500 && bullet2 == NULL) {
		bullet2 = Sprite::create("bullet2.png");
		bullet2->setScale(0.5);
		bullet2->setTag(4);
		bullet2->setPosition(Vec2(enemy->getPosition().x - enemy->getContentSize().width / 2 - bullet2->getContentSize().width / 2, enemy->getPosition().y));
		addChild(bullet2, 3);
		bullet2->setPhysicsBody(PhysicsBody::createCircle(bullet2->getContentSize().width / 2));
		MoveTo* moveto = MoveTo::create(2, Vec2(player[0]->getCharaSpr()->getPositionX(), player[0]->getCharaSpr()->getPositionY()));
		bullet2->runAction(moveto);
		bullet2->getPhysicsBody()->setContactTestBitmask(1);
		bullet2->getPhysicsBody()->setGravityEnable(true);
	}
}
