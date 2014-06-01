package com.dragon3d.util.assets;

import android.content.Context;
import android.content.res.AssetManager;

/**
 * native assets manager
 * 
 * @author yubing
 *
 */
public class AssetsManager {

	/**
	 * init the resource
	 * 
	 * @param pContext
	 */
	public static void init(final Context pContext) {
		AssetsManager.nativeSetAssetManager(pContext.getAssets());
	}
	
	// native interface
	private static native void nativeSetAssetManager(final AssetManager javaAssetManager);
}
