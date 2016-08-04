#include "SelectScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "HelloWorldScene.h"
#include "MapSelectScene.h"

using namespace CocosDenshion;

float posMX[3] = { 300, 480, 660 };
float posMY[3] = { 300, 300, 300 };

int cNum = 3;

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

	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm13.mp3");
	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm13.mp3", true);

	Sprite* background = Sprite::create("back2.jpg");
	background->setScale(0.65);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);

	red = Sprite::create("p1.png");
	//red->setAnchorPoint(Vec2(0, 0));
	red->setScale(0.5);
	red->setOpacity(0);
	red->setPosition(100, 100);
	addChild(red, 3);

	blue = Sprite::create("p2.png");
	//blue->setAnchorPoint(Vec2(1, 0));
	blue->setScale(0.5);
	blue->setOpacity(0);
	blue->setPosition(860, 100);
	addChild(blue, 3);


	FadeIn* fi = FadeIn::create(0.5f);
	FadeOut* fo = FadeOut::create(0.5f);
	red->runAction(RepeatForever::create(Sequence::create(fi, fo, NULL)));

	selected = 0;

	addChara();


	/*charac[0] = Sprite::create("headphoto_2.png");
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

*/













	startMenuItem = MenuItemImage::create("Button2/Button_next.png", "Button2/Button_next.png", CC_CALLBACK_1(Select::onStart, this));
	startMenuItem->setScale(0.2);
	startMenuItem->setPosition(visibleSize.width / 2, visibleSize.height / 8);
	auto start = Menu::create(startMenuItem, NULL);
	start->setPosition(Point::ZERO);
	addChild(start, 1);
	startMenuItem->setOpacity(0);
	startMenuItem->setEnabled(false);


	MenuItemImage* label0 = MenuItemImage::create("Button2/Button_back.png", "Button2/Button_back.png");
	auto menuItem = MenuItemLabel::create(label0);
	auto menu = Menu::create(menuItem, nullptr);
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		if (selected == 0)
		{
			auto scene = HelloWorld::createScene();
			HelloWorld* temp = HelloWorld::create();
			temp->isBgm = isBgm;
			scene->addChild(temp);
			Director::getInstance()->replaceScene(scene);
		}
		else if (selected == 1)
		{
			flyAway();

			DelayTime* dt = DelayTime::create(0.0f);
			FadeOut* fi = FadeOut::create(0.5f);
			MoveTo* mt = MoveTo::create(0.5f, Vec2(0, 300));
			p1->runAction(Sequence::create(dt, Spawn::create(fi, mt, NULL), NULL));

			reAddChara();

			selected = 0;

			blue->stopAllActions();
			blue->setOpacity(0);

			FadeIn* fi2 = FadeIn::create(0.5f);
			FadeOut* fo = FadeOut::create(0.5f);
			red->runAction(RepeatForever::create(Sequence::create(fi2, fo, NULL)));

			ban = true;
		}
		else if (selected == 2)
		{
			flyAway();

			DelayTime* dt = DelayTime::create(0.6f);
			FadeOut* fi = FadeOut::create(0.5f);
			MoveTo* mt = MoveTo::create(0.5f, Vec2(960, 300));
			p2->runAction(Sequence::create(dt, Spawn::create(fi, mt, NULL), NULL));

			reAddChara();

			selected = 1;

			FadeIn* fi8 = FadeIn::create(0.5f);
			FadeOut* fo8 = FadeOut::create(0.5f);
			blue->runAction(RepeatForever::create(Sequence::create(fi8, fo8, NULL)));

			DelayTime* dt1 = DelayTime::create(0.0f);
			ScaleTo* fi1 = ScaleTo::create(0.5f, 0.5);
			MoveTo* mt1 = MoveTo::create(0.5f, Vec2(100, 300));
			p1->runAction(Sequence::create(dt1, Spawn::create(fi1, mt1, NULL), NULL));

			DelayTime* dt2 = DelayTime::create(0.0f);
			ScaleTo* fi2 = ScaleTo::create(0.5f, 0.5);
			MoveTo* mt2 = MoveTo::create(0.5f, Vec2(860, 300));
			p2->runAction(Sequence::create(dt2, Spawn::create(fi2, mt2, NULL), NULL));

			DelayTime* dt5 = DelayTime::create(0.0f);
			MoveTo* mt5 = MoveTo::create(0.5f, Vec2(100, 100));
			red->runAction(Sequence::create(dt5, mt5, NULL));

			DelayTime* dt6 = DelayTime::create(0.0f);
			MoveTo* mt6 = MoveTo::create(0.5f, Vec2(860, 100));
			blue->runAction(Sequence::create(dt6, mt6, NULL));

			DelayTime* dt4 = DelayTime::create(0.0f);
			ScaleTo* st4 = ScaleTo::create(0.4f, 0.0);
			startMenuItem2->runAction(Sequence::create(dt4, st4, NULL));

			ban = true;
		}
		
	});
	menu->setPosition(Vec2::ZERO);
	menuItem->setScale(0.15);
	menuItem->setAnchorPoint(Vec2(0, 1));
	menuItem->setPosition(0, visibleSize.height);
	addChild(menu, 1);


	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(Select::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();

	ban = true;

	return true;
}

