#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "StoryScene.h"
#include "SaveManegerScene.h"
#include "EndScene.h"
#include "AboutGameScene.h"

#include <iostream>

using namespace CocosDenshion;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm14.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("effect2.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("effect3.mp3");
	//SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.2);
	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm14.mp3", true);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	menuRect[0] = Rect::Rect(605, 236, 132, 30);
	menuRect[1] = Rect::Rect(621, 203, 99, 30);
	menuRect[2] = Rect::Rect(583, 165, 180, 31);
	menuRect[3] = Rect::Rect(567, 129, 214, 35);
	menuRect[4] = Rect::Rect(570, 63, 210, 31);


	starPos[0] = Vec2::Vec2(586, 252);
	starPos[1] = Vec2::Vec2(601, 218);
	starPos[2] = Vec2::Vec2(565, 185);
	starPos[3] = Vec2::Vec2(550, 147);
	starPos[4] = Vec2::Vec2(555, 80);

	starPos2[0] = Vec2::Vec2(757, 252);
	starPos2[1] = Vec2::Vec2(738, 218);
	starPos2[2] = Vec2::Vec2(778, 185);
	starPos2[3] = Vec2::Vec2(800, 147);
	starPos2[4] = Vec2::Vec2(795, 80);

	Sprite* background = Sprite::create("BGP_2.png");
	//background->setScale(0.9);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);

	Sprite* act = Sprite::create("B_ALL2.png");
	act->setPosition(visibleSize.width*0.16, visibleSize.height*0.71);
	addChild(act, 1);

	auto texture = Director::getInstance()->getTextureCache()->addImage("B_ALL2.png");
	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 200, 200)));
	Vector<SpriteFrame*> walk;
	walk.reserve(8);
	for (int i = 0; i < 7; i++) {
		walk.pushBack(SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(200 * i, 0, 200, 200))));
	}
	//walk.pushBack(frame0);

	auto animate = Animate::create(Animation::createWithSpriteFrames(walk, 0.07f));
	act->runAction(RepeatForever::create(animate));

	ParticleSnow* ps = ParticleSnow::createWithTotalParticles(10000);
	ps->setSpeed(180.0);
	ps->setEmissionRate(20.0);
	ps->setScale(1);
	ps->setRotation(90);
	ps->setPosition(visibleSize.width, visibleSize.height / 2);
	addChild(ps, 2);

	for (int i = 0; i < 5; i++)
	{
		star[i] = Sprite::create("1112.png");
		star[i]->setScale(0.15);
		star[i]->setPosition(starPos[i]);
		addChild(star[i], 2);
		star[i]->setOpacity(0);

		star2[i] = Sprite::create("1112.png");
		star2[i]->setScale(0.15);
		star2[i]->setPosition(starPos2[i]);
		addChild(star2[i], 2);
		star2[i]->setOpacity(0);
	}

	isBgm = true;

	/////////////////////music control
	menuItem1 = MenuItemImage::create("on2.png", "off2.png");
	//auto menuItem = MenuItemLabel::create(label0);
	
	menuItem1->setCallback([&](cocos2d::Ref *sender) {
		if (isBgm)
		{
			SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
			menuItem1->selected();
			isBgm = false;
		}
		else
		{
			SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
			menuItem1->unselected();
			isBgm = true;
		}
	});
	
	menuItem1->setScale(0.25);
	menuItem1->setAnchorPoint(Vec2(1, 1));
	menuItem1->setPosition(visibleSize.width, visibleSize.height);
	auto menu = Menu::create(menuItem1, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 1);
	////////////////////////////////

	//startMenuItem = MenuItemImage::create("button.png", "button.png", CC_CALLBACK_1(HelloWorld::onStart, this));
	//startMenuItem->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//auto start = Menu::create(startMenuItem, NULL);
	//start->setPosition(Point::ZERO);
	//addChild(start, 1);

	//auto listener = EventListenerMouse::create();
	//listener->onMouseMove = CC_CALLBACK_1(HelloWorld::onMouseMove, this);
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	// add title

	/*auto label = LabelTTF::create("FUCKER", "STHUPO.ttf", 100);
	label->setColor(Color3B::RED);
	label->setPosition(visibleSize.width*0.7, visibleSize.height*0.7);
	addChild(label);*/
	//auto menuItem = MenuItemLabel::create(label);
	//auto menu = Menu::create(menuItem, nullptr);
	//menu->setPosition(Vec2::ZERO);
	//menuItem->setPosition(visibleSize.width*0.9, 17 * visibleSize.height / 20);
	//addChild(menu, 1);

	// this is for Menu section of the Programmers Guide
	// creating a Menu from a Vector of items
	//Vector<MenuItem*> MenuItems;

	//// first item
	//auto label1 = LabelTTF::create("BattleMode", "STHUPO.ttf", 30);
	//auto item1 = MenuItemLabel::create(label1);
	//item1->setPosition(visibleSize.width*0.7, visibleSize.height*0.4);
	//item1->setCallback([&](cocos2d::Ref *sender) {
	//	Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, Select::createScene()));
	//});
	//MenuItems.pushBack(item1);

	//// second item
	//auto label2 = LabelTTF::create("StoryMode", "STHUPO.ttf", 30);
	//auto item2 = MenuItemLabel::create(label2);
	//item2->setPosition(visibleSize.width*0.7, visibleSize.height*0.32);
	//item2->setCallback([&](cocos2d::Ref *sender) {
	//	Director::getInstance()->replaceScene(Story::createScene());
	//});
	//MenuItems.pushBack(item2);

	//// third item
	//auto label3 = LabelTTF::create("Save Maneger", "STHUPO.ttf", 30);
	//auto item3 = MenuItemLabel::create(label3);
	//item3->setPosition(visibleSize.width*0.7, visibleSize.height*0.24);
	//item3->setCallback([&](cocos2d::Ref *sender) {
	//	Director::getInstance()->replaceScene(SaveManeger::createScene());
	//});
	//MenuItems.pushBack(item3);

	//// fourth item
	//auto label4 = LabelTTF::create("About Game", "STHUPO.ttf", 30);
	//auto item4 = MenuItemLabel::create(label4);
	//item4->setPosition(visibleSize.width*0.7, visibleSize.height*0.16);
	//item4->setCallback([&](cocos2d::Ref *sender) {
	//	Director::getInstance()->replaceScene(AboutGame::createScene());
	//});
	//MenuItems.pushBack(item4);

	//// now create the menu from the vector of MenuItems
	//auto menuExample = Menu::createWithArray(MenuItems);
	//menuExample->setPosition(Vec2::ZERO);
	//addChild(menuExample, 1);

	mode_sel = false;

	modeSel = Sprite::create("Button/Button_f2.png");
	modeSel->setScale(0.8);
	modeSel->setPosition(visibleSize.width*0.7, visibleSize.height*0.5 + 700);
	addChild(modeSel, 3);

	mode1 = MenuItemImage::create("Button/Button_1.png", "Button/Button_1.png", CC_CALLBACK_1(HelloWorld::onVS, this));
	mode1->setScale(0.4);
	mode1->setPosition(visibleSize.width*0.675, visibleSize.height*0.38 + 700);
	auto mode1m = Menu::create(mode1, NULL);
	mode1m->setPosition(Point::ZERO);
	addChild(mode1m, 4);

	mode2 = MenuItemImage::create("Button/Button_3.png", "Button/Button_3.png", CC_CALLBACK_1(HelloWorld::onStage, this));
	mode2->setScale(0.4);
	mode2->setPosition(visibleSize.width*0.675, visibleSize.height*0.25 + 700);
	auto mode2m = Menu::create(mode2, NULL);
	mode2m->setPosition(Point::ZERO);
	addChild(mode2m, 4);

	bac = MenuItemImage::create("Button/Button_2.png", "Button/Button_2.png", CC_CALLBACK_1(HelloWorld::onUp, this));
	bac->setScale(0.4);
	bac->setPosition(visibleSize.width*0.675, visibleSize.height*0.12 + 840);
	auto bacm = Menu::create(bac, NULL);
	bacm->setPosition(Point::ZERO);
	addChild(bacm, 4);

	auto listener = EventListenerMouse::create();
	listener->onMouseMove = CC_CALLBACK_1(HelloWorld::onMouseMove, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto listener2 = EventListenerTouchOneByOne::create();

	listener2->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener2->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);


	return true;
}

