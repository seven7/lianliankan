﻿#include "GameUtils.h"
#include "GameData.h"
#include "GameScene.h"
USING_NS_CC;


Vec2 GameUtils::pointOffsetCenter(float x, float y){
	auto visibleSize = Director::getInstance()->getVisibleSize();
	return Vec2(visibleSize.width / 2 + x, visibleSize.height / 2 + y);
}

float GameUtils::getXScaleRate(){
	auto size_width = 640.0;
	if(VISIBLE_WIDTH > size_width) 
		size_width = 768.0;
	//if(VISIBLE_WIDTH < size_width) {
	//	return VISIBLE_WIDTH / size_width;
	//}
	return VISIBLE_WIDTH / size_width;
}

float GameUtils::getYScaleRate() {
	auto size_height = 960.0;
	if(VISIBLE_HEIGHT > 960 && VISIBLE_HEIGHT <= 1024.0) 
		size_height =  1024.0;
	else if ( VISIBLE_HEIGHT > 1024.0)
		size_height = 1136.0;
	//if( VISIBLE_HEIGHT < size_height) {
	//	return VISIBLE_HEIGHT / size_height;
	//}
	return VISIBLE_HEIGHT / size_height;
}

float GameUtils::getConScaleFactorX() {
	auto designSize = Size(640, 960);
	if(GameData::getInstance()->getscW() > 640) 
	{
		auto resourceSize = Size(768, 1024);
		return resourceSize.width/designSize.width;
	}
	return 1.0;

}

float GameUtils::getConScaleFactorY() {
	auto designSize = Size(640, 960);
	if(GameData::getInstance()->getscH() <= 960) 
	{
		return 1.0;
	}
	else if(GameData::getInstance()->getscH() > 960 && GameData::getInstance()->getscH() < 1136) 
	{
		return 1024/960;
	}
	return 1136/960;
}


float GameUtils::getSpriteXScaleRate(Sprite* sprite){
	float spriteWidth = sprite->getContentSize().width;
	float scaleRate = VISIBLE_WIDTH / spriteWidth;
	if (scaleRate <= 1){
		return 1;
	}
	else{
		return scaleRate;
	}
}

float GameUtils::getSpriteYScaleRate(Sprite* sprite){
	float spriteHeight = sprite->getContentSize().height;
	float scaleRate = VISIBLE_HEIGHT / spriteHeight;
	if (scaleRate <= 1){
		return 1;
	}
	else{
		return scaleRate;
	}
}

float GameUtils::getPainSpriteXScaleRate(Sprite* sprite){
	float spriteWidth = sprite->getContentSize().width;
	float scaleRate = VISIBLE_WIDTH / spriteWidth;
	return scaleRate;
}

float GameUtils::getVisibleWidth(){
	auto visibleSize = Director::getInstance()->getVisibleSize();
	return visibleSize.width;
}

float GameUtils::getVisibleHeight(){
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//auto screenSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	//return screenSize.height;
	return visibleSize.height;
}


float GameUtils::getLevelScale(Sprite* sprite) {
	// 元素之间空10
	//float spaceSize = GameData::getInstance()->getlevelSpace();
	float scaleRate = (VISIBLE_WIDTH - g_EachLineCount *2*level_space)/(sprite->getContentSize().width * g_EachLineCount);

	return scaleRate;
}

//根据block 实际像素大小和屏幕大小，算出要缩放的比例
float GameUtils::getBlockScale(Sprite* sprite,float x_count) {
	return (VISIBLE_WIDTH - level_space * 2)/(sprite->getContentSize().width * x_count);
}

float GameUtils::getPageScale(Sprite* page,Sprite* sprite) {

	float pagePer = (page->getContentSize().width * 2)/(page->getContentSize().width*2 + sprite->getContentSize().width * 5);

	float scaleRate = (VISIBLE_WIDTH * 0.8 * pagePer)/(sprite->getContentSize().width * 2);

	return scaleRate;
}

float GameUtils::getSpaceSizeRate(int spCount){
	return VISIBLE_WIDTH * 0.1/((spCount)*2);
}





Animation* GameUtils::getAnimationByKeyAndFrameName(const std::string& aniKey, const std::string& frameName,
	const int& frameCount, float delay){
	auto animCache = AnimationCache::getInstance();
	auto resultAnimation = animCache->getAnimation(aniKey);
	if (resultAnimation == nullptr){
		auto frameCache = SpriteFrameCache::getInstance();
		Vector<SpriteFrame*> animFrames(frameCount);
		char str[50] = { 0 };
		for (int i = 0; i < frameCount; i++){
			sprintf(str, frameName.c_str(), i);
			auto frame = frameCache->getSpriteFrameByName(str);
			CCASSERT(frame != nullptr, "frame is null!");
			animFrames.pushBack(frame);
		}
		auto animation = Animation::createWithSpriteFrames(animFrames, delay);

		// Add an animation to the Cache
		AnimationCache::getInstance()->addAnimation(animation, aniKey);
		animFrames.clear();
		resultAnimation = animCache->getAnimation(aniKey);
		//log("no cache");
	}
	return resultAnimation;
}


Animation* GameUtils::getAnimationByKeyAndFileName(const std::string& aniKey, const std::string& fileName,


	const int& frameCount, float delay){
	auto animCache = AnimationCache::getInstance();
	auto resultAnimation = animCache->getAnimation(aniKey);
	if (resultAnimation == nullptr){
		auto cache = Director::getInstance()->getTextureCache();
		Vector<SpriteFrame*> animFrames(frameCount);
		char str[50] = { 0 };
		for (int i = 0; i < frameCount; i++){
			sprintf(str, fileName.c_str(), i);
			auto texture = cache->addImage(str);
			CCASSERT(texture != nullptr, "texture is null!");
			auto size = texture->getContentSize();
			auto rect = Rect(0, 0, size.width, size.height);
			auto frame = SpriteFrame::createWithTexture(texture, rect);
			animFrames.pushBack(frame);
		}
		auto animation = Animation::createWithSpriteFrames(animFrames, delay);

		// Add an animation to the Cache
		AnimationCache::getInstance()->addAnimation(animation, aniKey);
		animFrames.clear();
		resultAnimation = animCache->getAnimation(aniKey);
		//log("no cache");
	}
	return resultAnimation;
}

void GameUtils::startGameByLevel(int level){
	if (level != 0) {
		GameData::getInstance()->setChooseLevel(level);
	}
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, GameScene::create()));
}


