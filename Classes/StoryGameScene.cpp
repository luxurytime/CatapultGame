#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "EndScene.h"
#include "StoryGameScene.h"
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


	
	addmap();

		//Vector<Sprite*>::iterator brickit = brickcontainer.begin();
		//for (; brickit != brickcontainer.end();) {
		//	(*brickit)->setPhysicsBody(PhysicsBody::createBox((*brickit)->getContentSize()));
		//	(*brickit)->getPhysicsBody()->setContactTestBitmask(1);
		//	(*brickit)->getPhysicsBody()->setDynamic(false);
		//	//(*brickit)->getPhysicsBody()->setRotationEnable(false);
		//}

	/*Sprite* background = Sprite::create("storyscene.png");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);*/

	auto label = LabelTTF::create("MainMenu", "Marker Felt.ttf", 48);
	auto menuItem = MenuItemLabel::create(label);
	auto menu = Menu::create(menuItem, nullptr);
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	});
	menu->setPosition(Vec2::ZERO);
	menuItem->setPosition(visibleSize.width*0.2, visibleSize.height*0.9);
	//addChild(menu, 1);



	player[0] = new Boy();


	addPlayer(origin.x + visibleSize.width / 4, 0);
	player[0]->getCharaSpr()->setTag(1);


	preloadMusic();
	//playBgm();

	//addEdge();
	addListener();
	//getFrameAction();
	//getFrameAction2();
	addHpBar();
	//scheduleUpdate();
	return true;
}

void StoryGame::addHpBar(){
	Sprite* sp1 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* sp2 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* sp = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(610, 362, 4, 16)));

	//ÑªÌõ1
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

	int altitude = 100;
	player[t]->getCharaSpr()->setScale(0.5, 0.5);
	Size tmpSize = Size(player[t]->getCharaSpr()->getContentSize().width / 1.5, player[t]->getCharaSpr()->getContentSize().height);
	//player[t]->getCharaSpr()->setContentSize(tmpSize);

	player[t]->getCharaSpr()->setPosition(Vec2(x, origin.y + player[t]->getCharaSpr()->getContentSize().height / 2 + altitude));
	player[t]->getCharaSpr()->setPhysicsBody(PhysicsBody::createBox(tmpSize, PhysicsMaterial(1.0f, 0, 0.1f)));
	player[t]->getCharaSpr()->getPhysicsBody()->setContactTestBitmask(1);
	//player[0]->getCharaSpr()->getPhysicsBody()->setVelocity(Point(0, 0));
	player[t]->getCharaSpr()->getPhysicsBody()->setDynamic(true);
	player[t]->getCharaSpr()->getPhysicsBody()->setRotationEnable(false);

	addChild(player[t]->getCharaSpr(), 3);

	return player[t]->getCharaSpr();
}
void StoryGame::addmap() {
	//map = cocos2d::experimental::TMXTiledMap::create("storymap.tmx");
	map = TMXTiledMap::create("res/storymap.tmx");
	map->setScale(0.58);
	addChild(map, 1);

	//从TMX中获取ground对象层
	TMXObjectGroup* groundObjects = map->getObjectGroup("ground");
	ValueVector groundContainer = groundObjects->getObjects();
	for (auto obj : groundContainer) {
		ValueMap values = obj.asValueMap();
		int x = values.at("x").asInt() + 48;
		int y = values.at("y").asInt() + 141;
		Sprite* brick = Sprite::create("brick.png");

		brick->setPosition(x, y);
		//player[t]->getCharaSpr()->setPhysicsBody(PhysicsBody::createBox(player[t]->getCharaSpr()->getContentSize()));
		brick->setPhysicsBody(PhysicsBody::createBox(brick->getContentSize()));
		brick->getPhysicsBody()->setDynamic(false);
		brickcontainer.pushBack(brick);
		map->addChild(brick, 1);
	}
	//从TMX中获取pipe对象层
	TMXObjectGroup* pipeObjects = map->getObjectGroup("pipe");
	ValueVector pipeContainer = pipeObjects->getObjects();
	for (auto obj : pipeContainer) {
		ValueMap values = obj.asValueMap();
		int x = values.at("x").asInt() + 48;
		int y = values.at("y").asInt() + 270;
		Sprite* pipe = Sprite::create("pipe.png");

		pipe->setPosition(x, y);
		//player[t]->getCharaSpr()->setPhysicsBody(PhysicsBody::createBox(player[t]->getCharaSpr()->getContentSize()));
		pipe->setPhysicsBody(PhysicsBody::createBox(pipe->getContentSize()));
		pipe->getPhysicsBody()->setDynamic(false);
		pipecontainer.pushBack(pipe);
		map->addChild(pipe, 1);
	}


}
void StoryGame::addEdge(){
	auto edge = Sprite::create();
	auto boundBody = PhysicsBody::createEdgeBox(visibleSize);
	boundBody->setDynamic(false);
	boundBody->setContactTestBitmask(1);
	edge->setPhysicsBody(boundBody);
	edge->setTag(0);
	//edge->setPosition(Point(visibleSize.width, visibleSize.height+50));
	edge->setPosition(Point(visibleSize.width, visibleSize.height+80));
	edge->setContentSize(visibleSize);
	this->addChild(edge);
}

