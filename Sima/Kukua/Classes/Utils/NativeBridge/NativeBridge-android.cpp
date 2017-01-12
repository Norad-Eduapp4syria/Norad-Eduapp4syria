#include "NativeBridge.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
#include "cocos/platform/android/jni/JniHelper.h"

#define  APP_ACTIVITY_CLASS_NAME "org/cocos2dx/cpp/AppActivity"

void NativeBridge::createFolder(std::string folderPath) {
    
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, APP_ACTIVITY_CLASS_NAME, "createFolder", "(Ljava/lang/String;II)V")) {
        jstring stringArg1 = t.env->NewStringUTF(folderPath.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1 , 0 , 0);
        t.env->DeleteLocalRef(t.classID);
    }
}

void NativeBridge::createNecessaryFolders(std::string folderPath) {
    
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, APP_ACTIVITY_CLASS_NAME, "createNecessaryFolders", "(Ljava/lang/String;II)V")) {
        jstring stringArg1 = t.env->NewStringUTF(folderPath.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1 , 0 , 0);
        t.env->DeleteLocalRef(t.classID);
    }
}

void NativeBridge::unZipArchiveToFolder(std::string archivePath, std::string destFolderPath)
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, APP_ACTIVITY_CLASS_NAME, "unZipArchiveToFolder", "(Ljava/lang/String;Ljava/lang/String;)V"))
    {
        jstring stringArg1 = t.env->NewStringUTF(archivePath.c_str());
        jstring stringArg2 = t.env->NewStringUTF(destFolderPath.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2);
        t.env->DeleteLocalRef(t.classID);
    }
}

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
