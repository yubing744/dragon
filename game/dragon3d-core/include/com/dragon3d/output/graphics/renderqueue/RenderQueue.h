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
 * Created:     2014/05/01
 **********************************************************************/


#ifndef RenderQueue_Renderqueue_Graphics_Output_Dragon3d_Com_H
#define RenderQueue_Renderqueue_Graphics_Output_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>

#include <com/dragon3d/output/graphics/Renderable.h>

BeginPackage5(com, dragon3d, output, graphics, renderqueue)

Import dragon::lang;
Import com::dragon3d::output::graphics;

class_ RenderQueue extends(Object) {
public:
    static const Type* TYPE;
    
public:
    RenderQueue();
    virtual ~RenderQueue();

public:
    /**
     * clear the queue.
     */
    virtual void clear();

    /**
     * add to renderable object to queue.
     * 
     * @param renderable [description]
     */
    virtual void add(Renderable* renderable);

    /**
     * add multiple renderable object.
     * 
     * @param renderables [description]
     */
    virtual void addAll(List<Renderable>* renderables);

    /**
     * get the iterator of the queue.
     * 
     */
    virtual Iterator<Renderable>* iterator();

    /**
     * sort the queue
     */
    virtual void sort();

protected:
    List<Renderable>* queue;
    
};//RenderQueue

EndPackage5 //(com, dragon3d, output, graphics, renderqueue)

#endif //RenderQueue_Renderqueue_Graphics_Output_Dragon3d_Com_H
