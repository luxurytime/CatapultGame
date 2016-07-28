#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "EndScene.h"
#include <math.h>

using namespace CocosDenshion;

int altitude = 70;


USING_NS_CC;

Scene* Games::createScene()
{
	// 'scene' is an autorelease object
	//auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Point(0, -980));

	// 'layer' is an autorelease object
	auto layer = Games::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
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

	Sprite* background = Sprite::create("background2.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);

	//Sprite* player[0] = Sprite::create("player.png");
	//player[0]->setPosition(visibleSize.width / 4, visibleSize.height * 0.15);
	//player[0]->setScale(0.1, 0.1);
	//addChild(player[0], 1);

	//Sprite* player[1] = Sprite::create("player.png");
	//player[1]->setPosition(visibleSize.width * 0.75, visibleSize.height * 0.15);
	//player[1]->setScale(0.1, 0.1);
	//addChild(player[1], 1);

	//Sprite* arrow = Sprite::create("arrow.png");
	//arrow->setPosition(visibleSize.width / 4+55, visibleSize.height * 0.15+70);
	//arrow->setScale(0.5, 0.5);
	//addChild(arrow, 1);

	//Sprite* line = Sprite::create("line2.png");
	//line->setPosition(visibleSize.width / 2+20, visibleSize.height * 0.35+30);
	//line->setScale(0.65, 0.65);
	//addChild(line, 1);

	//Sprite* bomb = Sprite::create("bomb.png");
	//bomb->setPosition(visibleSize.width / 2, visibleSize.height * 0.4+40);
	//bomb->setScale(0.4, 0.4);
	//addChild(bomb, 2);



	//Sprite* lifep = Sprite::create("lp.png");
	//lifep->setPosition(50, visibleSize.height-30);
	//lifep->setScale(0.2, 0.2);
	//addChild(lifep, 2);


	//Sprite* lifep2 = Sprite::create("lp.png");
	//lifep2->setPosition(visibleSize.width - 50, visibleSize.height - 30);
	//lifep2->setScale(0.2, 0.2);
	//addChild(lifep2, 2);

	auto label = LabelTTF::create("MainMenu", "Marker Felt.ttf", 48);
	auto menuItem = MenuItemLabel::create(label);
	auto menu = Menu::create(menuItem, nullptr);
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	});
	menu->setPosition(Vec2::ZERO);
	menuItem->setPosition(visibleSize.width*0.2, visibleSize.height*0.9);
	//addChild(menu, 1);

	/*MenuItemImage* startMenuItem = MenuItemImage::create("button.png", "button.png", CC_CALLBACK_1(Games::onBack, this));
	startMenuItem->setPosition(visibleSize.width / 8, visibleSize.height);
	auto start = Menu::create(startMenuItem, NULL);
	start->setPosition(Point::ZERO);
	addChild(start, 1);*/

	powerDir = false;

	already = false;

	currentPlayer = 0;

	player[0] = new Boy();
	player[1] = new Boy();

	addPlayer(origin.x + visibleSize.width / 4, 0);
	player[0]->getCharaSpr()->setTag(1);
	addPlayer(origin.x + visibleSize.width / 4 * 3, 1);
	player[1]->getCharaSpr()->setFlipX(true);
	player[1]->getCharaSpr()->setTag(2);

	preloadMusic();
	//playBgm();

	addEdge();
	addListener();
	//getFrameAction();
	//getFrameAction2();
	addHpBar();

	bullet1 = NULL;
	bullet2 = NULL;

	scheduleUpdate();


	return true;
}

void Games::addHpBar(){
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

	//ÑªÌõ2
	hp2 = ProgressTimer::create(sp);
	hp2->setScaleX(90);
	hp2->setAnchorPoint(Vec2(0, 0));
	hp2->setType(ProgressTimerType::BAR);
	hp2->setBarChangeRate(Point(1, 0));
	hp2->setMidpoint(Point(1, 0));
	hp2->setPercentage(100);
	hp2->setPosition(Vec2(origin.x + visibleSize.width / 2 + 14 * hp2->getContentSize().width, origin.y + visibleSize.height - 2 * hp2->getContentSize().height));
	addChild(hp2, 4);
	sp2->setAnchorPoint(Vec2(0, 0));
	sp2->setPosition(Vec2(origin.x + visibleSize.width / 2 + 11 * hp2->getContentSize().width + 1.5, origin.y + visibleSize.height - sp2->getContentSize().height));
	addChild(sp2, 3);
	sp2->setFlipX(true);
}

