#include "GameLayer.h"

GameLayer* GameLayer::_instrance;

GameLayer* GameLayer::getInstrance()
{
	if (_instrance != nullptr)
		return _instrance;
	return nullptr;
}
GameLayer::GameLayer()
{
	score = 0;
	distance = 0;
	isDead = false;
	isRightKeyDown = false;
	isLeftKeyDown = false;
	isSpaceKeyDown = false;
	winSize = Director::getInstance()->getWinSize();
	mapFollowPoint = winSize.width / 2 - 300;
	_instrance = this;
}

Scene* GameLayer::createScene()
{
	Scene* scene = Scene::create();
	Layer *layer = GameLayer::create();
	scene->addChild(layer);
	return scene;
}
bool GameLayer::init()
{
	if (!Layer::create())
	{
		return false;
	}

	initMapAndHero();
	initUI();
	AnimationManager::getInstrans()->addAllAnimationCache();
	//键盘事件注册
	auto keyEventListen = EventListenerKeyboard::create();
	keyEventListen->onKeyPressed = CC_CALLBACK_2(GameLayer::onKeyPressed, this);
	keyEventListen->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyEventListen, this);
	//this->setTouchEnabled(true);
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);

	int index = getRandNumber(1,4);
	std::string str = StringUtils::format("r_bgm_0%d.wav",index);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(str.c_str(), true);

	this->scheduleUpdate();

	hero->setState(eRight);
	isRightKeyDown = true;

	return true;
}


void GameLayer::paunseGame()
{
	this->unscheduleUpdate();
}
void GameLayer::initUI()
{
	Sprite* bg1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->
		getSpriteFrameByName("UI_GAM~4_05.png"));
	Sprite* performance = Sprite::createWithSpriteFrame(SpriteFrameCache::
		getInstance()->getSpriteFrameByName("ui_font_per.png"));
	performance->setAnchorPoint(Point::ZERO);
	performance->setPosition(Point(10, 5));
	Sprite* score = Sprite::createWithSpriteFrame(SpriteFrameCache::
		getInstance()->getSpriteFrameByName("ui_font_score.png"));
	score->setAnchorPoint(Point::ZERO);
	score->setPosition(Point(200, 5));
	perfomaceLabel = Label::createWithCharMap("image/number_02.png", 33, 25, '0');
	perfomaceLabel->setAnchorPoint(Point::ZERO);
	perfomaceLabel->setPosition(Point(100,10));
	perfomaceLabel->setString("123");

	bg1->addChild(perfomaceLabel);
	bg1->addChild(performance);
	bg1->addChild(score);
	bg1->setAnchorPoint(Point::ZERO);
	bg1->setPosition(0, winSize.height - 50);



	Sprite* bg2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->
		getSpriteFrameByName("UI_GAM~4_05.png"));
	Sprite* distance = Sprite::createWithSpriteFrame(SpriteFrameCache::
		getInstance()->getSpriteFrameByName("ui_font_dis.png"));
	distance->setAnchorPoint(Point::ZERO);
	distance->setPosition(Point(10,5));
	Sprite* meter = Sprite::createWithSpriteFrame(SpriteFrameCache::
		getInstance()->getSpriteFrameByName("ui_font_meter.png"));
	meter->setAnchorPoint(Point::ZERO);
	meter->setPosition(Point(200, 5));

	distanceLabel = Label::createWithCharMap("image/number_02.png", 33, 25, '0');
	distanceLabel->setAnchorPoint(Point::ZERO);
	distanceLabel->setPosition(Point(100, 7));
	distanceLabel->setString("456");
	bg2->addChild(distanceLabel);
	bg2->addChild(distance);
	bg2->addChild(meter);
	bg2->setAnchorPoint(Point::ZERO);
	bg2->setPosition(250, winSize.height - 50);

	this->addChild(bg1);
	this->addChild(bg2);

	auto pauseItem = MenuItemSprite::create(Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName("ui_game_n_10.png")),
		Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName("ui_game_n_101.png")),
		CC_CALLBACK_1(GameLayer::pauseCallback,this));
	auto menu = Menu::create(pauseItem,NULL);
	menu->setPosition(WINSIZE.width -50,WINSIZE.height-50);
	this->addChild(menu);

	auto downBtnSprite = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("UI_GAM~4_03.png"));
	auto downBtn = ControlButton::create(downBtnSprite);
	downBtn->setPreferredSize(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("UI_GAM~4_03.png"))->getContentSize());
	downBtn->setPosition(80, WINSIZE.height / 2 - 220);
	downBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::downBtnCallBack), Control::EventType::TOUCH_UP_INSIDE);
	downBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::downBtnCallBack), Control::EventType::TOUCH_DOWN);
	this->addChild(downBtn);

	auto jumpBtnSprite = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("UI_GAM~4_04.png"));
	auto jumpBtn = ControlButton::create(jumpBtnSprite);
	jumpBtn->setPreferredSize(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("UI_GAM~4_04.png"))->getContentSize());
	jumpBtn->setPosition(WINSIZE.width - 80, WINSIZE.height / 2 - 220);
	jumpBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::jumpBtnCallBack), Control::EventType::TOUCH_DOWN);
	this->addChild(jumpBtn);
}

