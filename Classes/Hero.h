#ifndef Hero_H
#define Hero_H
#include "cocos2d.h"
#include "GameEnum.h"
#include "AnimationManager.h"
#define GRAVITY 2
#define UPSPEED 30
#define RUNSPEED 10

USING_NS_CC;
class Hero :public Node
{
public:
	Hero();
	~Hero();
	void setState(HeroState state);
	static Hero* create();
	static Hero* _instrans;
	bool heroInit();
	Sprite* heroBody;
	HeroState heroState;
	float runSpeed;
	bool isRunning;
	bool isJumping;
	bool heroFace;
	bool isInSky;
	bool isReJump;
	bool isDead;
	bool isDownRun;
	float upSpeed;
	float gravity;
	float groundSurport;
	void clearIumpSpeed();
	void resetGroundSurport();
	void clearGroundSurport();
	static Hero* getInstrance();
private:
	SpriteFrame * normalStandFrame;
	SpriteFrame* downRunSprite;
	void resetJumpSpeed();
	
	
};
#endif