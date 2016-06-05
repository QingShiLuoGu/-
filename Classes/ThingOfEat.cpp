#include "ThingOfEat.h"

ThingOfEat::ThingOfEat()
{
	isRunAction = false;
}
ThingOfEat::~ThingOfEat()
{
}

void ThingOfEat::setType(EatType type)
{
	this->type = type;
}

EatType ThingOfEat::getType()
{
	return type;
}

bool ThingOfEat::collisionWithHero()
{
	Size heroSize = Hero::getInstrance()->heroBody->getContentSize();
	Point heroPos = Hero::getInstrance()->getPosition();
	Size pSize = bodySprite->getContentSize();
	Point pPos = this->getPosition();
	Rect heroRect = Rect(heroPos.x + 10, heroPos.y + 10, heroSize.width - 20, heroSize.height - 20);
	Rect pRect = Rect(pPos.x + 10, pPos.y + 10, pSize.width - 20, pSize.height - 20);

	if (heroRect.intersectsRect(pRect))
	{
		return true;
	}
	return false;
}

void ThingOfEat::setTileCoord(Point _point)
{
	tileCoord = _point;
}
Point ThingOfEat::getTileCoord()
{
	return tileCoord;
}

void ThingOfEat::setPos(Point _point)
{
	position = _point;
}
Point ThingOfEat::getPos()
{
	return position;
}

void ThingOfEat::setNoVisible()
{
	this->setVisible(false);
	this->removeFromParent();
}



bool HelpJump::init()	
{
	return true;
}
HelpJump::HelpJump()
{
	bodySprite = Sprite::create("image/LD_03.png");
	this->addChild(bodySprite);
	setType(eHJump);
}

HelpJump::~HelpJump()
{
	this->unscheduleUpdate();
}

void HelpJump::update(float a)
{
	
	if (collisionWithHero())
	{
		Hero* hero = Hero::getInstrance();
		if (hero->isInSky)
		{
			hero->setState(eJumpRight);
		}
		else
		{
			Point pos = hero->getPosition();
			hero->setPosition(Point(pos.x-10,pos.y));
		}
	}
}

void HelpJump::launchInmap()
{
	this->scheduleUpdate();
}



bool CatOfEat::init()
{
	return true;
}
CatOfEat::CatOfEat()
{
	bodySprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("LD_02.png"));
	this->addChild(bodySprite);
	setType(eCat);
	effectFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Ripple_0002.png");
	auto rotateR = RotateBy::create(0.7f, 15);
	auto rotateL = RotateBy::create(0.7f, -15);
	auto unrotateR = rotateR->reverse();
	auto unrotateL = rotateL->reverse();
	auto delay = DelayTime::create(0.5f);
	auto sequeence = Sequence::create(rotateR, delay, unrotateR, rotateL, delay, unrotateL, NULL);
	bodySprite->runAction(RepeatForever::create(sequeence));
}

CatOfEat::~CatOfEat()
{
	this->unscheduleUpdate();
}
void CatOfEat::update(float dt)
{
	if (collisionWithHero())
	{
		if (!isRunAction)
		{
			this->stopAllActions();
			this->unscheduleUpdate();
			bodySprite->setDisplayFrame(effectFrame);
			bodySprite->runAction(ScaleTo::create(0.01f, 0.3));
			ScaleBy* scaleBy = ScaleBy::create(0.25f, 2.0f, 2.0f);
			this->runAction(Sequence::create
				(scaleBy, CallFunc::create(this, callfunc_selector(CatOfEat::setNoVisible)), NULL));
			isRunAction = true;
		}
	}
}

void CatOfEat::launchInmap()
{
	this->scheduleUpdate();
}


bool FkOfEat::init()
{
	return true;
}
FkOfEat::FkOfEat()
{
	bodySprite = Sprite::createWithSpriteFrame(SpriteFrameCache::
		getInstance()->getSpriteFrameByName("Trap_01_06.png"));
	bodySprite->setAnchorPoint(Point::ZERO);
	bodySprite->setPosition(Point::ZERO);
	this->addChild(bodySprite);
	setType(eFK);
	isChanged = false;
	auto jumpby = JumpBy::create(20.0f, Point(0.0f, 0.0f), 5.0f, 20);
	bodySprite->runAction(RepeatForever::create(jumpby));
}
FkOfEat::~FkOfEat()
{
	this->unscheduleUpdate();
}
void FkOfEat::update(float dt)
{
	if (collisionWithHero())
	{
		if (!isRunAction)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("jelly.wav");
			isRunAction = true;
			bodySprite->runAction(Animate::create
				(AnimationManager::getInstrans()->getAnimation(coinFlyAnimation)));

			MoveBy* moveBy = MoveBy::create(0.3f, Point(1000, 0));
			JumpBy* jumpBy = JumpBy::create(15.0f, Point(1800.0f, 100.0f), 200.0f, 20);

			CallFunc* callFunc = CallFunc::create(this, callfunc_selector(FkOfEat::callBack));

			CCSequence * sequence = CCSequence::create(moveBy, callFunc, jumpBy, NULL);
			this->runAction(sequence);
		}

		if (isChanged)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jelly.wav");
			bodySprite->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("add500.png"));
			this->cleanup();
			auto delay = DelayTime::create(1.0f);
			auto callFunc = CallFunc::create(this, callfunc_selector(FkOfEat::dieCallBack));
			auto sequeence = Sequence::create(delay, callFunc,NULL);
			this->runAction(sequeence);
			
		}
	}
}
void FkOfEat::launchInmap()
{
	this->scheduleUpdate();
}

void FkOfEat::dieCallBack()
{
	GameMap::getInstrance()->removeChild(this, true);
}

void FkOfEat::callBack()
{
	isChanged = true;
}