#include "CocosCamera.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import <Foundation/Foundation.h>
// #include "../../proj.ios_mac/ios/AppController.h"
#include "AppController.h"

void CocosCamera::openCamera(std::string imageName, int width, int height, std::function<void(bool isError, std::string imagePath)> callBackFunct) {
	responseFunct = callBackFunct;

    AppController *appDelegate = (AppController *)[[UIApplication sharedApplication] delegate];
    [appDelegate openCamera:[NSString stringWithUTF8String:imageName.c_str()] :width :height];
}

void CocosCamera::saveImage(std::string imageName) {
    AppController *appDelegate = (AppController *)[[UIApplication sharedApplication] delegate];
    [appDelegate saveImage:[NSString stringWithUTF8String:imageName.c_str()]];
}

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)