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
 * Created:     2013/09/20
 **********************************************************************/


#ifndef ReadOnlyTimer_Util_Dragon3d_Com_H
#define ReadOnlyTimer_Util_Dragon3d_Com_H

#include <dragon/config.h>

BeginPackage3(com, dragon3d, util)

Import com::dragon3d::util;

/**
 * the base of Timer.
 * 
 */
interface _DragonExport ReadOnlyTimer {
public:
	virtual ~ReadOnlyTimer() {};

public:
 	/**
     * Get elapsed time in seconds since this timer was created or reset.
     * 
     * @see #getTime()
     * 
     * @return Time in seconds
     */
    virtual double getTimeInSeconds() = 0;

    /**
     * Get elapsed time since this timer was created or reset, in the resolution specified by the implementation
     * (usually in nanoseconds).
     * 
     * @see #getResolution()
     * @see #getTimeInSeconds()
     * 
     * @return Time in resolution specified by implementation
     */
    virtual long getTime() = 0;

    /**
     * Get the resolution used by this timer. Nanosecond resolution would return 10^9
     * 
     * @return Timer resolution
     */
    virtual long getResolution() = 0;

    /**
     * Get the current number of frames per second (fps).
     * 
     * @return Current frames per second (fps)
     */
    virtual double getFrameRate() = 0;

    /**
     * Get the time elapsed between the latest two frames, in seconds.
     * 
     * @return Time between frames, in seconds
     */
    virtual double getTimePerFrame() = 0;
	
};//ReadOnlyTimer

EndPackage3 //(com, dragon3d, util)

#endif //ReadOnlyTimer_Util_Dragon3d_Com_H
