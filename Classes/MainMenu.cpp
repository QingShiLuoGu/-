#include "MainMenu.h"
#include "CommonData.h"
#include "GameLayer.h"
#include "StoreListScene.h"
Scene* MainMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenu::create();
	scene->addChild(layer);
	return scene;
}
bool MainMenu::init()
{
	if (!Layer::init())
		return false;
	SpriteFrame *spriteFrame;
	Animation *animation = Animation::create();
	String * frameUri;
	for (int i = 1; i < 4; i++)
	{
		frameUri = String::createWithFormat("Ui_Role_Sq_0%d.png", i);
		spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameUri->getCString());
		if (spriteFrame != nullptr)
			animation->addSpriteFrame(spriteFrame);
	}
	for (int i = 2; i >= 1; i--)
	{
		frameUri = String::createWithFormat("Ui_Role_Sq_0%d.png", i);
		spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameUri->getCString());
		if (spriteFrame != nullptr)
			animation->addSpriteFrame(spriteFrame);
	}
	animation->setDelayPerUnit(0.05f);
	animation->setRestoreOriginalFrame(true);//设置在动作结束后恢复至初始帧
	animation->retain();

	auto bgPic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("Background_13.png"));
	bgPic->setAnchorPoint(Point::ZERO);
	bgPic->setPosition(Point(0, 0));

	this->addChild(bgPic);

	auto sprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Ui_Role_Sq_01.png"));
	sprite->setPosition(WINSIZE.width/4,WINSIZE.height/2);
	this->addChild(sprite);

	auto delay = DelayTime::create(2.0f);
	auto animate = Animate::create(animation);
	auto sequeence = Sequence::create(delay,animate,NULL);
	sprite->runAction(RepeatForever::create(sequeence));

	auto pet = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("UI_Pet_03.png"));
	pet->setPosition(WINSIZE.width/2-95,WINSIZE.height/2-70);
	pet->setFlippedX(true);
	auto jump = JumpBy::create(10.0f, Point(0, 0), 5.00f, 10);
	pet->runAction(RepeatForever::create(jump));
	this->addChild(pet);

	auto item1 = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(
		"game_01.png")), Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(
		"game_02.png")), CC_CALLBACK_1(MainMenu::startGameMenuCallback, this));

	auto item2 = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(
		"shop_01.png")), Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(
		"shop_02.png")), CC_CALLBACK_1(MainMenu::shopCallback, this));

	item1->setPosition(0,100);
	item2->setPosition(0,0);
	auto menu = Menu::create(item1,item2,NULL);
	menu->setPosition(WINSIZE.width / 2 + 200, WINSIZE.height / 2-100);
	this->addChild(menu);
	return true;
}

void MainMenu::startGameMenuCallback(Ref* node)
{
	Director::getInstance()->replaceScene(GameLayer::createScene());
}

void MainMenu::shopCallback(Ref* node)
{
	StoreListScene::runTheScene();
}