#include "LoadingScene.h"
#include "MainMenu.h"
#include "StoreListScene.h"

Scene* LoadingScene::createScene()
{
	Scene* scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoadingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("r_bgm_01.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("r_bgm_02.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("r_bgm_03.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("r_bgm_04.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("addScore.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("r_alert.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("r_jump.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("r_landing.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("r_second_jump_big_boy.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("u_btn_click.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("u_btn_click_item.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("u_get_coin.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("jelly.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("r_second_jump_boy.wav");
	

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/store.plist");

	auto bgPic = Sprite::create("image/bg_load.jpg");
	bgPic->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	this->addChild(bgPic);

	auto loadLabel = Label::createWithSystemFont("Loading", "Arial", 40);
	loadLabel->setPosition(Point(WINSIZE.width / 2 - 30, WINSIZE.height / 2 + 30));
	this->addChild(loadLabel, 1);
	

	percentLabel = Label::createWithSystemFont("0%", "Arial", 40);
	percentLabel->setPosition(Point(WINSIZE.width / 2 + 100, WINSIZE.height / 2 + 30));
	this->addChild(percentLabel, 1);

	loadProgress = ProgressTimer::create(Sprite::create("image/loadingbar.png"));
	loadProgress->setType(ProgressTimer::Type::BAR);
	loadProgress->setBarChangeRate(Point(1, 0));
	loadProgress->setMidpoint(Point(0, 1));
	loadProgress->setPercentage(75);
	loadProgress->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	this->addChild(loadProgress, 1);

	num = 0;
	
	Director::getInstance()->getTextureCache()->addImageAsync("image/hero.png", CC_CALLBACK_1(LoadingScene::loadingTextureCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("image/background1.png", CC_CALLBACK_1(LoadingScene::loadingTextureCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("image/background2.png", CC_CALLBACK_1(LoadingScene::loadingTextureCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("image/effect.png", CC_CALLBACK_1(LoadingScene::loadingTextureCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("image/cat.png", CC_CALLBACK_1(LoadingScene::loadingTextureCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("image/ui_font.png", CC_CALLBACK_1(LoadingScene::loadingTextureCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("image/dialog.png", CC_CALLBACK_1(LoadingScene::loadingTextureCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("image/main_menu.png", CC_CALLBACK_1(LoadingScene::loadingTextureCallBack, this));

	_loadingAudioThread = new std::thread(&LoadingScene::loadingAudio, this);

	return true;
}

void LoadingScene::loadingAudio()
{
	
}
void LoadingScene::loadingTextureCallBack(Texture2D * texture)
{
	switch (num++)
	{
	case 0:
		
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/hero.plist");
		break;
	case 1:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/background1.plist");
		break;
	case 2:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/background2.plist");
		break;
	case 3:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/effect.plist");
		break;
	case 4:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/cat.plist");
		break;
	case 5:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/ui_font.plist");
		break;
	case 6:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/dialog.plist");
		break;
	case 7:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/main_menu.plist");
		break;
	default:
		break;
	}
	if (num == 8)
	{
		///scene = GameLayer::createScene();
		scene = MainMenu::createScene();
		//StoreListScene::runTheScene();
		Director::getInstance()->replaceScene(scene);
	}

	int per = num / 7 * 100;
	percentLabel->setString(StringUtils::format("%d %%",per));
}

void LoadingScene::onExit()
{
	
	Layer::onExit();
	_loadingAudioThread->join();
	CC_SAFE_DELETE(_loadingAudioThread);
}