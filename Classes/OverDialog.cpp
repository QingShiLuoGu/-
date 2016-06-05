#include "OverDialog.h"
#include "GameLayer.h"

OverDialog::OverDialog()
{

}
Scene* OverDialog::createScene(CCRenderTexture *sqr, bool isFlip)
{
	auto scene = Scene::create();
	auto layer = OverDialog::create();
	

	CCSprite *_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
	_spr->setPosition(ccp(WINSIZE.width / 2, WINSIZE.height / 2));
	_spr->setFlipY(isFlip);
	_spr->setColor(Color3B::GRAY);
	scene->addChild(_spr);
	scene->addChild(layer);
	return scene;
}
bool OverDialog::init()
{
	if (!Layer::init())
		return false;
	auto bg1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("1_03.png"));
	bg1->setPosition(WINSIZE.width/2,WINSIZE.height/2);
	
	auto item1 = MenuItemSprite::create(Sprite::createWithSpriteFrame
		(SpriteFrameCache::getInstance()->getSpriteFrameByName("ui_game_n_05_03.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->
		getSpriteFrameByName("ui_game_n_03_03.png")),CC_CALLBACK_1(OverDialog::touchPlayAgain,this));
	auto item2 = MenuItemSprite::create(Sprite::createWithSpriteFrame
		(SpriteFrameCache::getInstance()->getSpriteFrameByName("ui_game_n_06_06.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->
		getSpriteFrameByName("ui_game_n_06_03.png")), CC_CALLBACK_1(OverDialog::touchFuhuo, this));
	auto menu = Menu::create(item1,item2,NULL);
	item1->setPosition(0,0);
	item2->setPosition(220,0);
	menu->setPosition(WINSIZE.width/3+50,WINSIZE.height/5);
	this->addChild(menu);

	this->addChild(bg1);
	return true;
}

void OverDialog::touchPlayAgain(Ref* node)
{
	Director::getInstance()->popScene();
	auto scene = GameLayer::createScene();
	Director::getInstance()->replaceScene(scene);
}

void OverDialog::touchFuhuo(Ref* node)
{
	GameLayer::getInstrance()->mainLayer->removeChildByTag(123);
	GameLayer::getInstrance()->isDead = false;
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("r_bgm_03.wav", true);
	Director::getInstance()->popScene();
}
