#include "Hero.h"
Hero* Hero::_instrans;
Hero::Hero()
{
	isRunning = false;
	isJumping = false;
	heroFace = false;
	isDead = false;
	isReJump = false;
	heroState = eRight;
	isDownRun = false;
	isInSky = false;
	normalStandFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Character_HJT_15.png");
	downRunSprite = SpriteFrameCache::getInstance()->getSpriteFrameByName("Character_HJT_20.png");
	upSpeed = 0;
	groundSurport = GRAVITY;
	gravity = GRAVITY;
	runSpeed = RUNSPEED;

	_instrans = this;
}
Hero::~Hero()
{

}

Hero* Hero::getInstrance()
{
	if (_instrans != nullptr)
		return _instrans;
	return nullptr;
}
Hero* Hero::create()
{
	Hero* hero = new Hero();
	if (hero&&hero->heroInit())
	{
		hero->autorelease();
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return NULL;

}
bool Hero::heroInit()
{
	heroBody = Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName("Character_HJT_15.png"));
	heroBody->setAnchorPoint(Point::ZERO);
	heroBody->setPosition(Point::ZERO);
	this->addChild(heroBody);
	//setState(eNormalRight);
	return true;
}

void Hero::resetGroundSurport()
{
	groundSurport = GRAVITY;
}

void Hero::clearGroundSurport()
{
	groundSurport = 0;
}
void Hero::resetJumpSpeed()
{
	if (isReJump)
		upSpeed = UPSPEED *0.7;
	else
		upSpeed = UPSPEED;
	clearGroundSurport();
}

void Hero::clearIumpSpeed()
{
	upSpeed = 0;
	resetGroundSurport();
}
void Hero::setState(HeroState state)
{
	heroState = state;
	Animate* animate;
	CCActionInterval *blinkAction;
	heroBody->stopAllActions();
	switch (state)
	{

	//������
	case eDownRun:
		heroBody->setDisplayFrame(downRunSprite);
		isDownRun = true;
		break;
	//գ��
	case eBlink:
		blinkAction = CCBlink::create(4, 20);
		heroBody->runAction(blinkAction);
		break;
	//������
	case eRight:
		if (heroFace != false)
		{
			heroFace = false;
		}
		heroBody->setFlippedX(false);
		animate = Animate::create(AnimationManager::getInstrans()->getAnimation(runAnimation));
		heroBody->runAction(RepeatForever::create(animate));
		isRunning = true;
		break;
	//������
	case eLeft:
		if (heroFace != true)
		{
			heroFace = true;
		}
		heroBody->setFlippedX(true);
		animate = Animate::create(AnimationManager::getInstrans()->getAnimation(runAnimation));
		heroBody->runAction(RepeatForever::create(animate));
		isRunning = true;
		break;
	//������
	case eJumpRight:
		if (heroFace != false)
		{
			heroFace = false;
		}
		resetJumpSpeed();//�ṩһ����ʼ�������ϵ��ٶ�
		heroBody->setFlippedX(false);
		animate = Animate::create(AnimationManager::getInstrans()->getAnimation(jumpAnimation));
		heroBody->runAction(animate);
		break;
	//������
	case eJumpLeft:
		if (heroFace != true)
		{
			heroFace = true;
		}
		resetJumpSpeed();//�ṩһ����ʼ�������ϵ��ٶ�
		heroBody->setFlippedX(true);
		animate = Animate::create(AnimationManager::getInstrans()->getAnimation(jumpAnimation));
		heroBody->runAction(animate);
		break;
	//������ ����
	case eReJumpLeft:
		if (heroFace != true)
		{
			heroFace = true;
		}
		resetJumpSpeed();//�ṩһ����ʼ�������ϵ��ٶ�
		heroBody->setFlippedX(true);
		animate = Animate::create(AnimationManager::getInstrans()->getAnimation(reJumpAnimation));
		heroBody->runAction(animate);
		break;
	//������ ����
	case eReJumpRight:
		if (heroFace != false)
		{
			heroFace = false;
		}
		resetJumpSpeed();//�ṩһ����ʼ�������ϵ��ٶ�
		heroBody->setFlippedX(false);
		animate = Animate::create(AnimationManager::getInstrans()->getAnimation(reJumpAnimation));
		heroBody->runAction(animate);
		break;
	//����
	case eNormalLeft:
		if (heroFace != true)
		{
			heroFace = true;
		}
		isRunning = false;
		heroBody->setFlippedX(true);
		heroBody->setDisplayFrame(normalStandFrame);
		break;
	//����
	case eNormalRight:
		if (heroFace != false)
		{
			heroFace = false;
		}
		isRunning = false;
		heroBody->setFlippedX(false);
		heroBody->setDisplayFrame(normalStandFrame);
		break;
	default:
		break;
	}
}