bool Games::onTouchBegan(Touch *touch, cocos2d::Event *event){
	auto location = touch->getLocation();

	powerBar = CCProgressTimer::create(Sprite::create("Toge.png"));
	powerBar->setAnchorPoint(Vec2(0, 0.5));
	//powerBar->setRotation(-45);
	if ((location.x - player[currentPlayer]->getCharaSpr()->getPosition().x) < 0)
	{
		powerBar->setRotation(-(atan((location.y - player[currentPlayer]->getCharaSpr()->getPosition().y) / (location.x - player[currentPlayer]->getCharaSpr()->getPosition().x))) / 3.1416 * 180 + 180);
	}
	else
	{
		powerBar->setRotation(-(atan((location.y - player[currentPlayer]->getCharaSpr()->getPosition().y) / (location.x - player[currentPlayer]->getCharaSpr()->getPosition().x))) / 3.1416 * 180);
	}

	powerBar->setType(ProgressTimer::Type::BAR);
	powerBar->setMidpoint(Point(0, 0));
	powerBar->setBarChangeRate(Point(1, 0));
	powerBar->setPercentage(0);

	powerBar->setPosition(player[currentPlayer]->getCharaSpr()->getPosition().x, player[currentPlayer]->getCharaSpr()->getPosition().y);
	addChild(powerBar, 3);

	this->schedule(schedule_selector(Games::powerRoll), 0.002f);

	return true;
	//printf("move");
}

void Games::onTouchEnded(Touch *touch, cocos2d::Event *event){
	this->unschedule(schedule_selector(Games::powerRoll));


	shootStone(powerBar->getPercentage(), powerBar->getRotation(), touch->getLocation());

	removeChild(powerBar);

	currentPlayer = 1 - currentPlayer;
	//printf("move");
}

void Games::onTouchMoved(Touch *touch, cocos2d::Event *event){
	auto location = touch->getLocation();
	if ((location.x - player[currentPlayer]->getCharaSpr()->getPosition().x) < 0)
	{
		powerBar->setRotation(-(atan((location.y - player[currentPlayer]->getCharaSpr()->getPosition().y) / (location.x - player[currentPlayer]->getCharaSpr()->getPosition().x))) / 3.1416 * 180 + 180);
	}
	else
	{
		powerBar->setRotation(-(atan((location.y - player[currentPlayer]->getCharaSpr()->getPosition().y) / (location.x - player[currentPlayer]->getCharaSpr()->getPosition().x))) / 3.1416 * 180);
	}
	//this->schedule(schedule_selector(Games::powerRoll), 0.002f);
	//auto location = touch->getLocation();
	//test->setPosition(location.x, location.y);
	//printf("move");
}

