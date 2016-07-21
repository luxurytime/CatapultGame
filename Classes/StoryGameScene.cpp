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




	return true;
}
