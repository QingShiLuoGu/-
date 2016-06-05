#ifndef OverDialog_H
#define OverDialog_H
#include "cocos2d.h"
#include "CommonData.h"
USING_NS_CC;
class OverDialog :public Layer
{
public:
	OverDialog();
	virtual bool init();
	static Scene* createScene(CCRenderTexture *sqr, bool isFlip);
	CREATE_FUNC(OverDialog);
	void touchPlayAgain(Ref* node);
	void touchFuhuo(Ref* node);
};
#endif