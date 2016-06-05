#include "StoreListScene.h"
#include "CustomTableViewCell.h"
#include "ItemAdapter.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

void StoreListScene::runTheScene()
{
	auto scene = Scene::create();
	auto layer = StoreListScene::create();
	scene->addChild(layer);
	Director::getInstance()->replaceScene(scene);
}

bool StoreListScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size winSize = Director::getInstance()->getWinSize();

	auto bg = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Background_13.png"));
	bg->setPosition(winSize.width/2,winSize.height/2);
	this->addChild(bg);


	TableView* tableView = TableView::create(this, Size(540,300));
	tableView->setDirection(extension::ScrollView::Direction::HORIZONTAL);
	tableView->setPosition(winSize.width/2-250,winSize.height/2-150);
	tableView->setDelegate(this);
	this->addChild(tableView);
	tableView->reloadData();

	return true;
}

void StoreListScene::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CCLOG("cell touched at index: %ld", cell->getIdx());
}


Size StoreListScene::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(200,420);
}

TableViewCell* StoreListScene::tableCellAtIndex(TableView *table, ssize_t idx)
{
	auto string = String::createWithFormat("%ld", idx);
	TableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new (std::nothrow) CustomTableViewCell();
		cell->autorelease();
		Sprite* sprite;
		switch (idx)
		{
		case 0:
			sprite = ItemAdapter::createCellItem("motobike 1", "UI_Mounts_01.png", "399");
			break;
		case 1:
			sprite = ItemAdapter::createCellItem("motobike2", "UI_Mounts_03.png", "599");
			break;
		case 2:
			sprite = ItemAdapter::createCellItem("huli", "UI_Mounts_04.png", "899");
			break;
		case 3:
			sprite = ItemAdapter::createCellItem("lion", "UI_Mounts_09.png", "1250");
			break;
		case 4:
			sprite = ItemAdapter::createCellItem("wolf", "UI_Mounts_10.png", "1500");
			break;
		default:
			break;
		}
		cell->addChild(sprite);
	}
	else
	{

	}


	return cell;
}

ssize_t StoreListScene::numberOfCellsInTableView(TableView *table)
{
	return 5;
}