void HelloWorld::onEnter()
{
	Layer::onEnter();
	if (isBgm)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm14.mp3", true);
	}
	if (isBgm == false)
	{
		menuItem1->selected();
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
}

bool HelloWorld::onTouchBegan(Touch *touch, cocos2d::Event *event)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (currentMenu == 0)
	{
		MoveTo* mt1 = MoveTo::create(1.5f, Vec2(visibleSize.width*0.7, visibleSize.height*0.5+180));
		EaseElasticOut* eo1 = EaseElasticOut::create(mt1);

		MoveTo* mt2 = MoveTo::create(1.5f, Vec2(visibleSize.width*0.675, visibleSize.height*0.38+100));
		EaseElasticOut* eo2 = EaseElasticOut::create(mt2);

		MoveTo* mt3 = MoveTo::create(1.5f, Vec2(visibleSize.width*0.675, visibleSize.height*0.25+100));
		EaseElasticOut* eo3 = EaseElasticOut::create(mt3);

		MoveTo* mt4 = MoveTo::create(1.5f, Vec2(visibleSize.width*0.675, visibleSize.height*0.12 + 100));
		EaseElasticOut* eo4 = EaseElasticOut::create(mt4);

		modeSel->runAction(eo1);
		mode1->runAction(eo2);
		mode2->runAction(eo3);
		bac->runAction(eo4);

		SimpleAudioEngine::sharedEngine()->playEffect("effect2.mp3");

		mode_sel = true;
	}
	else if (currentMenu == 1)
	{
		Director::getInstance()->replaceScene(TransitionFade::create(0.8f, AboutGame::createScene()));
		
	}
	if (mode_sel == true)
	{
		startPos = touch->getLocation().y;
	}

	return true;
}