void GameLayer::pauseCallback(Ref* node)
{
	isRightKeyDown = false;
	isLeftKeyDown = false;
	isSpaceKeyDown = false;
	hero->setState(eNormalRight);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	RenderTexture* renderTexture = RenderTexture::create(WINSIZE.width, WINSIZE.height);
	renderTexture->retain();
	Scene *s = Director::sharedDirector()->getRunningScene();
	renderTexture->begin();
	s->visit();
	renderTexture->end();
	Scene* pause = PauseDialog::createScene(renderTexture, true);
	Director::getInstance()->pushScene(pause);
}

int GameLayer::getRandNumber(int min,int max)
{
	srand((int)time(0));
	int a = random(min,max);
	return a;
}
void GameLayer::initMapAndHero()
{
	gameMap = GameMap::create("image/map/MyKuPaoMap1.tmx");
	mapSize = CCSizeMake(gameMap->getMapSize().width*gameMap->getTileSize().width,
		gameMap->getMapSize().height*gameMap->getTileSize().height);
	gameMap->setPosition(Point(0, 0));
	hero = Hero::create();
	hero->setAnchorPoint(Point(0, 0));
	hero->setPosition(gameMap->getHeroBirthPlace());

	int index = getRandNumber(1,6);
	std::string str = StringUtils::format("Background_1%d.png",index);
	auto bgPic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName(str));
	bgPic->setAnchorPoint(Point::ZERO);
	bgPic->setPosition(Point(0, 20));

	this->addChild(bgPic);

	mainLayer = Layer::create();
	mainLayer->addChild(gameMap);
	mainLayer->addChild(hero);
	mainLayer->setPosition(Point(0, 0));
	this->addChild(mainLayer);

}


void GameLayer::downBtnCallBack(Ref* p, Control::EventType type)
{
	switch (type)
	{
	case cocos2d::extension::Control::EventType::TOUCH_DOWN:
		hero->setState(eDownRun);
		break;
	case cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE:
		hero->isDownRun = false;
		hero->setState(eRight);
		break;
	default:
		break;
	}
}
void GameLayer::jumpBtnCallBack(Ref* p, Control::EventType type)
{
	isSpaceKeyDown = true;
	hero->isInSky = true;

	if ((hero->groundSurport != 0))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("r_jump.wav");
		if (!hero->heroFace)
			hero->setState(eJumpRight);
		else
			hero->setState(eJumpLeft);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("r_second_jump_boy.wav");
		oldState = hero->heroState;
		hero->isReJump = true;
		if (!hero->heroFace)
			hero->setState(eReJumpRight);
		else
			hero->setState(eReJumpLeft);
	}

}
void GameLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_P:
		log("%f", hero->getPosition().x);
		hero->setState(eDownRun);
		break;
	case EventKeyboard::KeyCode::KEY_D:
		if (isLeftKeyDown)//如果同时按下了A，那么此键无效
			return;
		isRightKeyDown = true;
		hero->setState(eRight);
		break;
	case EventKeyboard::KeyCode::KEY_A:
		if (isRightKeyDown)
			return;
		isLeftKeyDown = true;
		hero->setState(eLeft);
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		isSpaceKeyDown = true;
		//if (hero->groundSurport==0)//不能在没有支持力的时候跳跃
		//	return;
		hero->isInSky = true;

		if ((hero->groundSurport != 0))
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("r_jump.wav");
			if (!hero->heroFace)
				hero->setState(eJumpRight);
			else
				hero->setState(eJumpLeft);
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("r_second_jump_boy.wav");
			oldState = hero->heroState;
			hero->isReJump = true;
			if (!hero->heroFace)
				hero->setState(eReJumpRight);
			else
				hero->setState(eReJumpLeft);
		}

		break;
	}
}

