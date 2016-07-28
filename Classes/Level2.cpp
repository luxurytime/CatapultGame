#include "Level2.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "EndScene.h"
#include <math.h>

using namespace CocosDenshion;

USING_NS_CC;

Scene* Level2::createScene()
{
	// 'scene' is an autorelease object
	//auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Point(0, -98));

	// 'layer' is an autorelease object
	auto layer = Level2::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Level2::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	//addplayer
	player[0] = new Boy();
	addPlayer(origin.x + visibleSize.width / 4, 0);

	//preloadMusic();
	//playBgm();

	addmap();

	addListener();

	scheduleUpdate();

	return true;
}
void Level2::addmap() {
	//map = cocos2d::experimental::TMXTiledMap::create("storymap.tmx");
	map = TMXTiledMap::create("res/storymap2.tmx");
	map->setScale(0.8);
	map->setPosition(0, 0);

	addChild(map, 1);

	//从TMX中获取ground对象层
	TMXObjectGroup* groundObjects = map->getObjectGroup("wall");
	ValueVector groundContainer = groundObjects->getObjects();
	for (auto obj1 : groundContainer) {
		ValueMap values1 = obj1.asValueMap();
		int x1 = values1.at("x").asInt();
		int y1 = values1.at("y").asInt();
		brick = Sprite::create("brick.png");
		brick->setPosition(x1, y1);
		brick->setPhysicsBody(PhysicsBody::createBox(brick->getContentSize()));
		brick->setTag(2);
		brick->getPhysicsBody()->setDynamic(false);
		brickcontainer.pushBack(brick);
		map->addChild(brick, 1);
	}

}


void Level2::preloadMusic() {
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("shoot.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("move.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("shout.mp3");
}

void Level2::playBgm() {
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3", true);
}

Sprite* Level2::addPlayer(int x, int t)
{
	player[t]->getCharaSpr()->setScale(1.0, 1.0);
	player[t]->getCharaSpr()->setPosition(Vec2(x, origin.y + player[t]->getCharaSpr()->getContentSize().height / 2 ));
	player[t]->getCharaSpr()->setPhysicsBody(PhysicsBody::createBox(player[t]->getCharaSpr()->getContentSize(), PhysicsMaterial(0.1f, 0.1, 0.0f)));
	player[t]->getCharaSpr()->getPhysicsBody()->setContactTestBitmask(1);
	player[t]->getCharaSpr()->getPhysicsBody()->setDynamic(true);
	player[t]->getCharaSpr()->getPhysicsBody()->setRotationEnable(false);
	addChild(player[t]->getCharaSpr(), 3);

	return player[t]->getCharaSpr();
}



void Level2::addListener()
{

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Level2::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Level2::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);


}

void Level2::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

	keys[keyCode] = true;

	auto animation = Animation::createWithSpriteFrames(player[0]->getWalkFrame(), 0.05f);
	auto animate = Animate::create(animation);
	MoveBy* move;
	int movedis = 20;
	switch (keyCode)
	{

	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		SimpleAudioEngine::getInstance()->playEffect("move.mp3");
		move = MoveBy::create(0.4, Point(20, 0));
		player[0]->getCharaSpr()->setScale(-1.0, 1.0);
		map->runAction(move);
		this->schedule(schedule_selector(Level2::moveContine), 0.3f);
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		SimpleAudioEngine::getInstance()->playEffect("move.mp3");
		player[0]->getCharaSpr()->setScale(1.0, 1.0);
		move = MoveBy::create(0.4, Point(-20, 0));
		player[0]->getCharaSpr()->runAction(animate);
		map->runAction(move);

		this->schedule(schedule_selector(Level2::moveContine), 0.3f);
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		move = MoveBy::create(0.4, Point(0, 200));
		player[0]->getCharaSpr()->runAction(move);
		this->schedule(schedule_selector(Level2::moveContine), 0.3f);
		break;
	default:
		break;
	}
}

bool Level2::isKeyPressed(EventKeyboard::KeyCode keyCode)
{
	if (keys[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}

void Level2::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	keys[keyCode] = false;

	if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		this->unschedule(schedule_selector(Level2::moveContine));
	}
}


void Level2::onKeyPressedContinue(EventKeyboard::KeyCode keyCode)
{
	int offsetX = 0, offsetY = 0;
	int offsetX2 = 0, offsetY2 = 0;
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_A:
		offsetX = 20;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		offsetX = -20;
		break;
	default:
		offsetY = offsetX = 0;
		offsetX2 = offsetY2 = 0;
		break;
	}
	auto animate = Animate::create(Animation::createWithSpriteFrames(player[0]->getWalkFrame(), 0.04f));

	auto moveTo = MoveTo::create(0.3, Vec2(map->getPositionX() + offsetX, map->getPositionY() + offsetY));
	map->runAction(moveTo);
	player[0]->getCharaSpr()->runAction(animate);
}



void Level2::moveContine(float dt)
{
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_A)) {
		onKeyPressedContinue(EventKeyboard::KeyCode::KEY_A);
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_D)) {
		onKeyPressedContinue(EventKeyboard::KeyCode::KEY_D);
	}
}


void Level2::onBack(Ref* ref)
{
	Director::getInstance()->replaceScene(CCTransitionProgressOutIn::create(1.0f, HelloWorld::createScene()));
}


void Level2::update(float dt){
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_A) == false &&
		isKeyPressed(EventKeyboard::KeyCode::KEY_D) == false &&
		isKeyPressed(EventKeyboard::KeyCode::KEY_W) == false)
	{
		player[0]->getCharaSpr()->stopAllActions();
		map->stopAllActions();
	}
	Director::getInstance()->getRunningScene()->getPhysicsWorld()->setAutoStep(false);

	for (int i = 0; i < 3; ++i) {
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->step(1 / 180.0f);
	}

}
