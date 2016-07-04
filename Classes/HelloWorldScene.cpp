#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "SelectScene.h"

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
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = Sprite::create("background.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);

	startMenuItem = MenuItemImage::create("button.png", "button.png", CC_CALLBACK_1(HelloWorld::onStart, this));
	startMenuItem->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	auto start = Menu::create(startMenuItem, NULL);
	start->setPosition(Point::ZERO);
	addChild(start, 1);

	auto listener = EventListenerMouse::create();
	listener->onMouseMove = CC_CALLBACK_1(HelloWorld::onMouseMove, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
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