void Games::preloadMusic() {
	// Ô¤¼ÓÔØÒôÀÖ
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("shoot.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("move.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("shout.mp3");
}

void Games::playBgm() {
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3", true);
}

Sprite* Games::addPlayer(int x, int t)
{
	player[t]->getCharaSpr()->setScale(2.0, 2.0);
	player[t]->getCharaSpr()->setPosition(Vec2(x, origin.y + player[t]->getCharaSpr()->getContentSize().height / 2 + altitude));
	player[t]->getCharaSpr()->setPhysicsBody(PhysicsBody::createBox(player[t]->getCharaSpr()->getContentSize()));
	player[t]->getCharaSpr()->getPhysicsBody()->setContactTestBitmask(1);
	//player[t]->getCharaSpr()->getPhysicsBody()->setDynamic(false);
	player[t]->getCharaSpr()->getPhysicsBody()->setRotationEnable(false);
	player[0]->getCharaSpr()->getPhysicsBody()->setVelocity(Point(1000, 20));
	addChild(player[t]->getCharaSpr(), 3);

	return player[t]->getCharaSpr();
}

void Games::addEdge(){
	auto edge = Sprite::create();
	auto boundBody = PhysicsBody::createEdgeBox(visibleSize);
	boundBody->setDynamic(false);
	boundBody->setContactTestBitmask(1);
	edge->setPhysicsBody(boundBody);
	edge->setTag(0);
	edge->setPosition(Point(visibleSize.width, visibleSize.height));
	edge->setContentSize(visibleSize);
	this->addChild(edge);
}

void Games::addListener()
{
	// ¼üÅÌÊÂ¼þ
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Games::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Games::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	// ´¥ÅöÊÂ¼þ
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Games::onConcactBegan, this);
	_eventDispatcher->addEventListenerWithFixedPriority(contactListener, 1);

	//mouse event listener
	auto listener = EventListenerTouchOneByOne::create();  //µ¥µã´¥ÃþÊÂ¼þEventListenerTouchAllAtOnce
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Games::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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
		move = MoveBy::create(0.4, Point(-20, 0));
		player[0]->getCharaSpr()->setScale(-2.0, 2.0);
		player[0]->getCharaSpr()->runAction(Spawn::create(animate, move, NULL));
		this->schedule(schedule_selector(Games::moveContine), 0.3f);
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		SimpleAudioEngine::getInstance()->playEffect("move.mp3");
		move = MoveBy::create(0.4, Point(20, 0));
		player[0]->getCharaSpr()->setScale(2.0, 2.0);
		player[0]->getCharaSpr()->runAction(Spawn::create(animate, move, NULL));
		this->schedule(schedule_selector(Games::moveContine), 0.3f);
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		SimpleAudioEngine::getInstance()->playEffect("shoot.mp3");
		bullet1fire();
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_J:
		move = MoveBy::create(0.4, Point(-20, 0));
		player[1]->getCharaSpr()->setScale(2.0, 2.0);
		player[1]->getCharaSpr()->runAction(Spawn::create(animate, move, NULL));
		SimpleAudioEngine::getInstance()->playEffect("move.mp3");
		this->schedule(schedule_selector(Games::moveContine2), 0.3f);
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_L:
		move = MoveBy::create(0.4, Point(20, 0));
		player[1]->getCharaSpr()->setScale(-2.0, 2.0);
		player[1]->getCharaSpr()->runAction(Spawn::create(animate, move, NULL));
		SimpleAudioEngine::getInstance()->playEffect("move.mp3");
		this->schedule(schedule_selector(Games::moveContine2), 0.3f);
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_K:
		SimpleAudioEngine::getInstance()->playEffect("shoot.mp3");
		bullet2fire();
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

	if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		this->unschedule(schedule_selector(Games::moveContine));
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_J || keyCode == EventKeyboard::KeyCode::KEY_L)
	{
		this->unschedule(schedule_selector(Games::moveContine2));
	}
}

void Games::onKeyPressedContinue(EventKeyboard::KeyCode keyCode)
{
	int offsetX = 0, offsetY = 0;
	int offsetX2 = 0, offsetY2 = 0;
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_A:
		offsetX = -20;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		offsetX = 20;
		break;
	case EventKeyboard::KeyCode::KEY_J:
		offsetX2 = -20;
		break;
	case EventKeyboard::KeyCode::KEY_L:
		offsetX2 = 20;
		break;
	default:
		offsetY = offsetX = 0;
		offsetX2 = offsetY2 = 0;
		break;
	}

	auto animate = Animate::create(Animation::createWithSpriteFrames(player[0]->getWalkFrame(), 0.04f));

	auto moveTo = MoveTo::create(0.3, Vec2(player[0]->getCharaSpr()->getPositionX() + offsetX, player[0]->getCharaSpr()->getPositionY() + offsetY));
	player[0]->getCharaSpr()->runAction(Spawn::create(animate, moveTo, NULL));

	auto animate2 = Animate::create(Animation::createWithSpriteFrames(player[1]->getWalkFrame(), 0.04f));

	auto moveTo2 = MoveTo::create(0.3, Vec2(player[1]->getCharaSpr()->getPositionX() + offsetX2, player[1]->getCharaSpr()->getPositionY() + offsetY2));
	player[1]->getCharaSpr()->runAction(Spawn::create(animate2, moveTo2, NULL));
}

void Games::moveContine(float dt)
{
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_A)) {
		onKeyPressedContinue(EventKeyboard::KeyCode::KEY_A);
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_D)) {
		onKeyPressedContinue(EventKeyboard::KeyCode::KEY_D);
	}
}