void Select::onEnter()
{
	Layer::onEnter();
	if (isBgm)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm13.mp3", true);
	}
	if (isBgm == false)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
}

void Select::dontMove(float dt)
{
	ban = true;
}

void Select::addChara()
{
	charac[0] = Sprite::create("CHA_1_1.png");
	charac[1] = Sprite::create("CHA_2_2.png");
	charac[2] = Sprite::create("CHA_3_1.png");

	for (int i = 0; i < cNum; i++) {
		charac[i]->setPosition(posMX[i] + 500, posMY[i]);
		charac[i]->setOpacity(0);
		charac[i]->setScale(0.3, 0.3);
		addChild(charac[i], 1);
	}

	DelayTime* dt = DelayTime::create(0.5f);
	FadeIn* fi = FadeIn::create(0.4f);
	MoveBy* mb = MoveBy::create(0.4f, Vec2(-500, 0));
	Spawn* sp = Spawn::create(fi, mb, NULL);

	DelayTime* dt2 = DelayTime::create(0.6f);
	FadeIn* fi2 = FadeIn::create(0.4f);
	MoveBy* mb2 = MoveBy::create(0.4f, Vec2(-500, 0));
	Spawn* sp2 = Spawn::create(fi2, mb2, NULL);

	DelayTime* dt3 = DelayTime::create(0.7f);
	FadeIn* fi3 = FadeIn::create(0.4f);
	MoveBy* mb3 = MoveBy::create(0.4f, Vec2(-500, 0));
	Spawn* sp3 = Spawn::create(fi3, mb3, NULL);

	current = 1;
	charac[current]->setScale(0.5, 0.5);

	charac[0]->runAction(Sequence::create(dt, sp, NULL));
	charac[1]->runAction(Sequence::create(dt2, sp2, NULL));
	charac[2]->runAction(Sequence::create(dt3, sp3, NULL));

	/*for (int i = 0; i < cNum; i++)
	{
		charac[i]->runAction(Sequence::create(dt, sp, NULL));
	}*/
}

