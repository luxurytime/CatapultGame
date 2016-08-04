#include "StoryScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "StoryGameScene.h"

using namespace CocosDenshion;

USING_NS_CC;

float posSMX[3] = { 250, 480, 710 };
float posSMY[3] = { 300, 300, 300 };

int csNum = 3;

Scene* Story::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Story::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Story::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm13.mp3");
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm13.mp3", true);

	Sprite* background = Sprite::create("storyscene.png");
	background->setScale(1.05);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);

	selected = 0;

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object


	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	//auto label = Label::createWithTTF("StoryScene", "fonts/Marker Felt.ttf", 24);

	//// position the label on the center of the screen
	//label->setPosition(Vec2(origin.x + visibleSize.width / 2,
	//	origin.y + visibleSize.height - label->getContentSize().height));

	//// add the label as a child to this layer
	//this->addChild(label, 1);


	//auto label0 = LabelTTF::create("Back", "Marker Felt.ttf", 48);
	//auto menuItem = MenuItemLabel::create(label0);
	//auto menu = Menu::create(menuItem, nullptr);
	//menuItem->setCallback([&](cocos2d::Ref *sender) {
	//	Director::getInstance()->replaceScene(HelloWorld::createScene());
	//});
	//menu->setPosition(Vec2::ZERO);
	//menuItem->setPosition(visibleSize.width / 12, 1 * visibleSize.height / 2);
	//addChild(menu, 1);



	//// this is for Menu section of the Programmers Guide
	//// creating a Menu from a Vector of items
	//Vector<MenuItem*> MenuItems;

	//// first item
	//auto label1 = LabelTTF::create("Level 1", "Marker Felt.ttf", 32);
	//auto item1 = MenuItemLabel::create(label1);
	//item1->setPosition(visibleSize.width / 2, 13 * visibleSize.height / 20);
	//item1->setCallback([&](cocos2d::Ref *sender) {
	//	Director::getInstance()->replaceScene(StoryGame::createScene());
	//});
	//MenuItems.pushBack(item1);

	//// second item
	//auto label2 = LabelTTF::create("Level 2", "Marker Felt.ttf", 32);
	//auto item2 = MenuItemLabel::create(label2);
	//item2->setPosition(visibleSize.width / 2, 10 * visibleSize.height / 20);
	//item2->setCallback([&](cocos2d::Ref *sender) {
	//	Director::getInstance()->replaceScene(StoryGame::createScene());

	//});
	//MenuItems.pushBack(item2);

	//// third item
	//auto label3 = LabelTTF::create("Level 3", "Marker Felt.ttf", 32);
	//auto item3 = MenuItemLabel::create(label3);
	//item3->setPosition(visibleSize.width / 2, 7 * visibleSize.height / 20);
	//item3->setCallback([&](cocos2d::Ref *sender) {
	//	Director::getInstance()->replaceScene(StoryGame::createScene());

	//});
	//MenuItems.pushBack(item3);

	//// fourth item
	//auto label4 = LabelTTF::create("Level 4", "Marker Felt.ttf", 32);
	//auto item4 = MenuItemLabel::create(label4);
	//item4->setPosition(visibleSize.width / 2, 4 * visibleSize.height / 20);
	//item4->setCallback([&](cocos2d::Ref *sender) {
	//	Director::getInstance()->replaceScene(StoryGame::createScene());

	//});
	//MenuItems.pushBack(item4);

	//// now create the menu from the vector of MenuItems
	//auto menuExample = Menu::createWithArray(MenuItems);
	//menuExample->setPosition(Vec2::ZERO);
	//addChild(menuExample, 2);

	addChara();

	/*level[0] = Sprite::create("l1.png");
	level[1] = Sprite::create("l2.png");
	level[2] = Sprite::create("l3.png");
	level[3] = Sprite::create("l4.png");
	for (int i = 0; i < 4; i++)
	{
		level[i]->setAnchorPoint(Vec2(1, 1));
		level[i]->setPosition(visibleSize.width, visibleSize.height + 100);
		addChild(level[i], 2);
	}*/

	level[0] = MenuItemImage::create("l1.png", "l1.png", CC_CALLBACK_1(Story::onStart, this));
	level[0]->setAnchorPoint(Vec2(1, 1));
	level[0]->setPosition(visibleSize.width, visibleSize.height+100);
	auto level0m = Menu::create(level[0], NULL);
	level0m->setPosition(Point::ZERO);
	addChild(level0m, 1);

	level[1] = MenuItemImage::create("l2.png", "l2.png", CC_CALLBACK_1(Story::onStart, this));
	level[1]->setAnchorPoint(Vec2(1, 1));
	level[1]->setPosition(visibleSize.width, visibleSize.height + 100);
	auto level1m = Menu::create(level[1], NULL);
	level1m->setPosition(Point::ZERO);
	addChild(level1m, 1);

	level[2] = MenuItemImage::create("l3.png", "l3.png", CC_CALLBACK_1(Story::onStart, this));
	level[2]->setAnchorPoint(Vec2(1, 1));
	level[2]->setPosition(visibleSize.width, visibleSize.height + 100);
	auto level2m = Menu::create(level[2], NULL);
	level2m->setPosition(Point::ZERO);
	addChild(level2m, 1);

	level[3] = MenuItemImage::create("l4.png", "l4.png", CC_CALLBACK_1(Story::onStart, this));
	level[3]->setAnchorPoint(Vec2(1, 1));
	level[3]->setPosition(visibleSize.width, visibleSize.height + 100);
	auto level3m = Menu::create(level[3], NULL);
	level3m->setPosition(Point::ZERO);
	addChild(level3m, 1);

	levelMon[0] = Sprite::create("5.png");
	levelMon[1] = Sprite::create("6.png");
	levelMon[2] = Sprite::create("4.png");
	levelMon[3] = Sprite::create("1.png");

	for (int i = 0; i < 4; i++)
	{
		levelMon[i]->setAnchorPoint(Vec2(1, 1));
		levelMon[i]->setScale(0.32);
		levelMon[i]->setPosition(visibleSize.width, visibleSize.height*(0.2*(4 - i)) + 100);
		levelMon[i]->setOpacity(0);
		addChild(levelMon[i], 3);
	}


	MenuItemImage* label0 = MenuItemImage::create("Button2/Button_back.png", "Button2/Button_back.png");
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
	menuItem->setPosition(0, visibleSize.height);
	addChild(menu, 1);

	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(Story::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void Story::onEnter()
{
	Layer::onEnter();
	if (isBgm)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm13.mp3", true);
	}
	if (isBgm == false)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
}

