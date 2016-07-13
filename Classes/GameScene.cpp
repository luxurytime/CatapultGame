#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"

using namespace CocosDenshion;


USING_NS_CC;

Scene* Games::createScene()
{
	// 'scene' is an autorelease object
	//auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Point(0, -98));

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

	//Sprite* player1 = Sprite::create("player.png");
	//player1->setPosition(visibleSize.width / 4, visibleSize.height * 0.15);
	//player1->setScale(0.1, 0.1);
	//addChild(player1, 1);

	//Sprite* player2 = Sprite::create("player.png");
	//player2->setPosition(visibleSize.width * 0.75, visibleSize.height * 0.15);
	//player2->setScale(0.1, 0.1);
	//addChild(player2, 1);

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

	//Sprite* life = Sprite::create("life.png");
	//life->setPosition(100, visibleSize.height - 30);
	//life->setScale(1.5, 1.5);
	//addChild(life, 1);

	//Sprite* lifep = Sprite::create("lp.png");
	//lifep->setPosition(50, visibleSize.height-30);
	//lifep->setScale(0.2, 0.2);
	//addChild(lifep, 2);

	//Sprite* life2 = Sprite::create("life.png");
	//life2->setPosition(visibleSize.width-100, visibleSize.height - 30);
	//life2->setScale(1.5, 1.5);
	//addChild(life2, 1);

	//Sprite* lifep2 = Sprite::create("lp.png");
	//lifep2->setPosition(visibleSize.width - 50, visibleSize.height - 30);
	//lifep2->setScale(0.2, 0.2);
	//addChild(lifep2, 2);

	//auto label = LabelTTF::create("MainMenu", "Marker Felt.ttf", 48);
	//auto menuItem = MenuItemLabel::create(label);
	//auto menu = Menu::create(menuItem, nullptr);
	//menuItem->setCallback([&](cocos2d::Ref *sender) {
	//	Director::getInstance()->replaceScene(HelloWorld::createScene());
	//});
	//menu->setPosition(Vec2::ZERO);
	//menuItem->setPosition(visibleSize.width / 2, 1 * visibleSize.height / 2);
	//addChild(menu, 1);




	player1 = addPlayer(origin.x + visibleSize.width / 4);
	player1->setTag(1);
	player2 = addPlayer(origin.x + visibleSize.width / 4 * 3);
	player2->setFlipX(true);
	player2->setTag(2);

	//preloadMusic();
	//playBgm();

	addEdge();
	addListener();
	getFrameAction();

	bullet1 = NULL;
	bullet2 = NULL;

	scheduleUpdate();
	
	return true;
}

void Games::preloadMusic() {
	// 预加载音乐
	auto audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("music/bgm.mp3");
	audio->preloadEffect("music/meet_stone.wav");
}

void Games::playBgm() {
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bgm.mp3", true);
}


Sprite* Games::addPlayer(int x){
	// 创建一张贴图, 从贴图中以像素单位切割，创建关键帧
	auto texture = Director::getInstance()->getTextureCache()->addImage("$lucia_forward.png");
	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(10, 10, 48, 81)));

	auto player = Sprite::createWithSpriteFrame(frame0);
	player->setPosition(Vec2(x, origin.y + player->getContentSize().height / 2));
	player->setPhysicsBody(PhysicsBody::createBox(player->getContentSize()));
	player->getPhysicsBody()->setContactTestBitmask(1);
	player->getPhysicsBody()->setDynamic(false);
	addChild(player, 3);

	return player;
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

void Games::addListener(){
	// 键盘事件
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Games::onKeyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	// 触碰事件
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Games::onConcactBegan, this);
	_eventDispatcher->addEventListenerWithFixedPriority(contactListener, 1);
}

void Games::getFrameAction(){
	// 走路
	auto texture = Director::getInstance()->getTextureCache()->addImage("$lucia_forward.png");
	walk.reserve(9);
	for (int i = 0; i < 8; i++) {
		auto frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(68 * i + 10, 10, 48, 81)));
		walk.pushBack(frame);
	}
	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(10, 10, 48, 81)));
	walk.pushBack(frame0);

	// 死亡动画
	auto texture2 = Director::getInstance()->getTextureCache()->addImage("$lucia_dead.png");
	dead.reserve(23);
	for (int i = 0; i < 22; i++) {
		auto frame = SpriteFrame::createWithTexture(texture2, CC_RECT_PIXELS_TO_POINTS(Rect(79 * i, 0, 79, 90)));
		dead.pushBack(frame);
	}
	dead.pushBack(frame0);
}



// 实现键盘回调
void Games::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	auto animation = Animation::createWithSpriteFrames(walk, 0.05f);
	auto animate = Animate::create(animation);
	MoveBy* move;
	int movedis = 20;
	switch (keyCode)
	{

	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		move = MoveBy::create(0.4, Point(-20, 0));
		player1->runAction(Spawn::create(animate, move, NULL));
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		move = MoveBy::create(0.4, Point(20, 0));
		player1->runAction(Spawn::create(animate, move, NULL));
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		bullet1fire();
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_J:
		move = MoveBy::create(0.4, Point(-20, 0));
		player2->runAction(Spawn::create(animate, move, NULL));
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_L:
		move = MoveBy::create(0.4, Point(20, 0));
		player2->runAction(Spawn::create(animate, move, NULL));
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_K:
		bullet2fire();
		break;

	default:
		break;
	}
}

void Games::bullet1fire(){
	if (bullet1 == NULL) {
		bullet1 = Sprite::create("bullet1.png");
		bullet1->setScale(0.5);
		bullet1->setTag(3);
		bullet1->setPosition(Vec2(player1->getPosition().x + player1->getContentSize().width / 2 + bullet1->getContentSize().width / 2, player1->getPosition().y));
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
		bullet2->setScale(0.5);
		bullet2->setTag(4);
		bullet2->setPosition(Vec2(player2->getPosition().x - player2->getContentSize().width / 2 - bullet2->getContentSize().width / 2, player2->getPosition().y));
		addChild(bullet2, 3);
		bullet2->setPhysicsBody(PhysicsBody::createCircle(bullet2->getContentSize().width / 2));
		bullet2->getPhysicsBody()->setVelocity(Vec2(-100, 0));
		bullet2->getPhysicsBody()->setContactTestBitmask(1);
		bullet2->getPhysicsBody()->setGravityEnable(false);
	}
}

void Games::update(float dt){
	if (bullet1 != NULL) {
		
	}
}

bool Games::onConcactBegan(PhysicsContact& contact) {
	Sprite* spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	Sprite* spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();
	int tagA = spriteA->getTag();
	int tagB = spriteB->getTag();

	/*
	各个物体的Tag：
	player1：1
	player2：2
	edge：0
	bullet1：3
	bullet2：4
	*/


	auto animate = Animate::create(Animation::createWithSpriteFrames(dead, 0.1f));

	if (tagA == 1 && tagB == 4) {
		bullet2->removeFromParent();
		bullet2 = NULL;
		player1->runAction(animate);
	} else if (tagA == 4 && tagB == 1) {
		bullet2->removeFromParent();
		bullet2 = NULL;
		player1->runAction(animate);
	}

	if (tagA == 2 && tagB == 3) {
		bullet1->removeFromParent();
		bullet1 = NULL;
		player2->runAction(animate);
	}
	else if (tagA == 3 && tagB == 2) {
		bullet1->removeFromParent();
		bullet1 = NULL;
		player2->runAction(animate);
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





	return true;
}
