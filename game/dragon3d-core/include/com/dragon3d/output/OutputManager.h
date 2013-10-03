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


#ifndef OutputManager_Output_Dragon3d_Com_H
#define OutputManager_Output_Dragon3d_Com_H

#include <dragon/config.h>

#include <dragon/lang/Object.h>
#include <dragon/lang/String.h>
#include <dragon/util/List.h>

#include <com/dragon3d/framework/Output.h>
#include <com/dragon3d/output/OutputDevice.h>

BeginPackage3(com, dragon3d, output)

Import dragon::util;

Import com::dragon3d::framework;
Import com::dragon3d::output;

/**
 * ouput manager
 */
class _DragonExport OutputManager extends(Object) 
	implements1(Output) {
public:
	OutputManager();
	virtual ~OutputManager();

public:// implements Output

	/**
	 * init the output
	 */
	virtual void init();

	/**
	 * output the scene
	 */
	virtual void output(Scene* scene, CountDownLatch* latch);

public:
	/**
	 * register a ouput device.
	 * 
	 * @param outputDevice [description]
	 */
	virtual void registerDevice(OutputDevice* outputDevice);	

protected:
	/**
	 * the all game output device.
	 */
	List<OutputDevice>* outputDevices;

};//OutputManager

EndPackage3 //(com, dragon3d, output)

#endif //OutputManager_Output_Dragon3d_Com_H