void Story::onStart(Ref* ref)
{
	Director::sharedDirector()->replaceScene(TransitionFade::create(1.5f, StoryGame::createScene(pl, true)));
}

void Story::addChara()
{
	charac[0] = Sprite::create("CHA_1_1.png");
	charac[1] = Sprite::create("CHA_2_2.png");
	charac[2] = Sprite::create("CHA_3_1.png");

	for (int i = 0; i < csNum; i++) {
		charac[i]->setPosition(posSMX[i] + 500, posSMY[i]);
		charac[i]->setOpacity(0);
		charac[i]->setScale(0.5, 0.5);
		addChild(charac[i], 1);
	}

	DelayTime* dt = DelayTime::create(0.5f);
	FadeIn* fi = FadeIn::create(0.4f);
	MoveBy* mb = MoveBy::create(0.4f, Vec2(-500, 0));
	Spawn* sp = Spawn::create(fi, mb, NULL);

	DelayTime* dt2 = DelayTime::create(0.6f);
	FadeIn* fi2 = FadeIn::create(0.4f);
	MoveBy* mb2 = MoveBy::create(0.4f, Vec2(-500, 0));
	Spawn* sp2 = Spawn::create(fi2, mb2, NULL);

	DelayTime* dt3 = DelayTime::create(0.7f);
	FadeIn* fi3 = FadeIn::create(0.4f);
	MoveBy* mb3 = MoveBy::create(0.4f, Vec2(-500, 0));
	Spawn* sp3 = Spawn::create(fi3, mb3, NULL);

	current = 1;
	charac[current]->setScale(0.7, 0.7);

	charac[0]->runAction(Sequence::create(dt, sp, NULL));
	charac[1]->runAction(Sequence::create(dt2, sp2, NULL));
	charac[2]->runAction(Sequence::create(dt3, sp3, NULL));

	/*for (int i = 0; i < csNum; i++)
	{
	charac[i]->runAction(Sequence::create(dt, sp, NULL));
	}*/
}

