#include "CocosCamera.h"

CocosCamera* CocosCamera::cameraObj = nullptr;

void CocosCamera::nativeResponse(std::string imagePath) {
	cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {
		CocosCamera::getInstance()->cameraResponse(imagePath);
	});
}

void CocosCamera::cameraResponse(std::string imagePath) {
	log("CocosCamera::cameraResponse %s end", imagePath.c_str());
	if (imagePath.compare("") == 0) {
		responseFunct(true, "");
	}
	else {
		Sprite *oldTexture = Sprite::create(FileUtils::getInstance()->getWritablePath() + imagePath);
		if(oldTexture)
			Director::getInstance()->getTextureCache()->removeTexture(oldTexture->getTexture());
		responseFunct(false, FileUtils::getInstance()->getWritablePath() + imagePath);
	}
}
