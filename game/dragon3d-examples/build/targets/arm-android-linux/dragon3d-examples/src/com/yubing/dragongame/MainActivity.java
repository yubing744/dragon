package com.yubing.dragongame;

import android.app.Activity;
import android.content.res.AssetManager;
import android.os.Bundle;

public class MainActivity extends Activity  {

	static {
		System.loadLibrary("gnustl_shared");
		System.loadLibrary("unicode");
		System.loadLibrary("pcre32");
		System.loadLibrary("dragon");
		System.loadLibrary("dragon3d-core");
		System.loadLibrary("dragon3d-examples");
		System.loadLibrary("dg_main_jni");
	}

	//<<< JNI Interface 
	public static native void dragonInit(DGAndroidPlatfom platform, AssetManager assetManager);
	public static native void dragonDestroy();
	//>>> JNI Interface

	private DGAndroidPlatfom platform;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		platform = new DGAndroidPlatfom(this);
		dragonInit(platform, getAssets());
		platform.createWin();
	}

	@Override
	protected void onPause() {
		super.onPause();
		platform.onPause();
	}

	@Override
	protected void onResume() {
		super.onResume();
		platform.onResume();
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		dragonDestroy();
	}
}
