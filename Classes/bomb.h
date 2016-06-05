#ifndef Bomb_H
#define Bomb_H
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Hero.h"
#include "CommonData.h"
using namespace CocosDenshion;
USING_NS_CC;
class Bomb :public Node
{
public:
	Bomb();
	static Bomb* create();
	bool init();
	Sprite* bodySprite;
	Sprite* bombSprite;
	void update(float dt);
	void playEffect();
	void afterAlert();
	int mode;
	void bombUpdate(float dt);
	bool collisionWithHero();
	float height1;

private:
	
};

#endif