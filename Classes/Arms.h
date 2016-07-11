#ifndef __ARMS_H__
#define __ARMS_H__

#include "cocos2d.h"

USING_NS_CC;

extern enum armsName {ARTILLERY, PISTOL, STAFF};  //ÎäÆ÷Ãû³ÆÃ¶¾ÙÀà

class Arms {
public:
	Arms();

	//ÎäÆ÷ÉËº¦get set
	void setDamage(int);
	int getDamage();

	//ÎäÆ÷±¬Õ¨·¶Î§get set
	void setRange(int);
	int getRange();

	//ÎäÆ÷ÌùÍ¼get set
	void setArmSpr(Sprite*);
	Sprite* getArmSpr();

	//ÎäÆ÷Ãû³Æget set
	void setArmName(enum armsName);
	enum armsName getArmName();

	//ÎäÆ÷´óÕĞcd get set
	void setCd(int);
	int getCd();

private:
	int damage;                                    //ÎäÆ÷µÄÉËº¦
	int range;                                     //ÎäÆ÷±¬Õ¨·¶Î§
	Sprite* arm;                                   //ÎäÆ÷ÌùÍ¼
	enum armsName armN;                            //ÎäÆ÷Ãû³Æ
	int cd;                                        //ÎäÆ÷´óÕĞcd
};

#endif