void StoryGame::addListener()
{

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(StoryGame::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(StoryGame::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

}


void StoryGame::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

	keys[keyCode] = true;

	auto animation = Animation::createWithSpriteFrames(player[0]->getWalkFrame(), 0.05f);
	auto animate = Animate::create(animation);
	MoveBy* move;
	MoveBy* move2;
	MoveBy* move3;
	int movedis = 20;
	switch (keyCode)
	{

	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		SimpleAudioEngine::getInstance()->playEffect("move.mp3");
		move = MoveBy::create(0.4, Point(20, 0));
		move2 = MoveBy::create(0.4, Point(-20, 0));

		player[0]->getCharaSpr()->setScale(-0.5, 0.5);
		if (map->getPositionX() <= -20) {
			map->runAction(move);
			player[0]->getCharaSpr()->runAction(Spawn::create(animate, NULL));
		}
		else {
			//player[0]->getCharaSpr()->runAction(move2);
			player[0]->getCharaSpr()->runAction(Spawn::create(animate,move2, NULL));
		}
	
		this->schedule(schedule_selector(StoryGame::moveContine), 0.3f);
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		SimpleAudioEngine::getInstance()->playEffect("move.mp3");
		move = MoveBy::create(0.4, Point(-20, 0));
		move2 = MoveBy::create(0.4, Point(20, 0));
	
		player[0]->getCharaSpr()->setScale(0.5, 0.5);
		player[0]->getCharaSpr()->runAction(Spawn::create(animate, NULL));
		if (player[0]->getCharaSpr()->getPositionX() >= 240) {
			map->runAction(move);
		}
		else {
			player[0]->getCharaSpr()->runAction(move2);
		}
		this->schedule(schedule_selector(StoryGame::moveContine), 0.3f);
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		//SimpleAudioEngine::getInstance()->playEffect("jump.mp3");
		move3 = MoveBy::create(0.4, Point(0, 150));
		//player[0]->getCharaSpr()->setScale(2.0, 2.0);
		if (player[0]->getCharaSpr()->getPositionY() <= 75 ) {
		player[0]->getCharaSpr()->runAction(move3);
		}
		//player[0]->getCharaSpr()->runAction(Spawn::create(animate, NULL));
		this->schedule(schedule_selector(StoryGame::update), 0.3f);
		CCLOG("error buffer:%f", player[0]->getCharaSpr()->getPositionX());
		CCLOG("error buffer:%f", map->getPositionX());
		CCLOG("error buffer:%f", player[0]->getCharaSpr()->getPositionY()); 		//ground Y = 74
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
	auto animation = Animation::createWithSpriteFrames(player[0]->getWalkFrame(), 0.05f);
	auto animate = Animate::create(animation);
	MoveBy* move;
	MoveBy* move2;
	int movedis = 20;
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_A:
		SimpleAudioEngine::getInstance()->playEffect("move.mp3");
		move = MoveBy::create(0.4, Point(20, 0));
		move2 = MoveBy::create(0.4, Point(-20, 0));

		player[0]->getCharaSpr()->setScale(-0.5, 0.5);
		if (map->getPositionX() <= -20) {
			map->runAction(move);

		}
		else {
			player[0]->getCharaSpr()->runAction(move2);
		}
		player[0]->getCharaSpr()->runAction(Spawn::create(animate, NULL));
		this->schedule(schedule_selector(StoryGame::moveContine), 0.3f);
		break;
	case EventKeyboard::KeyCode::KEY_D:
		SimpleAudioEngine::getInstance()->playEffect("move.mp3");
		move = MoveBy::create(0.4, Point(-20, 0));
		move2 = MoveBy::create(0.4, Point(20, 0));
		player[0]->getCharaSpr()->setScale(0.5, 0.5);
		if (player[0]->getCharaSpr()->getPositionX() >= 240) {
			map->runAction(move);
		}
		else {
			player[0]->getCharaSpr()->runAction(move2);
		}
		player[0]->getCharaSpr()->runAction(Spawn::create(animate, NULL));
		this->schedule(schedule_selector(StoryGame::moveContine), 0.3f);
		break;
	default:

		break;
	}



}




void StoryGame::update(float dt){
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_A) == false && isKeyPressed(EventKeyboard::KeyCode::KEY_D) == false)
	{
		player[0]->getCharaSpr()->stopAllActions();
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



