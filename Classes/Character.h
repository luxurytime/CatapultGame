#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "Arms.h"

USING_NS_CC;

class Character {
public:
	Character()
	{
		
	}

	//人物生命值get set
	void setHP(int);
	int getHP();

	//人物生命条get set
	void setHPBar();
	ProgressTimer* getHPBar();

	//人物贴图get set
	void setCharaSpr(Sprite* c)
	{
		chara = c;
	}

	Sprite* getCharaSpr()
	{
		return chara;
	}

	//人物武器get set
	//void setArm(Arms);
	//Arms getArm();

	//人物位置get set
	void setPos(float, float);
	float getPosX();
	float getPosY();

	void setWalkFrame(Vector<SpriteFrame*> v)
	{
		walk = v;
	}

	Vector<SpriteFrame*> getWalkFrame()
	{
		return walk;
	}

	void setDeadFrame(Vector<SpriteFrame*> v)
	{
		dead = v;
	}

	Vector<SpriteFrame*> getDeadFrame()
	{
		return dead;
	}



private:
	int HP;                        //人物生命值
	ProgressTimer* hpBar;          //人物生命条
	Sprite* chara;             //人物贴图
	//Arms arm;                      //人物的武器

	//人物位置
	float posX;
	float posY;

	cocos2d::Vector<SpriteFrame*> walk;
	cocos2d::Vector<SpriteFrame*> dead;

};

#endif