void Select::flyAway()
{

	DelayTime* dt[3];

	dt[0] = DelayTime::create(0.0f);
	FadeOut* fo = FadeOut::create(0.4f);
	MoveBy* mb = MoveBy::create(0.4f, Vec2(-500, 0));
	Spawn* sp = Spawn::create(fo, mb, NULL);
	MoveTo* mt = MoveTo::create(0.0f, Vec2(posMX[0] + 500, posMY[0]));
	ScaleTo* st = ScaleTo::create(0.0f, 0.3);

	dt[1] = DelayTime::create(0.1f);
	FadeOut* fo2 = FadeOut::create(0.4f);
	MoveBy* mb2 = MoveBy::create(0.4f, Vec2(-500, 0));
	Spawn* sp2 = Spawn::create(fo2, mb2, NULL);
	MoveTo* mt2 = MoveTo::create(0.0f, Vec2(posMX[1] + 500, posMY[1]));
	ScaleTo* st2 = ScaleTo::create(0.0f, 0.5);

	dt[2] = DelayTime::create(0.2f);
	FadeOut* fo3 = FadeOut::create(0.4f);
	MoveBy* mb3 = MoveBy::create(0.4f, Vec2(-500, 0));
	Spawn* sp3 = Spawn::create(fo3, mb3, NULL);
	MoveTo* mt3 = MoveTo::create(0.0f, Vec2(posMX[2] + 500, posMY[2]));
	ScaleTo* st3 = ScaleTo::create(0.0f, 0.3);

	charac[0]->runAction(Sequence::create(dt[(cNum - 1 - current + (cNum - 1)) % cNum], sp, mt, st, NULL));
	charac[1]->runAction(Sequence::create(dt[(cNum - 1 - current + (cNum - 1) + 1) % cNum], sp2, mt2, st2, NULL));
	charac[2]->runAction(Sequence::create(dt[(cNum - 1 - current + (cNum - 1) + 2) % cNum], sp3, mt3, st3, NULL));
}

void Select::reAddChara()
{
	DelayTime* dt = DelayTime::create(0.8f);
	FadeIn* fi = FadeIn::create(0.4f);
	MoveBy* mb = MoveBy::create(0.4f, Vec2(-500, 0));
	Spawn* sp = Spawn::create(fi, mb, NULL);

	DelayTime* dt2 = DelayTime::create(0.9f);
	FadeIn* fi2 = FadeIn::create(0.4f);
	MoveBy* mb2 = MoveBy::create(0.4f, Vec2(-500, 0));
	Spawn* sp2 = Spawn::create(fi2, mb2, NULL);

	DelayTime* dt3 = DelayTime::create(1.0f);
	FadeIn* fi3 = FadeIn::create(0.4f);
	MoveBy* mb3 = MoveBy::create(0.4f, Vec2(-500, 0));
	Spawn* sp3 = Spawn::create(fi3, mb3, NULL);

	current = 1;

	charac[0]->runAction(Sequence::create(dt, sp, NULL));
	charac[1]->runAction(Sequence::create(dt2, sp2, NULL));
	charac[2]->runAction(Sequence::create(dt3, sp3, NULL));
}

void Select::addMap()
{
	maps[0] = Sprite::create("m1.png");
	maps[1] = Sprite::create("m2.png");
	maps[2] = Sprite::create("m3.png");

	for (int i = 0; i < 3; i++)
	{
		maps[i]->setPosition(posMX[i], posMY[i]);
		maps[i]->setScale(0.0);
		maps[i]->setOpacity(0);
		addChild(maps[i], 2);
	}

	maps[1]->setZOrder(3);
	//maps[1]->setScale(0.3);

	DelayTime* dt = DelayTime::create(0.8f);
	FadeIn* fi = FadeIn::create(0.4f);
	ScaleTo* st = ScaleTo::create(0.4f, 0.5);
	MoveBy* mb = MoveBy::create(0.4f, Vec2(-500, 0));
	Spawn* sp = Spawn::create(fi, st, NULL);

	DelayTime* dt2 = DelayTime::create(0.8f);
	FadeIn* fi2 = FadeIn::create(0.4f);
	ScaleTo* st2 = ScaleTo::create(0.4f, 0.7);
	MoveBy* mb2 = MoveBy::create(0.4f, Vec2(-500, 0));
	Spawn* sp2 = Spawn::create(fi2, st2, NULL);

	DelayTime* dt3 = DelayTime::create(0.8f);
	FadeIn* fi3 = FadeIn::create(0.4f);
	ScaleTo* st3 = ScaleTo::create(0.4f, 0.5);
	MoveBy* mb3 = MoveBy::create(0.4f, Vec2(-500, 0));
	Spawn* sp3 = Spawn::create(fi3, st3, NULL);

	current = 1;

	maps[0]->runAction(Sequence::create(dt, sp, NULL));
	maps[1]->runAction(Sequence::create(dt2, sp2, NULL));
	maps[2]->runAction(Sequence::create(dt3, sp3, NULL));
}

