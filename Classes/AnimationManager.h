#ifndef AnimationManager_H
#define AnimationManager_H
#include "cocos2d.h"
#include "GameEnum.h"
USING_NS_CC;
class AnimationManager
{
public:
	static AnimationManager* getInstrans();
	Animate* createAnimate(AnimationType type);
	Animation* createAnimation(AnimationType type);
	void addAllAnimationCache();
	Animation* getAnimation(AnimationType type);
private:
	AnimationManager();
	~AnimationManager();
	
	std::vector<AnimationType> allTypes;
	static AnimationManager* _instrans;
	void addAnimationCache(std::vector<AnimationType> allTypes);
	
};

#endif