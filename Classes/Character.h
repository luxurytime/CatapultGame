#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "Arms.h"

USING_NS_CC;

class Character{
public:
	Character()
	{

	}

	//ÈËÎïÉúÃüÖµget set
	void setHP(int);
	int getHP();

	//ÈËÎïÉúÃüÌõget set
	void setHPBar();
	ProgressTimer* getHPBar();

	//ÈËÎïÌùÍ¼get set
	void setCharaSpr(Sprite* c)
	{
		chara = c;
	}

	Sprite* getCharaSpr()
	{
		return chara;
	}

	//ÈËÎïÎäÆ÷get set
	//void setArm(Arms);
	//Arms getArm();

	//ÈËÎïÎ»ÖÃget set
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

	void setIsRight(bool ir){
		isRight = ir;
	}

	bool getIsRight(){
		return isRight;
	}

	void setJumpNum(int jm){
		jumpNum = jm;
	}

	int getJumpNum(){
		return jumpNum;
	}

	void setSpeed(float s){
		speed = s;
	}

	float getSpeed(){
		return speed;
	}

	void setMoveDis(float md){
		movedis = md;
	}

	float getMoveDis(){
		return movedis;
	}


private:
	int HP;                        //ÈËÎïÉúÃüÖµ
	ProgressTimer* hpBar;          //ÈËÎïÉúÃüÌõ
	Sprite* chara;             //ÈËÎïÌùÍ¼
	//Arms arm;                      //ÈËÎïµÄÎäÆ÷

	bool isRight;
	int jumpNum;
	float speed;
	float movedis;

	cocos2d::Vector<SpriteFrame*> walk;
	cocos2d::Vector<SpriteFrame*> dead;

};

#endif