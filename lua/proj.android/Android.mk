LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_lua_static

LOCAL_MODULE_FILENAME := liblua

LOCAL_SRC_FILES := ../cocos2dx_support/CCLuaEngine.cpp \
		../cocos2dx_support/DorothyXml.cpp \
		../cocos2dx_support/DorothyModule.cpp \
		../cocos2dx_support/LuaCocos2d.cpp \
		../cocos2dx_support/LuaCode.cpp \
		../cocos2dx_support/tolua_extern.cpp \
		../cocos2dx_support/tolua_fix.c \
		../tolua/tolua_event.c \
		../tolua/tolua_is.c \
		../tolua/tolua_map.c \
		../tolua/tolua_push.c \
		../tolua/tolua_to.c \
		../lpeg/lpcap.c \
		../lpeg/lpcode.c \
		../lpeg/lpprint.c \
		../lpeg/lptree.c \
		../lpeg/lpvm.c

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../lib/include \
                           $(LOCAL_PATH)/../tolua \
                           $(LOCAL_PATH)/../cocos2dx_support

LOCAL_C_INCLUDES := $(LOCAL_PATH)/ \
                    $(LOCAL_PATH)/../lib/include \
                    $(LOCAL_PATH)/../tolua \
                    $(LOCAL_PATH)/../lpeg \
                    $(LOCAL_PATH)/../../cocos2dx \
                    $(LOCAL_PATH)/../../cocos2dx/include \
                    $(LOCAL_PATH)/../../cocos2dx/platform \
                    $(LOCAL_PATH)/../../cocos2dx/platform/android \
                    $(LOCAL_PATH)/../../cocos2dx/kazmath/include \
                    $(LOCAL_PATH)/../../cocos2dx/extensions \
                    $(LOCAL_PATH)/../../CocosDenshion/include \
                    $(LOCAL_PATH)/../../dorothy \
                    $(LOCAL_PATH)/../../external

LOCAL_WHOLE_STATIC_LIBRARIES := luajit_static

LOCAL_CFLAGS += -Wno-psabi
LOCAL_EXPORT_CFLAGS += -Wno-psabi

include $(BUILD_STATIC_LIBRARY)

$(call import-module,lua/lib)
