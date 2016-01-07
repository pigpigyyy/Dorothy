APP_STL := gnustl_static

APP_CPPFLAGS := -frtti
APP_CPPFLAGS += -fexceptions
APP_CPPFLAGS += -std=c++11
PM5_CONFIG := debug
include $(call my-dir)/../../../build/androidmk/DorothyPremake_Application.mk