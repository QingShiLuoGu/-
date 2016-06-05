#include "bomb.h"
#include "GameLayer.h"
Bomb::Bomb()
{
	mode = 0;
	height1 = WINSIZE.width / 2-200;
	bodySprite = Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName("notitle_02.png"));
	bodySprite->setVisible(true);
	bodySprite->setAnchorPoint(Point::ZERO);
	bodySprite->setPosition(Point::ZERO);
	bombSprite = Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName("effect_map_03.png"));
	bombSprite->setVisible(false);
	bombSprite->setPosition(WINSIZE.width*3.0,0);
	this->setAnchorPoint(Point::ZERO);
	this->addChild(bombSprite);
	this->addChild(bodySprite);

}
Bomb* Bomb::create()
{
	auto bomb = new Bomb();
	if (bomb&&bomb->init())
	{
		bomb->autorelease();
		return bomb;
	}
	CC_SAFE_DELETE(bomb);
	return NULL;
}

void Bomb::update(float dt)
{
	Point heroPosition = Hero::getInstrance()->getPosition();
	this->setPosition(Point(heroPosition.x-180,height1));
}

void Bomb::bombUpdate(float dt)
{
	Point pos = bombSprite->getPosition();
	pos = Point(pos.x-25,pos.y); 
	bombSprite->setPosition(pos);
	if (collisionWithHero())
	{
		this->setTag(123);
		GameLayer::getInstrance()->isDead = true;
	}
}
void Bomb::playEffect()
{
	SimpleAudioEngine::getInstance()->playEffect("r_alert.wav");
}

void Bomb::afterAlert()
{
	bombSprite->setVisible(true);
	this->schedule(schedule_selector(Bomb::bombUpdate));
	
}

bool Bomb::collisionWithHero()
{
	Size heroSize = Hero::getInstrance()->heroBody->getContentSize();
	Point heroPos = Hero::getInstrance()->getPosition();
	Size pSize = bombSprite->getContentSize();
	Point pPos = Point(bombSprite->getPosition().x+this->getPosition().x,this->getPosition().y);
	Rect heroRect = Rect(heroPos.x + 10, heroPos.y + 10, heroSize.width - 20, heroSize.height - 20);
	Rect pRect = Rect(pPos.x + 10, pPos.y + 10, pSize.width - 20, pSize.height - 20);

	if (heroPos.x - pPos.x > 180)
	{
		this->cleanup();
		GameLayer::getInstrance()->mainLayer->removeChild(this);
	}

	if (heroRect.intersectsRect(pRect))
	{
		return true;
	}
	return false;
}


bool Bomb::init()
{
	bodySprite->setOpacity(0);
	//Animate
	auto fadeIn = FadeIn::create(1.0f);
	auto fadeOut = fadeIn->reverse();
	auto callfunc = CallFunc::create(this,callfunc_selector(Bomb::playEffect));
	auto callfunc2 = CallFunc::create(this, callfunc_selector(Bomb::afterAlert));
	auto delay = DelayTime::create(0.8f);
	auto sequeence = Sequence::create(fadeIn, delay, fadeOut, delay, fadeIn, delay, fadeOut, NULL);
	bodySprite->runAction(RepeatForever::create(sequeence));
	bodySprite->runAction(Sequence::create(callfunc,delay,callfunc,callfunc2,NULL));
	this->scheduleUpdate();
	return true;
}