void Games::moveContine2(float dt)
{
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_J)) {
		onKeyPressedContinue(EventKeyboard::KeyCode::KEY_J);
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_L)) {
		onKeyPressedContinue(EventKeyboard::KeyCode::KEY_L);
	}
}

bool Games::onConcactBegan(PhysicsContact& contact) {
	Sprite* spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	Sprite* spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();
	int tagA = spriteA->getTag();
	int tagB = spriteB->getTag();

	/*
	¸÷¸öÎïÌåµÄTag£º
	player[0]->getCharaSpr()£º1
	player[1]->getCharaSpr()£º2
	edge£º0
	bullet1£º3
	bullet2£º4
	*/


	auto animate = Animate::create(Animation::createWithSpriteFrames(player[0]->getDeadFrame(), 0.1f));

	if (tagA == 1 && tagB == 4) {
		SimpleAudioEngine::getInstance()->playEffect("shout.mp3");
		bullet2->removeFromParent();
		bullet2 = NULL;
		player[0]->getCharaSpr()->runAction(animate);
		damage(-20, 0);
	}
	else if (tagA == 4 && tagB == 1) {
		SimpleAudioEngine::getInstance()->playEffect("shout.mp3");
		bullet2->removeFromParent();
		bullet2 = NULL;
		player[0]->getCharaSpr()->runAction(animate);
		damage(-20, 0);
	}

	if (tagA == 2 && tagB == 3) {
		SimpleAudioEngine::getInstance()->playEffect("shout.mp3");
		bullet1->removeFromParent();
		bullet1 = NULL;
		player[1]->getCharaSpr()->runAction(animate);
		damage(-20, 1);
	}
	else if (tagA == 3 && tagB == 2) {
		SimpleAudioEngine::getInstance()->playEffect("shout.mp3");
		bullet1->removeFromParent();
		bullet1 = NULL;
		player[1]->getCharaSpr()->runAction(animate);
		damage(-20, 1);
	}

	if (tagA == 3 && tagB == 4) {
		bullet1->removeFromParent();
		bullet1 = NULL;
		bullet2->removeFromParent();
		bullet2 = NULL;
	}
	else if (tagA == 4 && tagB == 3) {
		bullet1->removeFromParent();
		bullet1 = NULL;
		bullet2->removeFromParent();
		bullet2 = NULL;
	}


	if (tagA == 0 && tagB == 3) {
		bullet1->removeFromParent();
		bullet1 = NULL;
	}
	else if (tagA == 3 && tagB == 0) {
		bullet1->removeFromParent();
		bullet1 = NULL;
	}

	if (tagA == 0 && tagB == 4) {
		bullet2->removeFromParent();
		bullet2 = NULL;
	}
	else if (tagA == 4 && tagB == 0) {
		bullet2->removeFromParent();
		bullet2 = NULL;
	}

	return true;
}

void Games::onBack(Ref* ref)
{
	Director::getInstance()->replaceScene(CCTransitionProgressOutIn::create(1.0f, HelloWorld::createScene()));
}

void Games::powerRoll(float dt)
{
	if (powerBar->getPercentage() <= 100 && powerDir == true)
	{
		powerBar->setPercentage(powerBar->getPercentage() - 0.1);
		if (powerBar->getPercentage() == 0) powerDir = false;
	}
	else
	{
		powerBar->setPercentage(powerBar->getPercentage() + 0.1);
		if (powerBar->getPercentage() == 100) powerDir = true;
	}
}

void Games::bullet1fire(){
	if (bullet1 == NULL) {
		bullet1 = Sprite::create("bullet1.png");
		bullet1->setScale(1.5);
		bullet1->setTag(3);
		bullet1->setPosition(Vec2(player[0]->getCharaSpr()->getPosition().x + player[0]->getCharaSpr()->getContentSize().width / 2 + bullet1->getContentSize().width / 2, player[0]->getCharaSpr()->getPosition().y));
		addChild(bullet1, 3);
		bullet1->setPhysicsBody(PhysicsBody::createCircle(bullet1->getContentSize().width / 2));
		bullet1->getPhysicsBody()->setVelocity(Vec2(100, 0));
		bullet1->getPhysicsBody()->setContactTestBitmask(1);
		bullet1->getPhysicsBody()->setGravityEnable(false);
	}
}

