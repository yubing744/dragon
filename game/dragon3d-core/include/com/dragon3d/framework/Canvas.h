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


#ifndef Canvas_Framework_Dragon3d_Com_H
#define Canvas_Framework_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/util/concurrent/CountDownLatch.h>

BeginPackage3(com, dragon3d, framework)

Import com::dragon3d::framework;
Import dragon::util::concurrent;

/**
 * This interface defines the View, and should maybe be called the ViewUpdater. It owns the rendering phase, and
 * controls all interactions with the Renderer.
 */
interface _DragonExport Canvas {
public:
	virtual ~Canvas();

public:
    /**
     * Do work to initialize this canvas, generally setting up the associated CanvasRenderer, etc.
     */
    virtual void init();

    /**
     * Ask the canvas to render itself. Note that this may occur in another thread and therefore a latch is given so the
     * caller may know when the draw has completed.
     * 
     * @param latch
     *            a counter that should be decremented once drawing has completed.
     */
    virtual void draw(CountDownLatch* latch);

    /**
     * @return the CanvasRenderer associated with this Canvas.
     */
    //virtual CanvasRenderer* getCanvasRenderer();
	
};//Canvas

EndPackage3 //(com, dragon3d, framework)

#endif //Canvas_Framework_Dragon3d_Com_H
