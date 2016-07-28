#include "SelectScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "HelloWorldScene.h"
#include "MapSelectScene.h"

using namespace CocosDenshion;

float posMX[3] = { 250, 480, 710 };
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

	Sprite* background = Sprite::create("BGP12.png");
	background->setScale(1.2);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);

	red = Sprite::create("p1s.png");
	red->setAnchorPoint(Vec2(0, 0));
	red->setOpacity(0);
	red->setPosition(0, 0);
	//addChild(red, 3);

	blue = Sprite::create("p2s.png");
	blue->setAnchorPoint(Vec2(1, 0));
	blue->setOpacity(0);
	blue->setPosition(visibleSize.width, 0);
	//addChild(blue, 3);


	FadeIn* fi = FadeIn::create(0.5f);
	FadeOut* fo = FadeOut::create(0.5f);
	//red->runAction(RepeatForever::create(Sequence::create(fi, fo, NULL)));

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


	MenuItemImage* label0 = MenuItemImage::create("Button2/Button_back.png", "Button2/Button_back.png");
	auto menuItem = MenuItemLabel::create(label0);
	auto menu = Menu::create(menuItem, nullptr);
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	});
	menu->setPosition(Vec2::ZERO);
	menuItem->setScale(0.15);
	menuItem->setAnchorPoint(Vec2(0, 1));
	menuItem->setPosition(0, visibleSize.height);
	addChild(menu, 1);


	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(Select::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void Select::addChara()
{
	charac[0] = Sprite::create("CHA_1_1.png");
	charac[1] = Sprite::create("CHA_2_2.png");
	charac[2] = Sprite::create("CHA_3_1.png");

	for (int i = 0; i < cNum; i++) {
		charac[i]->setPosition(posMX[i] + 500, posMY[i]);
		charac[i]->setOpacity(0);
		charac[i]->setScale(0.5, 0.5);
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
	charac[current]->setScale(0.7, 0.7);

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
	ScaleTo* st = ScaleTo::create(0.0f, 0.4);

	dt[1] = DelayTime::create(0.1f);
	FadeOut* fo2 = FadeOut::create(0.4f);
	MoveBy* mb2 = MoveBy::create(0.4f, Vec2(-500, 0));
	Spawn* sp2 = Spawn::create(fo2, mb2, NULL);
	MoveTo* mt2 = MoveTo::create(0.0f, Vec2(posMX[1] + 500, posMY[1]));
	ScaleTo* st2 = ScaleTo::create(0.0f, 0.8);

	dt[2] = DelayTime::create(0.2f);
	FadeOut* fo3 = FadeOut::create(0.4f);
	MoveBy* mb3 = MoveBy::create(0.4f, Vec2(-500, 0));
	Spawn* sp3 = Spawn::create(fo3, mb3, NULL);
	MoveTo* mt3 = MoveTo::create(0.0f, Vec2(posMX[2] + 500, posMY[2]));
	ScaleTo* st3 = ScaleTo::create(0.0f, 0.4);

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
	//maps[1]->setScale(0.7);

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
	else if (selected == 2)
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
	else if (selected == 3)
	{
		auto scene = Games::createScene();
		//Games *temp = Games::create();
		//temp->setPlayTag(0, player1);
		//temp->setPlayTag(1, player2);
		//scene->addChild(temp);
		CCDirector::sharedDirector()->replaceScene(TransitionFade::create(1.5f, scene));
	}
}

bool Select::onTouchBegan(Touch *touch, cocos2d::Event *event)
{
	auto location = touch->getLocation();
	int locX = location.x;
	int locY = location.y;
	if (locX >= 230 && locX <= 290 && locY >= 250 && locY <= 350)
	{
		if (selected <= 1)
		{
			MoveTo* mt = MoveTo::create(0.5f, Vec2(posMX[1], posMY[1]));
			EaseIn* mt_eo = EaseIn::create(mt, 3.0);
			ScaleTo* st = ScaleTo::create(0.5f, 0.7);
			charac[(current + (cNum - 1)) % cNum]->runAction(Spawn::create(mt_eo, st, NULL));

			MoveTo* mt2 = MoveTo::create(0.5f, Vec2(posMX[2], posMY[2]));
			//EaseBackOut* mt2_eo = EaseBackOut::create(mt2);
			ScaleTo* st2 = ScaleTo::create(0.5f, 0.5);
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
		}
		else if (selected == 2)
		{
			MoveTo* mt = MoveTo::create(0.5f, Vec2(posMX[1], posMY[1]));
			EaseIn* mt_eo = EaseIn::create(mt, 3.0);
			ScaleTo* st = ScaleTo::create(0.5f, 0.7);
			maps[(current + (cNum - 1)) % cNum]->runAction(Spawn::create(mt_eo, st, NULL));
			maps[(current + (cNum - 1)) % cNum]->setZOrder(3);

			MoveTo* mt2 = MoveTo::create(0.5f, Vec2(posMX[2], posMY[2]));
			ScaleTo* st2 = ScaleTo::create(0.5f, 0.5);
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
		}
	}
	else if (locX >= 670 && locX <= 730 && locY >= 250 && locY <= 350)
	{
		if (selected <= 1)
		{
			MoveTo* mt = MoveTo::create(0.5f, Vec2(posMX[1], posMY[1]));
			EaseIn* mt_eo = EaseIn::create(mt, 3.0);
			ScaleTo* st = ScaleTo::create(0.5f, 0.7);
			charac[(current + 1) % cNum]->runAction(Spawn::create(mt_eo, st, NULL));

			MoveTo* mt2 = MoveTo::create(0.5f, Vec2(posMX[0], posMY[0]));
			ScaleTo* st2 = ScaleTo::create(0.5f, 0.5);
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
		}
		else if (selected == 2)
		{
			MoveTo* mt = MoveTo::create(0.5f, Vec2(posMX[1], posMY[1]));
			EaseIn* mt_eo = EaseIn::create(mt, 3.0);
			ScaleTo* st = ScaleTo::create(0.5f, 0.7);
			maps[(current + 1) % cNum]->runAction(Spawn::create(mt_eo, st, NULL));
			maps[(current + 1) % cNum]->setZOrder(3);

			MoveTo* mt2 = MoveTo::create(0.5f, Vec2(posMX[0], posMY[0]));
			ScaleTo* st2 = ScaleTo::create(0.5f, 0.5);
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
		}
	}
	else if (locX >= 430 && locX <= 530 && locY >= 220 && locY <= 380)
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
			}
			else if (current == 1)
			{
				p1 = Sprite::create("texture/2.png");
			}
			else if (current == 2)
			{
				p1 = Sprite::create("texture/3.png");
			}
			p1->setScale(0.7);
			p1->setOpacity(0);
			p1->setPosition(300, 300);
			addChild(p1, 2);

			DelayTime* dt = DelayTime::create(0.3f);
			FadeIn* fi = FadeIn::create(0.5f);
			MoveTo* mt = MoveTo::create(0.5f, Vec2(200, 300));
			p1->runAction(Sequence::create(dt, Spawn::create(fi, mt, NULL), NULL));

			//red->stopAllActions();
			//red->setOpacity(255);

			/*flyAway();
			reAddChara();*/

			FadeIn* fi2 = FadeIn::create(0.5f);
			FadeOut* fo = FadeOut::create(0.5f);
			//blue->runAction(RepeatForever::create(Sequence::create(fi2, fo, NULL)));
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
			}
			else if (current == 1)
			{
				p2 = Sprite::create("texture/2.png");
			}
			else if (current == 2)
			{
				p2 = Sprite::create("texture/3.png");
			}
			//p2 = Sprite::create("texture/2.png");
			p2->setScale(0.7);
			p2->setOpacity(0);
			p2->setPosition(660, 300);
			addChild(p2, 2);

			DelayTime* dt = DelayTime::create(0.3f);
			FadeIn* fi = FadeIn::create(0.5f);
			MoveTo* mt = MoveTo::create(0.5f, Vec2(760, 300));
			p2->runAction(Sequence::create(dt, Spawn::create(fi, mt, NULL), NULL));

			//blue->stopAllActions();
			//blue->setOpacity(255);

			flyAway();
			//addMap();
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