void Select::onStart(Ref* ref) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (selected == 1)
	{
		DelayTime* dt = DelayTime::create(0.1f);
		FadeOut* fi = FadeOut::create(0.5f);
		MoveTo* mt = MoveTo::create(0.5f, Vec2(100, 300));
		p1->runAction(Sequence::create(dt, Spawn::create(fi, mt, NULL), NULL));

		reAddChara();
	}
	else if (selected == 1)
	{
		selected++;
		DelayTime* dt = DelayTime::create(0.1f);
		FadeOut* fi = FadeOut::create(0.5f);
		MoveTo* mt = MoveTo::create(0.5f, Vec2(860, 300));
		p2->runAction(Sequence::create(dt, Spawn::create(fi, mt, NULL), NULL));

		DelayTime* dt1 = DelayTime::create(0.8f);
		FadeIn* fi1 = FadeIn::create(0.5f);
		MoveTo* mt1 = MoveTo::create(0.5f, Vec2(200, 300));
		p1->runAction(Sequence::create(dt1, Spawn::create(fi1, mt1, NULL), NULL));

		DelayTime* dt2 = DelayTime::create(0.8f);
		FadeIn* fi2 = FadeIn::create(0.5f);
		MoveTo* mt2 = MoveTo::create(0.5f, Vec2(760, 300));
		p2->runAction(Sequence::create(dt2, Spawn::create(fi2, mt2, NULL), NULL));

		DelayTime* dt3 = DelayTime::create(0.1f);
		FadeOut* fo3 = FadeOut::create(0.5f);
		startMenuItem->runAction(Sequence::create(dt3, fo3, NULL));

		MenuItemImage* startMenuItem2 = MenuItemImage::create("Button2/Button_vs.png", "Button2/Button_vs.png", CC_CALLBACK_1(Select::onStart, this));
		startMenuItem2->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		startMenuItem2->setScale(0);
		auto start2 = Menu::create(startMenuItem2, NULL);
		start2->setPosition(Point::ZERO);
		addChild(start2, 1);

		DelayTime* dt4 = DelayTime::create(1.1f);
		ScaleTo* st4 = ScaleTo::create(0.4f, 0.4);
		startMenuItem2->runAction(Sequence::create(dt4, st4, NULL));
	}
	else if (selected == 2)
	{
		auto scene = Games::createScene(pl1, pl2, isBgm);
		//Games *temp = Games::create();
		//temp->setPlayTag(0, player1);
		//temp->setPlayTag(1, player2);
		//scene->addChild(temp);
		CCDirector::sharedDirector()->replaceScene(TransitionFade::create(1.5f, scene));
	}
}

