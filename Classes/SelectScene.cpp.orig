#include "SelectScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "HelloWorldScene.h"
#include "MapSelectScene.h"

using namespace CocosDenshion;


USING_NS_CC;

Scene* Select::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Select::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Select::init()
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

	MenuItemImage* startMenuItem = MenuItemImage::create("button.png", "button.png", CC_CALLBACK_1(Select::onStart, this));
	startMenuItem->setPosition(visibleSize.width / 2, visibleSize.height / 5);
	auto start = Menu::create(startMenuItem, NULL);
	start->setPosition(Point::ZERO);
	addChild(start, 1);


	auto label0 = LabelTTF::create("back", "Marker Felt.ttf", 48);
	auto menuItem = MenuItemLabel::create(label0);
	auto menu = Menu::create(menuItem, nullptr);
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	});
	menu->setPosition(Vec2::ZERO);
	menuItem->setPosition(visibleSize.width / 12, 1 * visibleSize.height / 2);
	addChild(menu, 1);



	return true;
}

void Select::onStart(Ref* ref) {
	Director::getInstance()->replaceScene(CCTransitionProgressOutIn::create(1.0f, MapSelect::createScene()));
}

