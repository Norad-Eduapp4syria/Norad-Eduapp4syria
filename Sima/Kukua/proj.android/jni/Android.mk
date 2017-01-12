LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)





LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp


# LOCAL_SRC_FILES := hellocpp/main.cpp
# LOCAL_SRC_FILES += ../../Classes/AppDelegate.cpp
# LOCAL_SRC_FILES += ../../Classes/PenaltyKickGame/PenaltyKickGame.cpp

# LOCAL_SRC_FILES := hellocpp/main.cpp \
#                   ../../Classes/AppDelegate.cpp \
#                   ../../Classes/PenaltyKickGame/PenaltyKickGame.cpp

# LOCAL_SRC_FILES := hellocpp/main.cpp \
#                   ../../Classes/AppDelegate.cpp \
#                   ../../Classes/PenaltyKickGame/PenaltyKickGame.cpp \
#                   ../../Classes/Engine1/TurtlesGame.cpp \
#                   ../../Classes/HomeContainer/Home.cpp \
#                   ../../Classes/PreGame/PreGame1.cpp \
#                   ../../Classes/HomeContainer/PreHome.cpp


LOCAL_SRC_FILES := hellocpp/main.cpp
FILE_LIST := $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/**/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/**/**/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/**/**/**/*.cpp)
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)
# LOCAL_SRC_FILES += ../../Classes/Utils/Data/sqlite3.c;

FILE_LIST2 := $(wildcard $(LOCAL_PATH)/../../Classes/*.c)
FILE_LIST2 += $(wildcard $(LOCAL_PATH)/../../Classes/**/*.c)
FILE_LIST2 += $(wildcard $(LOCAL_PATH)/../../Classes/**/**/*.c)
FILE_LIST2 += $(wildcard $(LOCAL_PATH)/../../Classes/**/**/**/*.c)
LOCAL_SRC_FILES += $(FILE_LIST2:$(LOCAL_PATH)/%=%)


LOCAL_SRC_FILES := $(filter-out ../../Classes/RecorderScene/AQ_MainEngine.cpp, $(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out ../../Classes/RecorderScene/AQFoundation/AQPlayer.cpp, $(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out ../../Classes/RecorderScene/AQFoundation/AQRecorder.cpp, $(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out ../../Classes/RecorderScene/AQFoundation/AUOutputBL.cpp, $(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out ../../Classes/RecorderScene/AQFoundation/CAAudioBufferList.cpp, $(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out ../../Classes/RecorderScene/AQFoundation/CAComponentDescription.cpp, $(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out ../../Classes/RecorderScene/AQFoundation/CAStreamBasicDescription.cpp, $(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out ../../Classes/RecorderScene/AQFoundation/CAXException.cpp, $(LOCAL_SRC_FILES))


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)
 
 
$(call import-module,extensions)

# $(call import-module,./prebuilt-mk)
$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
