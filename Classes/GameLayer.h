#ifndef GameLayer_H
#define GameLayer_H
#include "CommonData.h"
#include "GameMap.h"
#include "Hero.h"
#include "AnimationManager.h"
#include "SimpleAudioEngine.h"
#include "ThingOfEat.h"
#include "PauseDialog.h"
#include "OverDialog.h"
#include "bomb.h"
#include "cocos-ext.h"
#include<time.h>

#include "cocos2d.h"
USING_NS_CC;
USING_NS_CC_EXT;
class GameLayer :public Layer
{
public:
	GameLayer();
	static GameLayer* _instrance;
	static GameLayer* getInstrance();
	static Scene* createScene();
	virtual bool init();
	void initMapAndHero();
	void initUI();
	void update(float a);
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	CREATE_FUNC(GameLayer);
	GameMap* gameMap;
	Hero* hero;
	Size mapSize;
	Size winSize;
	float mapFollowPoint;
	Layer* mainLayer;
	HeroState oldState;
	Label *perfomaceLabel;
	Label *distanceLabel;
	void paunseGame();
	void pauseCallback(Ref* node);
	bool isDead;
	int score;
	int distance;
	void downBtnCallBack(Ref* p, Control::EventType type);
	void jumpBtnCallBack(Ref* p, Control::EventType type);
	
private:
	void freshScore(Point heroPos);
	bool isRightKeyDown;
	bool isLeftKeyDown;
	bool isSpaceKeyDown;
	Point positon;
	void collisionV();//´¹Ö±·½ÏòÅö×²¼ì²â
	void collisionH();
	void mapRun(Point position);
	int getRandNumber(int min, int max);
};

#endif