void HelloWorld::onTouchEnded(Touch *touch, cocos2d::Event *event){
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (mode_sel == true)
	{
		if (touch->getLocation().y - startPos > 50)
		{
			MoveTo* mt1 = MoveTo::create(1.5f, Vec2(visibleSize.width*0.7, visibleSize.height*0.5+700));
			EaseElasticIn* eo1 = EaseElasticIn::create(mt1);

			MoveTo* mt2 = MoveTo::create(1.5f, Vec2(visibleSize.width*0.675, visibleSize.height*0.38+700));
			EaseElasticIn* eo2 = EaseElasticIn::create(mt2);

			MoveTo* mt3 = MoveTo::create(1.5f, Vec2(visibleSize.width*0.675, visibleSize.height*0.25+700));
			EaseElasticIn* eo3 = EaseElasticIn::create(mt3);

			MoveTo* mt4 = MoveTo::create(1.5f, Vec2(visibleSize.width*0.675, visibleSize.height*0.12 + 700));
			EaseElasticIn* eo4 = EaseElasticIn::create(mt4);

			modeSel->runAction(eo1);
			mode1->runAction(eo2);
			mode2->runAction(eo3);
			bac->runAction(eo4);

			SimpleAudioEngine::sharedEngine()->playEffect("effect3.mp3");

			mode_sel = false;
		}
	}
}

void HelloWorld::onUp(Ref* ref)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	MoveTo* mt1 = MoveTo::create(1.5f, Vec2(visibleSize.width*0.7, visibleSize.height*0.5 + 700));
	EaseElasticIn* eo1 = EaseElasticIn::create(mt1);

	MoveTo* mt2 = MoveTo::create(1.5f, Vec2(visibleSize.width*0.675, visibleSize.height*0.38 + 700));
	EaseElasticIn* eo2 = EaseElasticIn::create(mt2);

	MoveTo* mt3 = MoveTo::create(1.5f, Vec2(visibleSize.width*0.675, visibleSize.height*0.25 + 700));
	EaseElasticIn* eo3 = EaseElasticIn::create(mt3);

	MoveTo* mt4 = MoveTo::create(1.5f, Vec2(visibleSize.width*0.675, visibleSize.height*0.12 + 700));
	EaseElasticIn* eo4 = EaseElasticIn::create(mt4);

	modeSel->runAction(eo1);
	mode1->runAction(eo2);
	mode2->runAction(eo3);
	bac->runAction(eo4);

	SimpleAudioEngine::sharedEngine()->playEffect("effect3.mp3");

	mode_sel = false;
}

void HelloWorld::onVS(Ref* ref)
{
	auto scene = Select::createScene();
	Select* temp = Select::create();
	temp->isBgm = isBgm;
	scene->addChild(temp);
	Director::getInstance()->replaceScene(TransitionFade::create(0.8f, scene));
}

void HelloWorld::onStage(Ref* ref)
{
	auto scene = Story::createScene();
	Story* temp = Story::create();
	temp->isBgm = isBgm;
	scene->addChild(temp);
	Director::getInstance()->replaceScene(TransitionFade::create(0.8f, scene));
	//Director::getInstance()->replaceScene(TransitionFade::create(0.8f, Story::createScene()));
}

void HelloWorld::onMouseMove(Event* event) {
	EventMouse* e = (EventMouse*)event;
	CCPoint mousePosition = CCPoint(e->getCursorX(), e->getCursorY());

	//auto block1 = startMenuItem->getBoundingBox();
	if (menuRect[0].containsPoint(mousePosition)) largerItem(0);
	else if (menuRect[1].containsPoint(mousePosition)) largerItem(1);
	else if (menuRect[2].containsPoint(mousePosition)) largerItem(2);
	else if (menuRect[3].containsPoint(mousePosition)) largerItem(3);
	else if (menuRect[4].containsPoint(mousePosition)) largerItem(4);
	else largerItem(5);
}

void HelloWorld::onStart(Ref* ref) {
	Director::getInstance()->replaceScene(CCTransitionPageTurn::create(1.0f, Select::createScene(), true));
}

void HelloWorld::largerItem(int a) {
	currentMenu = a;
	for (int i = 0; i < 5; i++)
	{
		star[i]->setOpacity(0);
		star2[i]->setOpacity(0);
	}

	if (a != 5)
	{
		star[a]->setOpacity(255);
		star2[a]->setOpacity(255);
	}
}
