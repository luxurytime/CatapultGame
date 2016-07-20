#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "StoryScene.h"
#include "SaveManegerScene.h"
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
    if ( !Layer::init() )
    {
        return false;
    }
    
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm.mp3");
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3", true);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = Sprite::create("background.png");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);

	//startMenuItem = MenuItemImage::create("button.png", "button.png", CC_CALLBACK_1(HelloWorld::onStart, this));
	//startMenuItem->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//auto start = Menu::create(startMenuItem, NULL);
	//start->setPosition(Point::ZERO);
	//addChild(start, 1);

	//auto listener = EventListenerMouse::create();
	//listener->onMouseMove = CC_CALLBACK_1(HelloWorld::onMouseMove, this);
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	// add title

	auto label = LabelTTF::create("MainMenu", "STHUPO.ttf", 48);
	auto menuItem = MenuItemLabel::create(label);
	auto menu = Menu::create(menuItem, nullptr);
	menu->setPosition(Vec2::ZERO);
	menuItem->setPosition(visibleSize.width*0.9, 17 * visibleSize.height / 20);
	//addChild(menu, 1);

	// this is for Menu section of the Programmers Guide
	// creating a Menu from a Vector of items
	Vector<MenuItem*> MenuItems;

	// first item
	auto label1 = LabelTTF::create("BattleMode", "STHUPO.ttf", 36);
	auto item1 = MenuItemLabel::create(label1);
	item1->setPosition(visibleSize.width*0.5, 10 * visibleSize.height / 20);
	item1->setCallback([&](cocos2d::Ref *sender) {
		Director::getInstance()->replaceScene(Games::createScene());
	});
	MenuItems.pushBack(item1);

	// second item
	auto label2 = LabelTTF::create("StoryMode", "STHUPO.ttf", 36);
	auto item2 = MenuItemLabel::create(label2);
	item2->setPosition(visibleSize.width*0.5, 8 * visibleSize.height / 20);
	item2->setCallback([&](cocos2d::Ref *sender) {
		Director::getInstance()->replaceScene(Story::createScene());
	});
	MenuItems.pushBack(item2);

	// third item
	auto label3 = LabelTTF::create("Save Maneger", "STHUPO.ttf", 36);
	auto item3 = MenuItemLabel::create(label3);
	item3->setPosition(visibleSize.width*0.5, 6 * visibleSize.height / 20);
	item3->setCallback([&](cocos2d::Ref *sender) {
		Director::getInstance()->replaceScene(SaveManeger::createScene());
	});
	MenuItems.pushBack(item3);

	// fourth item
	auto label4 = LabelTTF::create("About Game", "STHUPO.ttf", 36);
	auto item4 = MenuItemLabel::create(label4);
	item4->setPosition(visibleSize.width*0.5, 4 * visibleSize.height / 20);
	item4->setCallback([&](cocos2d::Ref *sender) {
		Director::getInstance()->replaceScene(AboutGame::createScene());
	});
	MenuItems.pushBack(item4);

	// now create the menu from the vector of MenuItems
	auto menuExample = Menu::createWithArray(MenuItems);
	menuExample->setPosition(Vec2::ZERO);
	addChild(menuExample, 2);


    return true;
}

void HelloWorld::onMouseMove(Event* event) {
	EventMouse* e = (EventMouse*)event;
	CCPoint mousePosition = CCPoint(e->getCursorX(), e->getCursorY() + 640);

	auto block1 = startMenuItem->getBoundingBox();
	if (block1.containsPoint(mousePosition)) largerItem(startMenuItem, 1);
	else largerItem(NULL, 0);
}

void HelloWorld::onStart(Ref* ref) {
	Director::getInstance()->replaceScene(CCTransitionPageTurn::create(1.0f, Select::createScene(), true));
}

void HelloWorld::largerItem(MenuItemImage* item, int i) {
	startMenuItem->setScale(1, 1);
	if (item) item->setScale(1.2, 1.2);
}
