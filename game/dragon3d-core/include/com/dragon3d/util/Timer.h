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


#ifndef Timer_Util_Dragon3d_Com_H
#define Timer_Util_Dragon3d_Com_H

#include <dragon/config.h>
#include <com/dragon3d/util/ReadOnlyTimer.h>

BeginPackage3(com, dragon3d, util)

Import com::dragon3d::util;

/**
 * game timer.
 * 
 */
class _DragonExport Timer 
	implements(ReadOnlyTimer) {
public:
	Timer();
	virtual ~Timer();

public: // Implements ReadOnlyTimer
    virtual double getTimeInSeconds();
    virtual long getTime();
    virtual long getResolution();
    virtual double getFrameRate();
    virtual double getTimePerFrame();	

public:
	/**
	 * Update should be called once per frame to correctly update "time per frame" and "frame rate (fps)"
	 */
	virtual void update();

	/**
	 * pause the time
	 */
	virtual void pause();

	/**
	 * resume the time;
	 */
	virtual void resume();

	/**
	 * Reset this timer, so that {@link #getTime()} and {@link #getTimeInSeconds()} reflects the time spend from this
     * call.
	 */
	virtual void reset();

protected:
	dg_long startTime;
    dg_long previousTime;

    double fps;
    double tps;

    bool paused;

};//Timer

EndPackage3 //(com, dragon3d, util)

#endif //Timer_Util_Dragon3d_Com_H