void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_P:
		hero->isDownRun = false;
		hero->setState(eRight);
		break;

	case EventKeyboard::KeyCode::KEY_D:
		isRightKeyDown = false;
		hero->setState(eNormalRight);
		break;
	case EventKeyboard::KeyCode::KEY_A:
		isLeftKeyDown = false;
		hero->setState(eNormalLeft);
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		isSpaceKeyDown = false;
		break;
	}
}
void GameLayer::collisionV()
{
	Size heroSize = hero->heroBody->getContentSize();
	Point currentPos = hero->getPosition();

	//头顶检测
	for (int i = 0; i < 60; i += 8)
	{
		Point collisionPos = Point(currentPos.x + 20 + i, currentPos.y + heroSize.height - 30);
		Point collisionTileCoord = gameMap->positionToTileCoord(collisionPos);
		TileType type = gameMap->tileTypeforPos(collisionTileCoord);
		switch (type)
		{
		case eScare:
			isDead = true;
			break;
		case eKnife:
			break;
		case eLand:
			break;
		case eGroud:
			break;
		case eDiao:

			break;
		case eBox:
			break;
		case eCoin:
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("u_get_coin.wav");
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("addScore.wav");
			gameMap->getCoinLayer()->removeTileAt(collisionTileCoord);
			score++;
			break;
		case eTile_none:
			break;
		default:
			break;
		}
	}

	//脚底检测
	for (int i = 0; i < 32; i += 4)
	{
		Point collisionPos = Point(currentPos.x + heroSize.width - 40 + i, currentPos.y);
		Point collisionTileCoord = gameMap->positionToTileCoord(collisionPos);
		collisionTileCoord.y += 1;
		TileType type = gameMap->tileTypeforPos(collisionTileCoord);
		switch (type)
		{
					case eScare:
			isDead = true;
			break;
		case eKnife:
			break;
		case eLand:
			break;
		case eGroud:
			if (hero->upSpeed > 0)
				return;
			hero->clearIumpSpeed();
			if (hero->isInSky)
			{
				hero->isInSky = false;
				hero->isReJump = false;
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("r_landing.wav");
				
				isRightKeyDown = true;//此处为了使英雄自动奔跑

				if (isLeftKeyDown)
					hero->setState(eLeft);
				else if (isRightKeyDown)
					hero->setState(eRight);
			}
			return;
			break;
		case eBox:
			hero->clearIumpSpeed();
			break;
		case eTile_none:
			break;
		default:
			break;
		}
	}

	for (int i = 0; i < 32; i += 4)
	{
		Point collisionPos = Point(currentPos.x + 40 - i, currentPos.y);
		Point collisionTileCoord = gameMap->positionToTileCoord(collisionPos);
		collisionTileCoord.y += 1;
		TileType type = gameMap->tileTypeforPos(collisionTileCoord);
		switch (type)
		{
		case eKnife:
			break;
		case eLand:
			break;
		case eGroud:
			if (hero->upSpeed > 0)
				return;
			hero->clearIumpSpeed();
			if (hero->isInSky)
			{
				hero->isInSky = false;
				hero->isReJump = false;
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("r_landing.wav");
				if (isLeftKeyDown)
					hero->setState(eLeft);
				else if (isRightKeyDown)
					hero->setState(eRight);
			}
			return;
			break;
		case eBox:
			hero->clearIumpSpeed();
			return;
			break;
		case eTile_none:
			break;
		default:
			break;
		}
	}

	hero->clearGroundSurport();
}

