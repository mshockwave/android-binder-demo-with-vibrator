NDK_TOOLCHAIN_VERSION=4.8

#Since my "android-headers" were pull from 5.0.0 which uses stdatomic.h and only exists in platforms higher than android-21
#So we need to force it to build library with android-21 toolchains
APP_PLATFORM := android-21

APP_CPPFLAGS += -fno-rtti -Wno-psabi -Wno-switch
STLPORT_FORCE_REBUILD := false