#include "CocosCamera.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
#include "cocos/platform/android/jni/JniHelper.h"

#define  APP_ACTIVITY_CLASS_NAME "org/cocos2dx/cpp/AppActivity"

extern "C" {
	JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_callCameraResponse(JNIEnv*  env, jobject thiz, jstring imagePath) {
		if (JniHelper::getJavaVM()->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK || !env) {
			return;
		}

		const char* str = env->GetStringUTFChars(imagePath, NULL);
		std::string ipath(str);
        CocosCamera::getInstance()->nativeResponse(ipath);
		env->ReleaseStringUTFChars(imagePath, str);
	}
}

void CocosCamera::openCamera(std::string imageName, int width, int height, std::function<void(bool isError, std::string imagePath)> callBackFunct) {
	responseFunct = callBackFunct;

	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, APP_ACTIVITY_CLASS_NAME, "openCamera", "(Ljava/lang/String;II)V")) {
		jstring stringArg1 = t.env->NewStringUTF(imageName.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, width, height);
		t.env->DeleteLocalRef(t.classID);
	}
}

void CocosCamera::saveImage(std::string imageName) {
    
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, APP_ACTIVITY_CLASS_NAME, "saveImage", "(Ljava/lang/String;II)V")) {
        jstring stringArg1 = t.env->NewStringUTF(imageName.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1 , 0 , 0);
        t.env->DeleteLocalRef(t.classID);
    }
}

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
