LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
                   $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/GamePlayScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/Hero.cpp \
				   $(LOCAL_PATH)/../../../Classes/Home.cpp \
				   $(LOCAL_PATH)/../../../Classes/Human.cpp \
				   $(LOCAL_PATH)/../../../Classes/Item.cpp \
				   $(LOCAL_PATH)/../../../Classes/GameSetting.cpp \
				   $(LOCAL_PATH)/../../../Classes/SettingScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/LoadingScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/LogoScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/MenuScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/MainMenuScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/MyObject.cpp \
				   $(LOCAL_PATH)/../../../Classes/Person.cpp \
				   $(LOCAL_PATH)/../../../Classes/Popup.cpp \
				   $(LOCAL_PATH)/../../../Classes/PopupHero.cpp \
				   $(LOCAL_PATH)/../../../Classes/ResourceManager.cpp \
				   $(LOCAL_PATH)/../../../Classes/ResourceNature.cpp \
				   $(LOCAL_PATH)/../../../Classes/ScoutTown.cpp \
				   $(LOCAL_PATH)/../../../Classes/SneakyButton.cpp \
				   $(LOCAL_PATH)/../../../Classes/SneakyButtonSkinnedBase.cpp \
				   $(LOCAL_PATH)/../../../Classes/SneakyJoystick.cpp \
				   $(LOCAL_PATH)/../../../Classes/SneakyJoystickSkinnedBase.cpp \
				   $(LOCAL_PATH)/../../../Classes/TownHall.cpp \
				   $(LOCAL_PATH)/../../../Classes/VisibleRect.cpp \
				   $(LOCAL_PATH)/../../../Classes/Dragon.cpp \
				   $(LOCAL_PATH)/../../../Classes/Knight.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d)
$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
