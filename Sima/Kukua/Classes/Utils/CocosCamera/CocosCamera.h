#ifndef __COCOS_CAMERA_H__
#define __COCOS_CAMERA_H__

#include "cocos2d.h"
USING_NS_CC;

class CocosCamera
{
public:
	CocosCamera() {};
	~CocosCamera() {};
	static CocosCamera* getInstance() {
        CCLOG("CocosCamera getInstance");
		if (!cameraObj) {
			cameraObj = new CocosCamera();
		}
		return cameraObj;
	}

	// imageName, imageWidth, imageHeight, responseMethod
	void openCamera(std::string imageName, int width, int height, std::function<void(bool isError, std::string imagePath)>);
    void nativeResponse(std::string imagePath);
	void cameraResponse(std::string imagePath);
    void saveImage(std::string imagePath);

private:
	static CocosCamera* cameraObj;
	std::function<void(bool isError, std::string imagePath)> responseFunct;
};

#endif // __COCOS_CAMERA_H__
