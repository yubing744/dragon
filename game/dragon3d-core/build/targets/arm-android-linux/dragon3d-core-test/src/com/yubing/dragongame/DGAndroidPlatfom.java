package com.yubing.dragongame;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.opengl.GLSurfaceView;
import android.util.Log;

public class DGAndroidPlatfom implements GLSurfaceView.Renderer {

	//<<< JNI Interface 
	public static native void start();
	public static native void resize(int width, int height);
	public static native void draw(long deltaTime);
	public static native void pause();
	public static native void resume();
	//>>> JNI Interface
	
	
	private GLSurfaceView surfaceView;
	private Activity mainActivity;
	private long lastTime;
	
	public DGAndroidPlatfom(MainActivity mainActivity) {
		this.mainActivity = mainActivity;
	}

	public void createWin(){
		surfaceView = new GLSurfaceView(mainActivity);
		
        if (detectOpenGLES20()){
            // Tell the surface view we want to create an OpenGL ES 2.0-compatible
            // context, and set an OpenGL ES 2.0-compatible renderer.
        	surfaceView.setEGLContextClientVersion(2);
        	surfaceView.setRenderer(this);
        } else {
        	Log.e("DragonGame", "OpenGL ES 2.0 not supported on device.  Exiting...");
        	mainActivity.finish();
        }
        
        mainActivity.setContentView(surfaceView);
	}
	
	private boolean detectOpenGLES20() {
        ActivityManager am = (ActivityManager)mainActivity.getSystemService(Context.ACTIVITY_SERVICE);
        ConfigurationInfo info = am.getDeviceConfigurationInfo();
        return (info.reqGlEsVersion >= 0x20000);
    }
	
	@Override
	public void onDrawFrame(GL10 gl) {
		long curTime = System.currentTimeMillis();
		long deltaTime = curTime - lastTime;
		lastTime = curTime;
		
		draw(deltaTime);
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		resize(width, height);
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		lastTime = System.currentTimeMillis();
		
		start();
	}
	
	public void onPause() {
		pause();
	}

	public void onResume() {
		resume();
	}
	
}
