#include "SelectScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "HelloWorldScene.h"
#include "MapSelectScene.h"

using namespace CocosDenshion;

float posX[4] = { 400, 400, 900, 900 };
float posY[4] = { 200, 300, 200, 300 };

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

	Sprite* background = Sprite::create("background2.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);

	charac[0] = Sprite::create("headphoto_2.png");
	charac[1] = Sprite::create("headpphoto_2.png");
	charac[2] = Sprite::create("headphoto_2.png");
	charac[3] = Sprite::create("headpphoto_2.png");

	for (int i = 0; i < 4; i++)
	{
		charac[i]->setScale(1.0);
		charac[i]->setPosition(posX[i], posY[i]);
		addChild(charac[i], 1);
	}

	bigC[0] = Sprite::create("headphoto_2.png");
	bigC[1] = Sprite::create("headpphoto_2.png");
	bigC[2] = Sprite::create("headphoto_2.png");
	bigC[3] = Sprite::create("headpphoto_2.png");

	for (int i = 0; i < 2; i++)
	{
		bigC[i]->setPosition(200, visibleSize.height / 2);
		bigC[i]->setScale(2.0);
		addChild(bigC[i], 1);
		bigC[i]->setOpacity(0);
	}

	for (int i = 2; i < 4; i++)
	{
		bigC[i]->setPosition(700, visibleSize.height / 2);
		addChild(bigC[i], 1);
		bigC[i]->setOpacity(0);
	}















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


	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(Select::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void Select::onStart(Ref* ref) {
	auto scene = Games::createScene();
	//Games *temp = Games::create();
	//temp->setPlayTag(0, player1);
	//temp->setPlayTag(1, player2);
	//scene->addChild(temp);
	CCDirector::sharedDirector()->replaceScene(TransitionFade::create(1.5f, scene));
}

bool Select::onTouchBegan(Touch *touch, cocos2d::Event *event)
{
	/*for (int i = 0; i < 4; i++)
	{
		bigC[i]->setOpacity(0);
	}*/

	auto location = touch->getLocation();
	int locX = location.x;
	int locY = location.y;
	//log("%d", (locY + 50) / 100);
	if ((locX + 50) / 100 == 4 && (locY + 50) / 100 - 1 >= 1 && (locY + 50) / 100 - 1 <= 2)
	{
		for (int i = 0; i < 2; i++)
		{
			bigC[i]->setOpacity(0);
		}
		bigC[(locY + 50) / 100 - 1-1]->setOpacity(255);
		player1 = (locY + 50) / 100 - 1;
	}
	else if ((locX + 50) / 100 == 9 && (locY + 50) / 100 - 1 >= 1 && (locY + 50) / 100 - 1 <= 2)
	{
		for (int i = 2; i < 4; i++)
		{
			bigC[i]->setOpacity(0);
		}
		bigC[(locY + 50) / 100 - 1+1]->setOpacity(255);
		player2 = (locY + 50) / 100 - 1;
	}



	return true;
}
