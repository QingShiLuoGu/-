#include "GameMap.h"

 GameMap*  GameMap::_instrance;
#include "GameLayer.h"
GameMap::GameMap()
{
	pItemCoordArray = PointArray::create(100);
	pBombPosArray = PointArray::create(50);
	pBombPosArray->retain();
	pItemCoordArray->retain();
	pEatArray = Array::create();
	pEatArray->retain();
	_instrance = this;
}
GameMap::~GameMap()
{

}

GameMap* GameMap::getInstrance()
{
	return _instrance;
}
GameMap* GameMap::create(const char *tmxfile)
{
	GameMap* gameMap = new GameMap();
	if (gameMap&&gameMap->initWithTMXFile(tmxfile))
	{
		gameMap->extraInit();
		gameMap->autorelease();
		return gameMap;
	}
	CC_SAFE_DELETE(gameMap);
	return NULL;
}
void GameMap::extraInit()
{
	scareLayer = this->getLayer("scare");
	knifeLayer = this->getLayer("knife");
	diaoLayer = this->getLayer("diao");
	landLayer = this->getLayer("land");
	coinLayer = this->getLayer("coin");
	//boxLayer = this->getLayer("box");
	objectLayer = this->getObjectGroup("object");
	groundLayer = this->getLayer("ground");
	groundLayer->setVisible(false);
	initObjects();
	lanchThingOfEatInMap();
	this->scheduleUpdate();
}

void GameMap::update(float dt)
{
	Point heroPosition = Hero::getInstrance()->getPosition();
	float height = heroPosition.x;
	int count = pBombPosArray->count();
	Point pPos;
	for (int i = 0; i < count; i++)
	{
		pPos = pBombPosArray->getControlPointAtIndex(i);
		if (fabs(heroPosition.x - pPos.x) < 5)
		{
			GameLayer::getInstrance()->mainLayer->addChild(Bomb::create());
		}
	}
}

void GameMap::paunseMap()
{
	ThingOfEat* thingOfEat;
	int count = pEatArray->count();
	for (int i = 0; i < count; i++)
	{
		thingOfEat = (ThingOfEat*)pEatArray->objectAtIndex(i);
		thingOfEat->unscheduleUpdate();
	}
	this->unscheduleUpdate();
}

TMXLayer* GameMap::getScareLayer() const
{
	return scareLayer;
}

TMXLayer* GameMap::getKnifeLayer() const
{
	return knifeLayer;
}
TMXLayer* GameMap::getDiaoLayer() const
{
	return diaoLayer;
}
TMXLayer* GameMap::getLandLayer() const
{
	return landLayer;
}
TMXLayer* GameMap::getCoinLayer() const
{
	return coinLayer;
}
TMXObjectGroup* GameMap::getObjectLayer() const
{
	return objectLayer;
}

TMXLayer* GameMap::getGroundLayer() const
{
	return groundLayer;
}
TMXLayer* GameMap::getBoxLayer() const
{
	return boxLayer;
}


void GameMap::lanchThingOfEatInMap()
{
	ThingOfEat* thingOfEat;
	int count = pEatArray->count();
	for (int i = 0; i < count; i++)
	{
		thingOfEat = (ThingOfEat*)pEatArray->objectAtIndex(i);
		thingOfEat->setPosition(thingOfEat->getPos());
		switch (thingOfEat->getType())
		{
		case eFK:
		case eHJump:
		case eCat:
			this->addChild(thingOfEat);
			break;
		default:
			break;
		}
		thingOfEat->launchInmap();
	}
}

void GameMap::initObjects()
{
	ValueVector tempArray = objectLayer->getObjects();
	Value objPointMap;
	for (auto objPointMap : tempArray)
	{
		ValueMap objPoint = objPointMap.asValueMap();
		int posX = objPoint.at("x").asFloat();
		int posY = objPoint.at("y").asFloat();
		Point tileXY = this->positionToTileCoord(Point(posX,posY));
		std::string name = objPoint.at("name").asString();
		std::string type = objPoint.at("type").asString();
		if (name == "birth_place")
		{
			heroBirthPlace = Point(posX, posY);
		}
		if (name == "eat")
		{
			ThingOfEat* thingOfEat = NULL;
			if (type == "cat")
			{
				thingOfEat = CatOfEat::create();
			}
			else if (type == "fk")
			{
				thingOfEat = FkOfEat::create();
			}
			else if (type == "hj")
			{
				thingOfEat = HelpJump::create();
				posY -= 30;
			}
			if (thingOfEat != NULL)
			{
				pEatArray->addObject(thingOfEat);
				thingOfEat->setTileCoord(tileXY);
				thingOfEat->setPos(Point(posX,posY));
			}
		}
		if (name == "enemy")
		{
			if (type == "bomb")
			{
				pBombPosArray->addControlPoint(Point(posX,posY));
			}
		}

	}
}
Point GameMap::getHeroBirthPlace()
{
	return heroBirthPlace;
}

Point GameMap::positionToTileCoord(Point pos)
{
	int x = pos.x / this->getTileSize().width;
	int y = (this->getMapSize().height - 1) - pos.y / this->getTileSize().height;
	return Point(x, y);
}

Point GameMap::tilecoordToPosition(Point tileCoord)
{
	float x = tileCoord.x * this->getTileSize().width;
	float y = (this->getMapSize().height - 1 - tileCoord.y) * this->getTileSize().height;
	return Point(x, y);
}
// 接受一个Tile坐标系下的点，给出该点对应在图中的图块元素类型
TileType GameMap::tileTypeforPos(Point tileCoord)
{
	/*int GID = boxLayer->tileGIDAt(tileCoord);
	if (GID > 0)
	{
		return eBox;
	}*/

	 int GID = groundLayer->tileGIDAt(tileCoord);
	if (GID > 0)
	{
		return eGroud;
	}

	GID = diaoLayer->tileGIDAt(tileCoord);
	if (GID > 0)
	{
		return eDiao;
	}

	 GID = landLayer->tileGIDAt(tileCoord);
	if (GID > 0)
	{
		return eLand;
	}
	GID = coinLayer->tileGIDAt(tileCoord);
	if (GID > 0)
	{
		return eCoin;
	}
	GID = knifeLayer->tileGIDAt(tileCoord);
	if (GID > 0)
	{
		return eKnife;
	}
	GID = scareLayer->tileGIDAt(tileCoord);
	if (GID > 0)
	{
		return eScare;
	}

	return eTile_none;
}