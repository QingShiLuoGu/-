#ifndef MainMenu_H
#define Main_Menu_H
#include "cocos2d.h"
USING_NS_CC;
class MainMenu :public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(MainMenu);
	virtual bool init();
private:
	void startGameMenuCallback(Ref* node);
	void shopCallback(Ref* node);

};

#endif