bool Select::onTouchBegan(Touch *touch, cocos2d::Event *event)
{
	if (ban == false)
	{
		return true;
	}

	auto location = touch->getLocation();
	int locX = location.x;
	int locY = location.y;
	log("%d %d", locX, locY);
	if (locX >= 250 && locX <= 350 && locY >= 220 && locY <= 370)
	{
		if (selected <= 1)
		{
			MoveTo* mt = MoveTo::create(0.5f, Vec2(posMX[1], posMY[1]));
			EaseIn* mt_eo = EaseIn::create(mt, 3.0);
			ScaleTo* st = ScaleTo::create(0.5f, 0.5);
			charac[(current + (cNum - 1)) % cNum]->runAction(Spawn::create(mt_eo, st, NULL));

			MoveTo* mt2 = MoveTo::create(0.5f, Vec2(posMX[2], posMY[2]));
			//EaseBackOut* mt2_eo = EaseBackOut::create(mt2);
			ScaleTo* st2 = ScaleTo::create(0.5f, 0.3);
			charac[current]->runAction(Spawn::create(mt2, st2, NULL));

			FadeOut* fo = FadeOut::create(0.25f);
			MoveBy* mb = MoveBy::create(0.25f, Vec2(50, 0));
			Spawn* fm = Spawn::create(fo, mb, NULL);
			MoveTo* mt3 = MoveTo::create(0.01f, Vec2(posMX[0] - 50, posMY[0]));
			FadeIn* fi = FadeIn::create(0.25f);
			MoveBy* mb2 = MoveBy::create(0.25f, Vec2(50, 0));
			Spawn* fm2 = Spawn::create(fi, mb2, NULL);
			charac[(current + 1) % cNum]->runAction(Sequence::create(fm, mt3, fm2, NULL));

			current = (current + (cNum - 1)) % cNum;

			ban = false;

			scheduleOnce(schedule_selector(Select::dontMove), 0.5f);
		}
		else if (selected == 2)
		{
			MoveTo* mt = MoveTo::create(0.5f, Vec2(posMX[1], posMY[1]));
			EaseIn* mt_eo = EaseIn::create(mt, 3.0);
			ScaleTo* st = ScaleTo::create(0.5f, 0.5);
			maps[(current + (cNum - 1)) % cNum]->runAction(Spawn::create(mt_eo, st, NULL));
			maps[(current + (cNum - 1)) % cNum]->setZOrder(3);

			MoveTo* mt2 = MoveTo::create(0.5f, Vec2(posMX[2], posMY[2]));
			ScaleTo* st2 = ScaleTo::create(0.5f, 0.3);
			maps[current]->runAction(Spawn::create(mt2, st2, NULL));
			maps[current]->setZOrder(2);

			FadeOut* fo = FadeOut::create(0.25f);
			MoveBy* mb = MoveBy::create(0.25f, Vec2(50, 0));
			Spawn* fm = Spawn::create(fo, mb, NULL);
			MoveTo* mt3 = MoveTo::create(0.0f, Vec2(posMX[0] - 50, posMY[0]));
			FadeIn* fi = FadeIn::create(0.25f);
			MoveBy* mb2 = MoveBy::create(0.25f, Vec2(50, 0));
			Spawn* fm2 = Spawn::create(fi, mb2, NULL);
			maps[(current + 1) % cNum]->runAction(Sequence::create(fm, mt3, fm2, NULL));

			current = (current + (cNum - 1)) % cNum;

			ban = false;

			scheduleOnce(schedule_selector(Select::dontMove), 0.5f);
		}
	}
	else if (locX >= 610 && locX <= 710 && locY >= 220 && locY <= 370)
	{
		if (selected <= 1)
		{
			MoveTo* mt = MoveTo::create(0.5f, Vec2(posMX[1], posMY[1]));
			EaseIn* mt_eo = EaseIn::create(mt, 3.0);
			ScaleTo* st = ScaleTo::create(0.5f, 0.5);
			charac[(current + 1) % cNum]->runAction(Spawn::create(mt_eo, st, NULL));

			MoveTo* mt2 = MoveTo::create(0.5f, Vec2(posMX[0], posMY[0]));
			ScaleTo* st2 = ScaleTo::create(0.5f, 0.3);
			charac[current]->runAction(Spawn::create(mt2, st2, NULL));

			FadeOut* fo = FadeOut::create(0.25f);
			MoveBy* mb = MoveBy::create(0.25f, Vec2(-50, 0));
			Spawn* fm = Spawn::create(fo, mb, NULL);
			MoveTo* mt3 = MoveTo::create(0.01f, Vec2(posMX[2] + 50, posMY[2]));
			FadeIn* fi = FadeIn::create(0.25f);
			MoveBy* mb2 = MoveBy::create(0.25f, Vec2(-50, 0));
			Spawn* fm2 = Spawn::create(fi, mb2, NULL);
			charac[(current + (cNum - 1)) % cNum]->runAction(Sequence::create(fm, mt3, fm2, NULL));

			current = (current + 1) % cNum;

			ban = false;

			scheduleOnce(schedule_selector(Select::dontMove), 0.5f);
		}
		else if (selected == 2)
		{
			MoveTo* mt = MoveTo::create(0.5f, Vec2(posMX[1], posMY[1]));
			EaseIn* mt_eo = EaseIn::create(mt, 3.0);
			ScaleTo* st = ScaleTo::create(0.5f, 0.5);
			maps[(current + 1) % cNum]->runAction(Spawn::create(mt_eo, st, NULL));
			maps[(current + 1) % cNum]->setZOrder(3);

			MoveTo* mt2 = MoveTo::create(0.5f, Vec2(posMX[0], posMY[0]));
			ScaleTo* st2 = ScaleTo::create(0.5f, 0.3);
			maps[current]->runAction(Spawn::create(mt2, st2, NULL));
			maps[current]->setZOrder(2);

			FadeOut* fo = FadeOut::create(0.25f);
			MoveBy* mb = MoveBy::create(0.25f, Vec2(-50, 0));
			Spawn* fm = Spawn::create(fo, mb, NULL);
			MoveTo* mt3 = MoveTo::create(0.0f, Vec2(posMX[2] + 50, posMY[2]));
			FadeIn* fi = FadeIn::create(0.25f);
			MoveBy* mb2 = MoveBy::create(0.25f, Vec2(-50, 0));
			Spawn* fm2 = Spawn::create(fi, mb2, NULL);
			maps[(current + (cNum - 1)) % cNum]->runAction(Sequence::create(fm, mt3, fm2, NULL));

			current = (current + 1) % cNum;

			ban = false;

			scheduleOnce(schedule_selector(Select::dontMove), 0.5f);
		}
	}
	else if (locX >= 400 && locX <= 560 && locY >= 180 && locY <= 410)
	{
		if (selected == 0)
		{
			/*selected++;
			Sprite* p1 = Sprite::create("kne.jpg");
			p1->setAnchorPoint(Vec2(0, 0));
			p1->setOpacity(0);
			p1->setPosition(0, 0);
			addChild(p1, 2);

			FadeIn* fi = FadeIn::create(0.3f);
			p1->runAction(fi);*/
			selected++;
			flyAway();

			if (current == 0)
			{
				p1 = Sprite::create("texture/1.png");
				pl1 = 0;
			}
			else if (current == 1)
			{
				p1 = Sprite::create("texture/2.png");
				pl1 = 1;
			}
			else if (current == 2)
			{
				p1 = Sprite::create("texture/3.png");
				pl1 = 2;
			}
			p1->setScale(0.5);
			p1->setOpacity(0);
			p1->setPosition(200, 300);
			addChild(p1, 2);

			DelayTime* dt = DelayTime::create(0.3f);
			FadeIn* fi = FadeIn::create(0.5f);
			MoveTo* mt = MoveTo::create(0.5f, Vec2(100, 300));
			p1->runAction(Sequence::create(dt, Spawn::create(fi, mt, NULL), NULL));

			reAddChara();

			red->stopAllActions();
			red->setOpacity(255);

			/*flyAway();
			reAddChara();*/

			FadeIn* fi2 = FadeIn::create(0.5f);
			FadeOut* fo = FadeOut::create(0.5f);
			blue->runAction(RepeatForever::create(Sequence::create(fi2, fo, NULL)));

			ban = true;
		}
		else if (selected == 1)
		{
			/*selected++;
			Sprite* p2 = Sprite::create("lune.jpg");
			p2->setAnchorPoint(Vec2(1, 0));
			p2->setOpacity(0);
			p2->setPosition(960, 0);
			addChild(p2, 2);

			FadeIn* fi = FadeIn::create(0.3f);
			p2->runAction(fi);*/
			selected++;
			flyAway();

			if (current == 0)
			{
				p2 = Sprite::create("texture/1.png");
				pl2 = 0;
			}
			else if (current == 1)
			{
				p2 = Sprite::create("texture/2.png");
				pl2 = 1;
			}
			else if (current == 2)
			{
				p2 = Sprite::create("texture/3.png");
				pl2 = 2;
			}
			//p2 = Sprite::create("texture/2.png");
			p2->setScale(0.5);
			p2->setOpacity(0);
			p2->setPosition(760, 300);
			addChild(p2, 2);

			DelayTime* dt = DelayTime::create(0.3f);
			FadeIn* fi = FadeIn::create(0.5f);
			MoveTo* mt = MoveTo::create(0.5f, Vec2(860, 300));
			p2->runAction(Sequence::create(dt, Spawn::create(fi, mt, NULL), NULL));

			blue->stopAllActions();
			blue->setOpacity(255);

			//flyAway();

			DelayTime* dt1 = DelayTime::create(1.1f);
			ScaleTo* fi1 = ScaleTo::create(0.5f, 0.6);
			MoveTo* mt1 = MoveTo::create(0.5f, Vec2(200, 300));
			p1->runAction(Sequence::create(dt1, Spawn::create(fi1, mt1, NULL), NULL));

			DelayTime* dt2 = DelayTime::create(1.1f);
			ScaleTo* fi2 = ScaleTo::create(0.5f, 0.6);
			MoveTo* mt2 = MoveTo::create(0.5f, Vec2(760, 300));
			p2->runAction(Sequence::create(dt2, Spawn::create(fi2, mt2, NULL), NULL));

			DelayTime* dt5 = DelayTime::create(1.1f);
			MoveTo* mt5 = MoveTo::create(0.5f, Vec2(200, 80));
			red->runAction(Sequence::create(dt5, mt5, NULL));

			DelayTime* dt6 = DelayTime::create(1.1f);
			MoveTo* mt6 = MoveTo::create(0.5f, Vec2(760, 80));
			blue->runAction(Sequence::create(dt6, mt6, NULL));

			startMenuItem2 = MenuItemImage::create("Button2/Button_vs.png", "Button2/Button_vs.png", CC_CALLBACK_1(Select::onStart, this));
			startMenuItem2->setPosition(480, 290);
			startMenuItem2->setScale(0);
			auto start2 = Menu::create(startMenuItem2, NULL);
			start2->setPosition(Point::ZERO);
			addChild(start2, 1);

			DelayTime* dt4 = DelayTime::create(1.1f);
			ScaleTo* st4 = ScaleTo::create(0.4f, 0.4);
			startMenuItem2->runAction(Sequence::create(dt4, st4, NULL));
			//addMap();

			ban = true;
		}
		else if (selected == 2)
		{
			MoveTo* mt = MoveTo::create(0.25f, Vec2(posMX[1], posMY[1]));
			FadeOut* fo = FadeOut::create(0.25f);
			maps[(current + 1) % cNum]->runAction(Spawn::create(mt, fo, NULL));

			MoveTo* mt2 = MoveTo::create(0.25f, Vec2(posMX[1], posMY[1]));
			FadeOut* fo2 = FadeOut::create(0.25f);
			maps[(current + (cNum - 1)) % cNum]->runAction(Spawn::create(mt2, fo2, NULL));

			selected++;
		}
		
	}

	return true;
}


int Select::getPos(float x)
{
	for (int i = 0; i < cNum; i++) {
		if (posMX[i] == x) {
			return i;
		}
	}
}