void Story::flyAway()
{

	DelayTime* dt[3];

	dt[0] = DelayTime::create(0.0f);
	FadeOut* fo = FadeOut::create(0.4f);
	MoveBy* mb = MoveBy::create(0.4f, Vec2(-500, 0));
	Spawn* sp = Spawn::create(fo, mb, NULL);
	MoveTo* mt = MoveTo::create(0.0f, Vec2(posSMX[0] + 500, posSMY[0]));
	ScaleTo* st = ScaleTo::create(0.0f, 0.4);

	dt[1] = DelayTime::create(0.1f);
	FadeOut* fo2 = FadeOut::create(0.4f);
	MoveBy* mb2 = MoveBy::create(0.4f, Vec2(-500, 0));
	Spawn* sp2 = Spawn::create(fo2, mb2, NULL);
	MoveTo* mt2 = MoveTo::create(0.0f, Vec2(posSMX[1] + 500, posSMY[1]));
	ScaleTo* st2 = ScaleTo::create(0.0f, 0.8);

	dt[2] = DelayTime::create(0.2f);
	FadeOut* fo3 = FadeOut::create(0.4f);
	MoveBy* mb3 = MoveBy::create(0.4f, Vec2(-500, 0));
	Spawn* sp3 = Spawn::create(fo3, mb3, NULL);
	MoveTo* mt3 = MoveTo::create(0.0f, Vec2(posSMX[2] + 500, posSMY[2]));
	ScaleTo* st3 = ScaleTo::create(0.0f, 0.4);

	charac[0]->runAction(Sequence::create(dt[(csNum - 1 - current + (csNum - 1)) % csNum], sp, mt, st, NULL));
	charac[1]->runAction(Sequence::create(dt[(csNum - 1 - current + (csNum - 1) + 1) % csNum], sp2, mt2, st2, NULL));
	charac[2]->runAction(Sequence::create(dt[(csNum - 1 - current + (csNum - 1) + 2) % csNum], sp3, mt3, st3, NULL));
}

