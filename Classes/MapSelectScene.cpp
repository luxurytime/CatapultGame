#include "MapSelectScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "HelloWorldScene.h"

using namespace CocosDenshion;


USING_NS_CC;

Scene* MapSelect::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MapSelect::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool MapSelect::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = Sprite::create("background3.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);




	auto label0 = LabelTTF::create("back", "Marker Felt.ttf", 48);
	auto menuItem = MenuItemLabel::create(label0);
	auto menu = Menu::create(menuItem, nullptr);
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	});
	menu->setPosition(Vec2::ZERO);
	menuItem->setPosition(visibleSize.width / 12, 1 * visibleSize.height / 2);
	addChild(menu, 1);



	// this is for Menu section of the Programmers Guide
	// creating a Menu from a Vector of items
	Vector<MenuItem*> MenuItems;

	// first item
	auto label1 = LabelTTF::create("Map 1", "arial.ttf", 32);
	label1->setColor(Color3B(0, 0, 0));
	auto item1 = MenuItemLabel::create(label1);
	item1->setPosition(visibleSize.width / 2, 13 * visibleSize.height / 20);
	item1->setCallback([&](cocos2d::Ref *sender) {
		//Director::getInstance()->replaceScene(Games::createScene());
	});
	MenuItems.pushBack(item1);

	// second item
	auto label2 = LabelTTF::create("Map 2", " arial.ttf", 32);
	label2->setColor(Color3B(0, 0, 0));
	auto item2 = MenuItemLabel::create(label2);
	item2->setPosition(visibleSize.width / 2, 10 * visibleSize.height / 20);
	item2->setCallback([&](cocos2d::Ref *sender) {
		//Director::getInstance()->replaceScene(Games::createScene());

	});
	MenuItems.pushBack(item2);

	// third item
	auto label3 = LabelTTF::create("Map 3", "arial.ttf", 32);
	auto item3 = MenuItemLabel::create(label3);
	label3->setColor(Color3B(0, 0, 0));
	item3->setPosition(visibleSize.width / 2, 7 * visibleSize.height / 20);
	item3->setCallback([&](cocos2d::Ref *sender) {
		//Director::getInstance()->replaceScene(Games::createScene());

	});
	MenuItems.pushBack(item3);

	// fourth item
	auto label4 = LabelTTF::create("Map 4", "arial.ttf", 32);
	label4->setColor(Color3B(0, 0, 0));
	auto item4 = MenuItemLabel::create(label4);
	item4->setPosition(visibleSize.width / 2, 4 * visibleSize.height / 20);
	item4->setCallback([&](cocos2d::Ref *sender) {
		//Director::getInstance()->replaceScene(Games::createScene());

	});
	MenuItems.pushBack(item4);

	// now create the menu from the vector of MenuItems
	auto menuExample = Menu::createWithArray(MenuItems);
	menuExample->setPosition(Vec2::ZERO);
	addChild(menuExample, 2);


	return true;
}

void MapSelect::onStart(Ref* ref) {
	//Director::getInstance()->replaceScene(CCTransitionProgressOutIn::create(1.0f, Games::createScene()));
}