void GameLayer::collisionH()
{
	Point currentPos = hero->getPosition();
	Size heroSize = hero->heroBody->getContentSize();
	Point collisionPos = Point(currentPos.x + heroSize.width, currentPos.y);
	Point collisionTilCoord = gameMap->positionToTileCoord(collisionPos);
	for (int i = 0; i < 48; i = i + 4)
	{
		collisionPos = Point(currentPos.x + heroSize.width - 16, currentPos.y + i);
		collisionTilCoord = gameMap->positionToTileCoord(collisionPos);
		TileType type = gameMap->tileTypeforPos(collisionTilCoord);
		switch (type)
		{
		case eScare:
			isDead = true;
			break;
		case eKnife:
			hero->setPosition(Point(hero->getPosition().x-1,hero->getPosition().y));
			break;
		case eBox:
			return;
			break;
		case eDiao:
			if (!hero->isDownRun)
				hero->setPosition(Point(hero->getPosition().x - 1, hero->getPosition().y));
			break;
		case eCoin:
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("u_get_coin.wav");
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("addScore.wav");
			gameMap->getCoinLayer()->removeTileAt(collisionTilCoord);
			score++;
			break;
		case eTile_none:
			break;
		default:
			break;
		}

		collisionTilCoord = gameMap->positionToTileCoord(Point(currentPos.x + 16, currentPos.y + i));
		type = gameMap->tileTypeforPos(collisionTilCoord);
		switch (type)
		{
		case eScare:
			isDead = true;
			break;
		case eKnife:
		case eBox:
			hero->setPosition(Point(currentPos.x + 10, currentPos.y));
			return;
			break;
		case eDiao:
			if (!hero->isDownRun)
				hero->setPosition(Point(hero->getPosition().x - 1, hero->getPosition().y));
			break;
		case eCoin:
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("u_get_coin.wav");
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("addScore.wav");
			gameMap->getCoinLayer()->removeTileAt(collisionTilCoord);
			score++;
			break;
		case eTile_none:
			break;
		default:
			break;
		}
	}
}

void GameLayer::mapRun(Point position)
{
	position = hero->getPosition();
	float x = MAX(position.x, mapFollowPoint);
	x = MIN(x, mapSize.width - winSize.width / 2 - 60);
	float xx = mapFollowPoint - x;
	mainLayer->setPosition(Point(xx, 0));
	
}

void GameLayer::freshScore(Point heroPos)
{
	distance = positon.x / 10;
	distanceLabel->setString(StringUtils::format("%03d",distance));
	perfomaceLabel->setString(StringUtils::format("%03d", score));

}
void GameLayer::update(float a)
{
	positon = hero->getPosition();
	if (positon.x > mapSize.width - winSize.width / 2 - 60)
	{
		hero->setState(eNormalRight);
		isRightKeyDown = false;
	}
	mapRun(positon);
	freshScore(positon);
	if (isDead)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();

		RenderTexture* renderTexture = RenderTexture::create(WINSIZE.width, WINSIZE.height);
		renderTexture->retain();
		Scene *s = Director::getInstance()->getRunningScene();
		renderTexture->begin();
		s->visit();
		renderTexture->end();
		Scene* scene = OverDialog::createScene(renderTexture, true);
		Director::getInstance()->pushScene(scene);
	}

	
	if (isRightKeyDown)
	{
		positon.x += hero->runSpeed;
	}

	if (isLeftKeyDown)
	{
		positon.x -= hero->runSpeed;
	}

	hero->upSpeed -= hero->gravity - hero->groundSurport;
	positon.y += hero->upSpeed;

	if (positon.y < 5)
	{
		isDead = true;
	}
	if (positon.y > 450)
		positon.y = 450;
	if (positon.y > mapSize.height - 48)
	{
		positon.y = mapSize.height - 48;
	}
	hero->setPosition(positon);
	collisionV();
	collisionH();
}