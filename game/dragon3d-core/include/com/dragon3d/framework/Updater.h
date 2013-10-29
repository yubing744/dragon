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
 * Created:     2013/09/17
 **********************************************************************/


#ifndef Updater_Framework_Dragon3d_Com_H
#define Updater_Framework_Dragon3d_Com_H

#include <dragon/config.h>
#include <com/dragon3d/util/ReadOnlyTimer.h>
#include <com/dragon3d/framework/Scene.h>

BeginPackage3(com, dragon3d, framework)

Import com::dragon3d::util;

/**
 * The purpose of this class is to own the update phase and separate update logic from the view.
 */
__interface _DragonExport Updater {
public:
	virtual ~Updater(){};

public:
	/**
	 * init the updater
	 */
	virtual void init() = 0;

	/**
	 * update the scene status
	 * 
	 * @param scene 
	 *        	game scene
	 * @param timer
	 *        	the timer for game
	 */
	virtual void update(Scene* scene, ReadOnlyTimer* timer) = 0;

};//Updater

EndPackage3 //(com, dragon3d, framework)

#endif //Updater_Framework_Dragon3d_Com_H
