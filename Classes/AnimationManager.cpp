#include "AnimationManager.h"

AnimationManager *AnimationManager::_instrans = nullptr;
AnimationManager::AnimationManager()
{
	allTypes = {
		runAnimation,
		jumpAnimation,
		reJumpAnimation,
		coinFlyAnimation
	};
	//this->addAnimationCache(allTypes);
}  
AnimationManager::~AnimationManager()
{
}

void AnimationManager::addAllAnimationCache()
{
	addAnimationCache(allTypes);
}

AnimationManager* AnimationManager::getInstrans()
{
	if (_instrans == nullptr)
	{
		_instrans = new AnimationManager();

		return _instrans;
	}
	return _instrans;
}

void AnimationManager::addAnimationCache(std::vector<AnimationType> allTypes)
{
	for (auto type : allTypes)
	{
		std::string animationName = StringUtils::format("%d", type);

		AnimationCache::getInstance()->addAnimation(createAnimation(type), animationName);
	}
}

Animate* AnimationManager::createAnimate(AnimationType type)
{
	Animation* animation = getAnimation(type);
	if (animation)
	{
		return Animate::create(animation);
	}
	return nullptr;
}

Animation* AnimationManager::getAnimation(AnimationType type)
{
	std::string animationName = StringUtils::format("%d", type);
	Animation* animation = AnimationCache::getInstance()->getAnimation(animationName);
	return animation;
}

Animation* AnimationManager::createAnimation(AnimationType type)
{
	SpriteFrame *spriteFrame;
	Animation *animation = Animation::create();
	String * frameUri;

	switch (type)
	{
	case coinFlyAnimation:
		for (int i = 1; i < 5; i++)
		{
			if (i <= 3)
			{
				frameUri = String::createWithFormat("coin_fly_%d.png", i);
			}
			else if (i==4)
				frameUri = String::create("coin_fly_2.png");
			spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameUri->getCString());
			if (spriteFrame != nullptr)
				animation->addSpriteFrame(spriteFrame);
		}
		animation->setLoops(-1);
		animation->setDelayPerUnit(0.11f);
		animation->setRestoreOriginalFrame(false);//设置在动作结束后恢复至初始帧
		break;
	case runAnimation:
		for (int i = 2; i < 14; i++)
		{
			frameUri = String::createWithFormat("Character_HJT_%02d.png", i);
			spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameUri->getCString());
			if (spriteFrame != nullptr)
				animation->addSpriteFrame(spriteFrame);
		}
		animation->setDelayPerUnit(0.06f);
		animation->setRestoreOriginalFrame(true);//设置在动作结束后恢复至初始帧

		break;
	case reJumpAnimation:
		for (int i = 15; i < 20; i++)
		{
			frameUri = String::createWithFormat("Character_HJT_%02d.png", i);
			spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameUri->getCString());
			if (spriteFrame != nullptr)
				animation->addSpriteFrame(spriteFrame);
		}
		animation->setDelayPerUnit(0.1f);
		animation->setRestoreOriginalFrame(true);//设置在动作结束后恢复至初始帧
		break;
	case jumpAnimation:
		for (int i = 1; i < 4; i++)
		{
			frameUri = String::createWithFormat("Character_HJT_jump_%d.png", i);
			spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameUri->getCString());
			if (spriteFrame != nullptr)
				animation->addSpriteFrame(spriteFrame);
		}
		animation->setDelayPerUnit(0.2f);
		animation->setRestoreOriginalFrame(true);//设置在动作结束后恢复至初始帧
		break;
	}
	return animation;
}