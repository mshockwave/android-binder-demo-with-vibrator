package com.test.vibratorbinder;

public class NativeHandler {

    private native void initNative();
    public native boolean hasVibratorNative();
    private native void vibrateNative(int uid, String pkgName, long millis);

    private int mUid;
    private String mPkgName;

    public NativeHandler(int uid, String pkgName){
        mUid = uid;
        mPkgName = pkgName;
        initNative();
    }

    public void vibrate(long millis){
        vibrateNative(mUid, mPkgName, millis);
    }

    static {
        System.loadLibrary("myVibrator");
    }
}
