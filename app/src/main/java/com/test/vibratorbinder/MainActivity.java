package com.test.vibratorbinder;

import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.View;


public class MainActivity extends ActionBarActivity {
    private NativeHandler mNative;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mNative = new NativeHandler(android.os.Process.myUid(), this.getPackageName());

        Log.i("MainActivity", "Has vibrator: " + mNative.hasVibratorNative());
    }

    public void vibrateNativeOnClick(View v){
        mNative.vibrate(200);
    }
}
