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


#ifndef OutputDevice_Output_Dragon3d_Com_H
#define OutputDevice_Output_Dragon3d_Com_H

#include <dragon/config.h>
#include <com/dragon3d/output/OutputController.h>

BeginPackage3(com, dragon3d, output)

/**
 * interface output device
 */
__interface _DragonExport OutputDevice {
public:
	virtual ~OutputDevice(){};

public:
	/**
	 * init the output device
	 */
	virtual void init() = 0;	

	/**
	 * query the output device status by code.
	 * 
	 * @param code [description]
	 */
	virtual int queryStatus(int code) = 0;

	/**
	 * destroy the output device
	 */
	virtual void destroy() = 0;	

	/**
	 *  get the ouput controller.
	 *  
	 * @return [description]
	 */
	virtual OutputController* getOutputController() = 0;

};//OutputDevice

EndPackage3 //(com, dragon3d, output)

#endif //OutputDevice_Output_Dragon3d_Com_H
