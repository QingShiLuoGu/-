#ifndef ThingOfEat_H
#define ThingOfEat_H
#include "cocos2d.h"
#include "GameEnum.h"
#include "Hero.h"
#include "GameMap.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
class ThingOfEat :public Node
{
public:
	ThingOfEat();
	~ThingOfEat();
	void setTileCoord(Point _point);
	Point getTileCoord();
	void setPos(Point _point);
	Point getPos();
	void setType(EatType type);
	EatType getType();
	Sprite *bodySprite;
	virtual bool collisionWithHero();
	virtual void launchInmap()=0;
	virtual void setNoVisible();
	bool isRunAction;
private:
	EatType type;
	Point tileCoord;
	Point position; 
};

class CatOfEat :public ThingOfEat
{
public:
	CREATE_FUNC(CatOfEat);
	bool init();
	CatOfEat();
	~CatOfEat();
	void update(float dt);
	void launchInmap()override;
	SpriteFrame* effectFrame;
};
class HelpJump :public ThingOfEat
{
public:
	CREATE_FUNC(HelpJump);
	bool init();
	HelpJump();
	~HelpJump();
	void update(float);
	void launchInmap()override;
};

class FkOfEat :public ThingOfEat
{
public:
	CREATE_FUNC(FkOfEat);
	bool init();
	FkOfEat();
	~FkOfEat();
	void update(float dt);
	void launchInmap() override;
	bool isChanged;
	void callBack();
	void dieCallBack();
};

#endif