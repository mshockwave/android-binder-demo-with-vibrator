LOCAL_PATH :=   $(call my-dir)

include $(CLEAR_VARS)

AOSP_INCLUDE :=    $(LOCAL_PATH)/include
AOSP_LIB := $(LOCAL_PATH)/lib

LOCAL_SRC_FILES +=  MyVibratorProxy.cpp
LOCAL_SRC_FILES +=  jniWrapper.cpp

LOCAL_MODULE := myVibrator
#LOCAL_CFLAGS += -DHAVE_PTHREADS -DHAVE_SYS_UIO_H
LOCAL_C_INCLUDES += $(AOSP_INCLUDE)
LOCAL_LDLIBS += -L$(AOSP_LIB)
LOCAL_LDLIBS += -llog -lbinder -lutils -lcutils

include $(BUILD_SHARED_LIBRARY)