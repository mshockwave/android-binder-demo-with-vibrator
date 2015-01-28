#include <binder/IInterface.h>
#include <binder/IBinder.h>
#include <binder/Binder.h>
#include <binder/IServiceManager.h>
#include <binder/Parcel.h>

#undef LOG_TAG
#define LOG_TAG "MyVibrator"

using namespace android;

class IMyVibrator : public IInterface {

public:
    DECLARE_META_INTERFACE(MyVibrator);

    virtual bool hasVibrator(void) = 0;
    virtual void vibrate(int32_t uid, String16& opPkg, int64_t milliseconds, int32_t usageHint, sp<IBinder>& token) = 0;
    virtual void vibratePattern(int32_t uid, String16& opPkg, int64_t pattern[], int32_t repeat, int32_t usageHint, sp<IBinder>& token) = 0;
    virtual void cancelVibrate(sp<IBinder>& token) = 0;

};

#define TRANSACTION_hasVibrator (IBinder::FIRST_CALL_TRANSACTION + 0)
#define TRANSACTION_vibrate (IBinder::FIRST_CALL_TRANSACTION + 1)
#define TRANSACTION_vibratePattern  (IBinder::FIRST_CALL_TRANSACTION + 2)
#define TRANSACTION_cancelVibrate  (IBinder::FIRST_CALL_TRANSACTION + 3)