bool Story::onTouchBegan(Touch *touch, cocos2d::Event *event)
{

	auto location = touch->getLocation();
	int locX = location.x;
	int locY = location.y;
	if (locX >= 230 && locX <= 290 && locY >= 250 && locY <= 350)
	{

			MoveTo* mt = MoveTo::create(0.5f, Vec2(posSMX[1], posSMY[1]));
			EaseIn* mt_eo = EaseIn::create(mt, 3.0);
			ScaleTo* st = ScaleTo::create(0.5f, 0.7);
			charac[(current + (csNum - 1)) % csNum]->runAction(Spawn::create(mt_eo, st, NULL));

			MoveTo* mt2 = MoveTo::create(0.5f, Vec2(posSMX[2], posSMY[2]));
			ScaleTo* st2 = ScaleTo::create(0.5f, 0.5);
			charac[current]->runAction(Spawn::create(mt2, st2, NULL));

			FadeOut* fo = FadeOut::create(0.25f);
			MoveBy* mb = MoveBy::create(0.25f, Vec2(50, 0));
			Spawn* fm = Spawn::create(fo, mb, NULL);
			MoveTo* mt3 = MoveTo::create(0.01f, Vec2(posSMX[0] - 50, posSMY[0]));
			FadeIn* fi = FadeIn::create(0.25f);
			MoveBy* mb2 = MoveBy::create(0.25f, Vec2(50, 0));
			Spawn* fm2 = Spawn::create(fi, mb2, NULL);
			charac[(current + 1) % csNum]->runAction(Sequence::create(fm, mt3, fm2, NULL));

			current = (current + (csNum - 1)) % csNum;
	}
	else if (locX >= 670 && locX <= 730 && locY >= 250 && locY <= 350)
	{
			MoveTo* mt = MoveTo::create(0.5f, Vec2(posSMX[1], posSMY[1]));
			EaseIn* mt_eo = EaseIn::create(mt, 3.0);
			ScaleTo* st = ScaleTo::create(0.5f, 0.7);
			charac[(current + 1) % csNum]->runAction(Spawn::create(mt_eo, st, NULL));

			MoveTo* mt2 = MoveTo::create(0.5f, Vec2(posSMX[0], posSMY[0]));
			ScaleTo* st2 = ScaleTo::create(0.5f, 0.5);
			charac[current]->runAction(Spawn::create(mt2, st2, NULL));

			FadeOut* fo = FadeOut::create(0.25f);
			MoveBy* mb = MoveBy::create(0.25f, Vec2(-50, 0));
			Spawn* fm = Spawn::create(fo, mb, NULL);
			MoveTo* mt3 = MoveTo::create(0.01f, Vec2(posSMX[2] + 50, posSMY[2]));
			FadeIn* fi = FadeIn::create(0.25f);
			MoveBy* mb2 = MoveBy::create(0.25f, Vec2(-50, 0));
			Spawn* fm2 = Spawn::create(fi, mb2, NULL);
			charac[(current + (csNum - 1)) % csNum]->runAction(Sequence::create(fm, mt3, fm2, NULL));

			current = (current + 1) % csNum;
	}
	else if (locX >= 430 && locX <= 530 && locY >= 220 && locY <= 380)
	{
		if (selected == 0)
		{
			selected++;
			flyAway();

			if (current == 0)
			{
				p1 = Sprite::create("texture/1.png");
				pl = 0;
			}
			else if (current == 1)
			{
				p1 = Sprite::create("texture/2.png");
				pl = 1;
			}
			else if (current == 2)
			{
				p1 = Sprite::create("texture/3.png");
				pl = 2;
			}
			p1->setScale(0.7);
			p1->setOpacity(0);
			p1->setPosition(300, 300);
			addChild(p1, 2);

			DelayTime* dt = DelayTime::create(0.3f);
			FadeIn* fi = FadeIn::create(0.5f);
			MoveTo* mt = MoveTo::create(0.5f, Vec2(200, 300));
			p1->runAction(Sequence::create(dt, Spawn::create(fi, mt, NULL), NULL));

			levelDown();
		}
		else if (selected == 1)
		{
			selected++;
		}
		else if (selected == 2)
		{
			selected++;
		}

	}

	return true;
}

void Story::levelDown()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	for (int i = 3; i >= 0; i--)
	{
		DelayTime* dt = DelayTime::create(1.0f+(3-i)*0.2f);
		MoveTo* mt = MoveTo::create(0.4f, Vec2(visibleSize.width, visibleSize.height*(0.2*(4 - i)) + 50));
		level[i]->runAction(Sequence::create(dt, mt, NULL));
	}

	for (int i = 0; i < 4; i++)
	{
		DelayTime* dt = DelayTime::create(1.8f + i*0.15f);
		FadeIn* fi = FadeIn::create(0.7f);
		levelMon[i]->runAction(Sequence::create(dt, fi, NULL));
	}
}