#ifndef LOADINGSCENE_H
#define LOADINGSCENE_H
#include "cocos2d.h"
#include "CommonData.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "PauseDialog.h"
#include "OverDialog.h"
USING_NS_CC;
class LoadingScene :public Layer
{
public:
	static Scene* createScene();
	void loadingTextureCallBack(Texture2D * texture);
	virtual bool init();
	CREATE_FUNC(LoadingScene);
	int num;
	void loadingAudio();
	void onExit();
	std::thread* _loadingAudioThread;
	ProgressTimer* loadProgress;
	Scene* scene;
	Label* percentLabel;
};

#endif