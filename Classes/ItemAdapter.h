#ifndef ITEMADAPTER
#define ITEMADAPTER
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
class ItemAdapter : public Sprite
{
public:
	static Sprite* createCellItem(const char* name,
		const char* image, const char* price);

};
#endif