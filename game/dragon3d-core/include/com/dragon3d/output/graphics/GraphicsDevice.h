/*
* Copyright 2013 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**********************************************************************
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/09/28
 **********************************************************************/


#ifndef Display_Graphics_Output_Dragon3d_Com_H
#define Display_Graphics_Output_Dragon3d_Com_H

#include <dragon/config.h>

#include <dragon/lang/Object.h>
#include <com/dragon3d/output/OutputDevice.h>

BeginPackage4(com, dragon3d, output, graphics)

Import dragon::lang;
Import com::dragon3d::output;

#define STATUS_DISPLAY_WIDTH 0x333000
#define STATUS_DISPLAY_HEIGHT 0x333001

/**
 * game output display.
 * 
 */
class _DragonExport GraphicsDevice extends(Object) 
	implements1(OutputDevice) {
public:
	GraphicsDevice();
	virtual ~GraphicsDevice();

public: // implements OutputDevice
	/**
	 * init the output device
	 */
	virtual void init();	

	/**
	 * query the output device status by code.
	 * 
	 * @param code [description]
	 */
	virtual int queryStatus(int code);

	/**
	 *  get the ouput controller.
	 *  
	 * @return [description]
	 */
	virtual OutputController* getOutputController();

	/**
	 * get the native data.
	 * 
	 */
	virtual void* getNativeData();

	/**
	 * destroy the device.
	 */
	virtual void destroy();

protected:
	/**
	 * display scene output controller.
	 */
	OutputController* controller;

	/**
	 * native data.
	 */
	void* nativeData;

public:
	/**
	 * can show width
	 */
	int width;

	/**
	 * can show height
	 */
	int height;

};//GraphicsDevice

EndPackage4 //(com, dragon3d, output, graphics)

#endif //Display_Graphics_Output_Dragon3d_Com_H
