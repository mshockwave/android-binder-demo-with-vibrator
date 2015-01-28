#include "IMyVibrator.h"
using namespace android;

//Client proxy interface
class BpMyVibrator : public BpInterface<IMyVibrator> {

public:
    BpMyVibrator(const sp<IBinder>& impl) : BpInterface<IMyVibrator>(impl) {
        ALOGD("BpMyVibrator constructor");
    }

    virtual bool hasVibrator(void) {
        ALOGD("BpMyVibrator::hasVibrator invoked");
        Parcel _data, _reply;
        _data.writeInterfaceToken(IMyVibrator::getInterfaceDescriptor());
        remote() -> transact(TRANSACTION_hasVibrator, _data, &_reply);
        /*
        * Need to read the exception before fetching return data!!
        * Since methods in AIDL file will always throw RemoteException
        */
        ALOGD("%s exception code: %d", __func__, _reply.readExceptionCode());
        int retInt32 = _reply.readInt32();
        //ALOGD("Return in int: %d", retInt32);

        return (bool)(0 != retInt32);
    }

    virtual void vibrate(int32_t uid, String16& opPkg, int64_t milliseconds, int32_t usageHint, sp<IBinder>& token) {
        ALOGD("BpMyVibrator::vibrate invoked");
        Parcel _data, _reply;
        _data.writeInterfaceToken(IMyVibrator::getInterfaceDescriptor());
        _data.writeInt32(uid);
        _data.writeString16(opPkg);
        _data.writeInt64(milliseconds);
        _data.writeInt32(usageHint);
        _data.writeStrongBinder(token);

        remote() -> transact(TRANSACTION_vibrate, _data, &_reply);
        //ALOGD("%s exception code: %d", __func__, _reply.readExceptionCode());
    }

    virtual void vibratePattern(int32_t uid, String16& opPkg, int64_t pattern[], int32_t repeat, int32_t usageHint, sp<IBinder>& token) {
        ALOGD("BpMyVibrator::vibratePattern invoked");
        Parcel _data, _reply;
        _data.writeInterfaceToken(IMyVibrator::getInterfaceDescriptor());
        _data.writeInt32(uid);
        _data.writeString16(opPkg);
        size_t len = (size_t)(sizeof(pattern) / sizeof(pattern[0]));
        _data.write((const void*)pattern, len);
        _data.writeInt32(repeat);
        _data.writeInt32(usageHint);
        _data.writeStrongBinder(token);

        remote() -> transact(TRANSACTION_vibratePattern, _data, &_reply);
        //ALOGD("%s exception code: %d", __func__, _reply.readExceptionCode());
    }

    virtual void cancelVibrate(sp<IBinder>& token) {
        ALOGD("BpMyVibrator::cancelVibrate invoked");
        Parcel _data, _reply;
        _data.writeInterfaceToken(IMyVibrator::getInterfaceDescriptor());
        _data.writeStrongBinder(token);

        remote() -> transact(TRANSACTION_cancelVibrate, _data, &_reply);
        //ALOGD("%s exception code: %d", __func__, _reply.readExceptionCode());
    }
};

IMPLEMENT_META_INTERFACE(MyVibrator, "android.os.IVibratorService");