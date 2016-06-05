#ifndef GameMap_H
#define GameMap_H
#include "cocos2d.h"
#include "GameEnum.h"
#include "ThingOfEat.h"

USING_NS_CC;
class GameLayer;
class GameMap :public TMXTiledMap
{
	CC_PROPERTY_READONLY(TMXLayer*,landLayer,LandLayer);
	CC_PROPERTY_READONLY(TMXLayer*, scareLayer, ScareLayer);
	CC_PROPERTY_READONLY(TMXLayer*, diaoLayer, DiaoLayer);
	CC_PROPERTY_READONLY(TMXLayer*, groundLayer, GroundLayer);
	CC_PROPERTY_READONLY(TMXLayer*, coinLayer, CoinLayer);
	CC_PROPERTY_READONLY(TMXLayer*,knifeLayer,KnifeLayer);
	CC_PROPERTY_READONLY(TMXLayer*, boxLayer, BoxLayer);
	CC_PROPERTY_READONLY(TMXObjectGroup*,objectLayer,ObjectLayer);
	

public:
	GameMap();
	~GameMap();
	void paunseMap();
	static GameMap* create(const char* tmxfile);
	static GameMap* getInstrance();
	static GameMap* _instrance;
	void extraInit();
	Point heroBirthPlace;
	Point getHeroBirthPlace();
	void initObjects();
	Point positionToTileCoord(Point pos);
	Point tilecoordToPosition(Point tileCoord);
	TileType tileTypeforPos(Point tileCoord);
	void lanchThingOfEatInMap();
	void update(float dt);

private:
	PointArray *pItemCoordArray;
	PointArray *pBombPosArray;
	Array *pEatArray;
};

#endif