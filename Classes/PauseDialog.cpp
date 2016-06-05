#include "PauseDialog.h"

PauseDialog::PauseDialog()
{
}
Scene* PauseDialog::createScene(CCRenderTexture *sqr, bool isFlip)
{
	auto scene = Scene::create();
	auto layer = PauseDialog::create();

	CCSprite *_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
	_spr->setPosition(ccp(WINSIZE.width / 2, WINSIZE.height / 2));
	_spr->setFlipY(isFlip);
	_spr->setColor(Color3B::GRAY);
	scene->addChild(_spr);

	scene->addChild(layer);
	return scene;
}
bool PauseDialog::init()
{
	if (!Layer::init())
		return false;
	auto bg1 = Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName("ui_font_07_10.png"));
	auto item1 = MenuItemSprite::create(Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName("ui_font_07_15.png")),
		Sprite::createWithSpriteFrame
		(SpriteFrameCache::getInstance()->getSpriteFrameByName("ui_font_07_13.png")),
		CC_CALLBACK_1(PauseDialog::touchGoOn,this));
	auto item2 = MenuItemSprite::create(Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName("ui_font_07_18.png")),
		Sprite::createWithSpriteFrame
		(SpriteFrameCache::getInstance()->getSpriteFrameByName("ui_font_07_21.png")),
		CC_CALLBACK_1(PauseDialog::touchReStart, this));
	auto item3 = MenuItemSprite::create(Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName("ui_font_07_03.png")),
		Sprite::createWithSpriteFrame
		(SpriteFrameCache::getInstance()->getSpriteFrameByName("ui_font_07_07.png")),
		CC_CALLBACK_1(PauseDialog::touchTop, this));
	item1->setPosition(Point(0, 130));
	item2->setPosition(Point(0,65));
	item3->setPosition(Point(0,0));
	auto menu = Menu::create(item1,item2,item3,NULL);
	menu->setPosition(WINSIZE.width/2-10,WINSIZE.height/2-90);
	bg1->setPosition(Point(WINSIZE.width/2,WINSIZE.height/2));
	this->addChild(bg1);
	this->addChild(menu);
	return true;
}

void PauseDialog::touchReStart(Ref* node)
{
	auto scene = GameLayer::createScene();
	Director::getInstance()->replaceScene(scene);
}
void PauseDialog::touchGoOn(Ref* node)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	Director::getInstance()->popScene();
}
void PauseDialog::touchTop(Ref* node)
{

}