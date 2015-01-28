#include <jni.h>

#include "IMyVibrator.h"

#define BIND_CLASS_NAME "com/test/vibratorbinder/NativeHandler"

static sp<IMyVibrator> gVibratorService = NULL;
static sp<IBinder> gServiceBinder = NULL;

void initNative(JNIEnv *env, jobject thiz){
    gServiceBinder = defaultServiceManager() -> getService(String16("vibrator"));
    if(gServiceBinder == NULL){
        ALOGE("Error getting vibrator service binder");
    }else{
        gVibratorService = interface_cast<IMyVibrator>(gServiceBinder);
    }
}

jboolean hasVibratorWrapper(JNIEnv *env, jobject thiz) {
    if(gVibratorService != NULL){
        return (gVibratorService -> hasVibrator())? JNI_TRUE : JNI_FALSE;
    }

    return JNI_FALSE;
}

void vibrateWrapper(JNIEnv *env, jobject thiz, jint uid, jstring packageName, jlong millis) {
    if(gVibratorService != NULL){
        const char *pkgName = env -> GetStringUTFChars(packageName, JNI_FALSE);
        String16 strPkgName = String16(pkgName);
        gVibratorService -> vibrate((int32_t)uid, strPkgName, (int64_t)millis, (int32_t)0, gServiceBinder);

        env -> ReleaseStringUTFChars(packageName, pkgName);
    }
}

//TODO: Add vibratePattern and cancelVibrate binding

static JNINativeMethod jniMethods[] = {
    {"initNative", "()V", (void*)initNative},
    {"hasVibratorNative", "()Z", (void*)hasVibratorWrapper},
    {"vibrateNative", "(ILjava/lang/String;J)V", (void*)vibrateWrapper}
};

JNIEXPORT
jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved){
    JNIEnv *env;
    if(vm -> GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK){ //Must use reinterpret_cast instead of (void**)&env in C
        ALOGE("Error getting jni environment");
        return JNI_ERR;
    }

    //Find bind class
    jclass classBind = (env -> FindClass(BIND_CLASS_NAME));
    if(classBind == NULL){
        ALOGE("Error getting class: "BIND_CLASS_NAME);
        return JNI_ERR;
    }

    if( env -> RegisterNatives( classBind, jniMethods, (sizeof(jniMethods) / sizeof(JNINativeMethod)) ) < 0 ){
        ALOGE("Error registering native methods");
        env -> DeleteLocalRef(classBind);
        return JNI_ERR;
    }
    env -> DeleteLocalRef(classBind);

    return JNI_VERSION_1_6;
}