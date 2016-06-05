#ifndef GameEnum_H
#define GameEnum_H
enum AnimationType
{
	runAnimation,
	reJumpAnimation,
	jumpAnimation,
	coinFlyAnimation
};

enum HeroState
{
	eNormalRight,
	eNormalLeft,
	eRight,
	eLeft,
	eJumpRight,
	eJumpLeft,
	eReJumpRight,
	eBlink,
	eDownRun,
	eReJumpLeft
};

enum TileType
{
	eKnife,
	eScare,
	eLand,
	eGroud,
	eBox,
	eCoin,
	eDiao,
	eTile_none
};
enum EatType
{
	eCat,
	eFK,
	eHJump
};

#endif