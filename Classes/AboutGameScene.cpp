#include "AboutGameScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* AboutGame::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = AboutGame::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool AboutGame::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	Sprite* background = Sprite::create("guide.png");
	background->setScale(1.05);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object


	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Guide", "fonts/STHUPO.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);


	// add title
	auto label1 = LabelTTF::create("Menu and MenuItem", "Marker Felt.ttf", 32);
	label1->setPosition(visibleSize.width / 2, 17 * visibleSize.height / 20);

	//this->addChild(label1, 1);

	auto label2 = LabelTTF::create("Back", "STHUPO.ttf", 48);
	auto menuItem = MenuItemLabel::create(label2);
	auto menu = Menu::create(menuItem, nullptr);
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	});
	menu->setPosition(Vec2::ZERO);
	menuItem->setPosition(50, 50);
	addChild(menu, 1);

	return true;
}