void Games::bullet2fire(){
	if (bullet2 == NULL) {
		bullet2 = Sprite::create("bullet2.png");
		bullet2->setScale(1.5);
		bullet2->setTag(4);
		bullet2->setPosition(Vec2(player[1]->getCharaSpr()->getPosition().x - player[1]->getCharaSpr()->getContentSize().width / 2 - bullet2->getContentSize().width / 2, player[1]->getCharaSpr()->getPosition().y));
		addChild(bullet2, 3);
		bullet2->setPhysicsBody(PhysicsBody::createCircle(bullet2->getContentSize().width / 2));
		bullet2->getPhysicsBody()->setVelocity(Vec2(-100, 0));
		bullet2->getPhysicsBody()->setContactTestBitmask(1);
		bullet2->getPhysicsBody()->setGravityEnable(false);
	}
}

void Games::shootStone(float power, float direction, Vec2 loc)
{
	int pow = 4;

	if (currentPlayer == 0) {
		log("player1");
		if (bullet1 == NULL) {
			bullet1 = Sprite::create("ball.png");
			//bullet1->setScale(1.5);
			bullet1->setTag(3);
			addChild(bullet1, 3);
			bullet1->setPhysicsBody(PhysicsBody::createCircle(bullet1->getContentSize().width / 2));

			float vx = 0;
			float vy = 0;

			if (direction >= 0 && direction < 90) {
				Vec2 bullet_loc = Vec2(player[0]->getCharaSpr()->getPosition().x + player[0]->getCharaSpr()->getContentSize().width + bullet1->getContentSize().width, player[0]->getCharaSpr()->getPosition().y);
				float tmpx = loc.x - bullet_loc.x;
				float tmpy = loc.y - bullet_loc.y;
				float tmpz = sqrt(tmpx*tmpx + tmpy*tmpy);
				bullet1->setPosition(bullet_loc);

				vx = abs(tmpx / tmpz*power) * pow;
				vy = -abs(tmpy / tmpz*power) * pow;
			}
			else if (direction >= 90 && direction < 180) {

				Vec2 bullet_loc = Vec2(player[0]->getCharaSpr()->getPosition().x - player[0]->getCharaSpr()->getContentSize().width - bullet1->getContentSize().width, player[0]->getCharaSpr()->getPosition().y);
				float tmpx = loc.x - bullet_loc.x;
				float tmpy = loc.y - bullet_loc.y;
				float tmpz = sqrt(tmpx*tmpx + tmpy*tmpy);
				bullet1->setPosition(bullet_loc);

				vx = -abs(tmpx / tmpz*power) * pow;
				vy = -abs(tmpy / tmpz*power) * pow;

			}
			else if (direction >= 180 && direction <= 270) {
				Vec2 bullet_loc = Vec2(player[0]->getCharaSpr()->getPosition().x - player[0]->getCharaSpr()->getContentSize().width - bullet1->getContentSize().width, player[0]->getCharaSpr()->getPosition().y);
				float tmpx = loc.x - bullet_loc.x;
				float tmpy = loc.y - bullet_loc.y;
				float tmpz = sqrt(tmpx*tmpx + tmpy*tmpy);
				bullet1->setPosition(bullet_loc);

				vx = -abs(tmpx / tmpz*power) * pow;
				vy = abs(tmpy / tmpz*power) * pow;
			}
			else if (direction < 0) {

				Vec2 bullet_loc = Vec2(player[0]->getCharaSpr()->getPosition().x + player[0]->getCharaSpr()->getContentSize().width + bullet1->getContentSize().width, player[0]->getCharaSpr()->getPosition().y);
				float tmpx = loc.x - bullet_loc.x;
				float tmpy = loc.y - bullet_loc.y;
				float tmpz = sqrt(tmpx*tmpx + tmpy*tmpy);

				bullet1->setPosition(bullet_loc);
				vx = abs(tmpx / tmpz*power) * 5;
				vy = abs(tmpy / tmpz*power) * 5;
			}

			bullet1->getPhysicsBody()->setVelocity(Vec2(vx, vy));
			bullet1->getPhysicsBody()->setContactTestBitmask(1);

		}

	}
	if (currentPlayer == 1) {

		if (bullet2 == NULL) {
			bullet2 = Sprite::create("ball.png");
			//bullet2->setScale(1.5);
			bullet2->setTag(4);
			addChild(bullet2, 3);
			bullet2->setPhysicsBody(PhysicsBody::createCircle(bullet2->getContentSize().width / 2));

			float vx = 0;
			float vy = 0;

			if (direction >= 0 && direction < 90) {
				Vec2 bullet_loc = Vec2(player[1]->getCharaSpr()->getPosition().x + player[1]->getCharaSpr()->getContentSize().width + bullet2->getContentSize().width, player[1]->getCharaSpr()->getPosition().y);
				float tmpx = loc.x - bullet_loc.x;
				float tmpy = loc.y - bullet_loc.y;
				float tmpz = sqrt(tmpx*tmpx + tmpy*tmpy);
				bullet2->setPosition(bullet_loc);

				vx = abs(tmpx / tmpz*power) * pow;
				vy = -abs(tmpy / tmpz*power) * pow;
			}
			else if (direction >= 90 && direction < 180) {

				Vec2 bullet_loc = Vec2(player[1]->getCharaSpr()->getPosition().x - player[1]->getCharaSpr()->getContentSize().width - bullet2->getContentSize().width, player[1]->getCharaSpr()->getPosition().y);
				float tmpx = loc.x - bullet_loc.x;
				float tmpy = loc.y - bullet_loc.y;
				float tmpz = sqrt(tmpx*tmpx + tmpy*tmpy);
				bullet2->setPosition(bullet_loc);

				vx = -abs(tmpx / tmpz*power) * pow;
				vy = -abs(tmpy / tmpz*power) * pow;

			}
			else if (direction >= 180 && direction <= 270) {
				Vec2 bullet_loc = Vec2(player[1]->getCharaSpr()->getPosition().x - player[1]->getCharaSpr()->getContentSize().width - bullet2->getContentSize().width, player[1]->getCharaSpr()->getPosition().y);
				float tmpx = loc.x - bullet_loc.x;
				float tmpy = loc.y - bullet_loc.y;
				float tmpz = sqrt(tmpx*tmpx + tmpy*tmpy);
				bullet2->setPosition(bullet_loc);

				vx = -abs(tmpx / tmpz*power) * pow;
				vy = abs(tmpy / tmpz*power) * pow;
			}
			else if (direction < 0) {

				Vec2 bullet_loc = Vec2(player[1]->getCharaSpr()->getPosition().x + player[1]->getCharaSpr()->getContentSize().width + bullet2->getContentSize().width, player[1]->getCharaSpr()->getPosition().y);
				float tmpx = loc.x - bullet_loc.x;
				float tmpy = loc.y - bullet_loc.y;
				float tmpz = sqrt(tmpx*tmpx + tmpy*tmpy);

				bullet2->setPosition(bullet_loc);
				vx = abs(tmpx / tmpz*power) * pow;
				vy = abs(tmpy / tmpz*power) * pow;
			}


			bullet2->getPhysicsBody()->setVelocity(Vec2(vx, vy));
			bullet2->getPhysicsBody()->setContactTestBitmask(1);
		}
	}

}

void Games::damage(int damage, int player)
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
	else if (player == 1){
		if (hp2->getPercentage() + damage > 0 && hp2->getPercentage() + damage <= 100) {
			hp2->setPercentage(hp2->getPercentage() + damage);
		}
		else if (hp2->getPercentage() + damage <= 0) {
			hp2->setPercentage(0);
			Director::getInstance()->replaceScene(End::createScene());
		}
		else {
			hp2->setPercentage(100);
		}
		// 实现血量渐渐变化
		auto updateHP = ProgressTo::create(0.2, (hp2->getPercentage() + damage));
		hp2->runAction(updateHP);
	}


}

void Games::update(float dt){
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_A) == false && isKeyPressed(EventKeyboard::KeyCode::KEY_D) == false)
	{
		player[0]->getCharaSpr()->stopAllActions();
	}

	if (isKeyPressed(EventKeyboard::KeyCode::KEY_J) == false && isKeyPressed(EventKeyboard::KeyCode::KEY_L) == false)
	{
		player[1]->getCharaSpr()->stopAllActions();
	}
}
