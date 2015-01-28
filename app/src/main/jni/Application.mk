NDK_TOOLCHAIN_VERSION=4.8

APP_PLATFORM := android-21

APP_CPPFLAGS += -fno-rtti -Wno-psabi -Wno-switch
STLPORT_FORCE_REBUILD := false