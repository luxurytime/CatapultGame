#include "StoryGameScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"

using namespace CocosDenshion;


USING_NS_CC;

Scene* StoryGame::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

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

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = Sprite::create("background2.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);

	Sprite* player1 = Sprite::create("player.png");
	player1->setPosition(visibleSize.width / 4, visibleSize.height * 0.15);
	player1->setScale(0.1, 0.1);
	addChild(player1, 1);

	Sprite* arrow = Sprite::create("arrow.png");
	arrow->setPosition(visibleSize.width / 4 + 55, visibleSize.height * 0.15 + 70);
	arrow->setScale(0.5, 0.5);
	addChild(arrow, 1);

	Sprite* line = Sprite::create("line2.png");
	line->setPosition(visibleSize.width / 2 + 20, visibleSize.height * 0.35 + 30);
	line->setScale(0.65, 0.65);
	addChild(line, 1);

	Sprite* bomb = Sprite::create("bomb.png");
	bomb->setPosition(visibleSize.width / 2, visibleSize.height * 0.4 + 40);
	bomb->setScale(0.4, 0.4);
	addChild(bomb, 2);

	Sprite* life = Sprite::create("life.png");
	life->setPosition(100, visibleSize.height - 30);
	life->setScale(1.5, 1.5);
	addChild(life, 1);

	Sprite* lifep = Sprite::create("lp.png");
	lifep->setPosition(50, visibleSize.height - 30);
	lifep->setScale(0.2, 0.2);
	addChild(lifep, 2);


	auto label = LabelTTF::create("MainMenu", "Marker Felt.ttf", 48);
	auto menuItem = MenuItemLabel::create(label);
	auto menu = Menu::create(menuItem, nullptr);
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	});
	menu->setPosition(Vec2::ZERO);
	menuItem->setPosition(visibleSize.width / 2, 1 * visibleSize.height / 2);
	addChild(menu, 1);

	return true;
}
