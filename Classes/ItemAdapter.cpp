#include "ItemAdapter.h"

Sprite* ItemAdapter::createCellItem(const char* name,
	const char* image, const char* price)
{
	auto nameLabel = Label::createWithSystemFont(name, "Helvetica", 20.0);
	auto nameSprite = Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName("UI_Mounts_10_03.png"));
	auto itemSprite = Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName(image));
	auto priceSprite = Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName("UI_Mounts_10_07.png"));
	auto priceNumber = Label::createWithSystemFont(name, "Helvetica", 25.0);
	priceNumber->setAnchorPoint(Point::ZERO);
	priceNumber->setPosition(Point(100, 7));
	priceNumber->setColor(Color3B::BLACK);
	priceNumber->setString(price);
	priceSprite->addChild(priceNumber);
	auto sprite = Sprite::create();
	nameLabel->setPosition(85,15);
	nameSprite->addChild(nameLabel);
	nameSprite->setAnchorPoint(Point::ZERO);
	nameSprite->setPosition(0, 250);
	sprite->addChild(nameSprite);
	itemSprite->setAnchorPoint(Point::ZERO);
	itemSprite->setPosition(0,70);
	sprite->addChild(itemSprite);
	priceSprite->setAnchorPoint(Point::ZERO);
	priceSprite->setPosition(-5,0);
	sprite->addChild(priceSprite);
	return sprite;
}