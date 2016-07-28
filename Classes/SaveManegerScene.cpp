#include "SaveManegerScene.h"
#include "SimpleAudioEngine.h"
#include "StoryGameScene.h"
#include "HelloWorldScene.h"
#include "GameScene.h"

using namespace CocosDenshion;

USING_NS_CC;

Scene* SaveManeger::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SaveManeger::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SaveManeger::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	Sprite* background = Sprite::create("savescene.png");
	background->setScale(1.05);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);

	Sprite* sback = Sprite::create("config.png");
	sback->setScale(2);
	sback->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(sback, 1);
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object


	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	//auto label = Label::createWithTTF("SaveManegerScene", "fonts/Marker Felt.ttf", 24);

	//// position the label on the center of the screen
	//label->setPosition(Vec2(origin.x + visibleSize.width / 2,
	//	origin.y + visibleSize.height - label->getContentSize().height));

	//// add the label as a child to this layer
	//this->addChild(label, 1);

	auto label0 = LabelTTF::create("Back", "Marker Felt.ttf", 48);
	auto menuItem = MenuItemLabel::create(label0);
	auto menu = Menu::create(menuItem, nullptr);
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	});
	menu->setPosition(Vec2::ZERO);
	menuItem->setPosition(visibleSize.width / 12, 1 * visibleSize.height / 2);
	addChild(menu, 1);

	bgmSel = false;
	effSel = false;

	bgm = MenuItemImage::create("on.png", "off.png", CC_CALLBACK_1(SaveManeger::onBgm, this));
	bgm->setScale(2);
	bgm->setPosition(500, 300);
	auto bgmm = Menu::create(bgm, NULL);
	bgmm->setPosition(Point::ZERO);
	addChild(bgmm, 2);

	eff = MenuItemImage::create("on.png", "off.png", CC_CALLBACK_1(SaveManeger::onEff, this));
	eff->setScale(2);
	eff->setPosition(500, 240);
	auto effm = Menu::create(eff, NULL);
	effm->setPosition(Point::ZERO);
	addChild(effm, 2);

	// this is for Menu section of the Programmers Guide
	// creating a Menu from a Vector of items
	//Vector<MenuItem*> MenuItems;

	// first item
	//auto label1 = LabelTTF::create("save1", "Marker Felt.ttf", 32);
	//auto item1 = MenuItemLabel::create(label1);
	//item1->setPosition(visibleSize.width / 2, 13 * visibleSize.height / 20);
	//item1->setCallback([&](cocos2d::Ref *sender) {
	//	Director::getInstance()->replaceScene(Games::createScene());
	//});
	//MenuItems.pushBack(item1);

	//// second item
	//auto label2 = LabelTTF::create("save2", "Marker Felt.ttf", 32);
	//auto item2 = MenuItemLabel::create(label2);
	//item2->setPosition(visibleSize.width / 2, 10 * visibleSize.height / 20);
	//item2->setCallback([&](cocos2d::Ref *sender) {
	//	Director::getInstance()->replaceScene(Games::createScene());

	//});
	//MenuItems.pushBack(item2);

	//// third item
	//auto label3 = LabelTTF::create("save3", "Marker Felt.ttf", 32);
	//auto item3 = MenuItemLabel::create(label3);
	//item3->setPosition(visibleSize.width / 2, 7 * visibleSize.height / 20);
	//item3->setCallback([&](cocos2d::Ref *sender) {
	//	Director::getInstance()->replaceScene(Games::createScene());

	//});
	//MenuItems.pushBack(item3);

	//// fourth item
	//auto label4 = LabelTTF::create("save4", "Marker Felt.ttf", 32);
	//auto item4 = MenuItemLabel::create(label4);
	//item4->setPosition(visibleSize.width / 2, 4 * visibleSize.height / 20);
	//item4->setCallback([&](cocos2d::Ref *sender) {
	//	Director::getInstance()->replaceScene(Games::createScene());

	//});
	//MenuItems.pushBack(item4);

	//// now create the menu from the vector of MenuItems
	//auto menuExample = Menu::createWithArray(MenuItems);
	//menuExample->setPosition(Vec2::ZERO);
	//addChild(menuExample, 2);


	return true;
}

void SaveManeger::onBgm(Ref* ref)
{
	if (bgmSel)
	{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		bgm->unselected();
		bgmSel = false;
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		bgm->selected();
		bgmSel = true;
	}
}

void SaveManeger::onEff(Ref* ref)
{
	if (effSel)
	{
		eff->unselected();
		effSel = false;
	}
	else
	{
		eff->selected();
		effSel = true;
	}
}
