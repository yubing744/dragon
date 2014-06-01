package com.dragon3d.util.assets;

import android.content.Context;
import android.content.pm.ApplicationInfo;

/**
 * the andriod native Resource.
 * 
 * @author yubing
 *
 */
public class Resource {

	/**
	 * init the resource
	 * 
	 * @param pContext
	 */
	public static void init(final Context pContext) {
		final ApplicationInfo applicationInfo = pContext.getApplicationInfo();
		Resource.nativeSetApkPath(applicationInfo.sourceDir);
	}
	
	// native interface
	private static native void nativeSetApkPath(final String pApkPath);
}
