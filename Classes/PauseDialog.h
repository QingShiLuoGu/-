#ifndef PauseDialog_H
#define PauseDialog_H
#include "cocos2d.h"
#include "CommonData.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
class PauseDialog :public Layer
{
public:
	PauseDialog();
	virtual bool init();
	static Scene* createScene(CCRenderTexture *sqr, bool isFlip);
	CREATE_FUNC(PauseDialog);
	void touchReStart(Ref* node);
	void touchGoOn(Ref* node);
	void touchTop(Ref* node);

};
#endif