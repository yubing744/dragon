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
 * Created:     2014/02/11
 **********************************************************************/


#ifndef AudioOutputController_Audio_Output_Dragon3d_Com_H
#define AudioOutputController_Audio_Output_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <com/dragon3d/output/OutputController.h>

BeginPackage4(com, dragon3d, output, audio)

Import dragon::lang;

class_ AudioOutputController extends(Object) 
    implements1(OutputController) {
public:
    static const Type* TYPE;
    
public:
    AudioOutputController();
    virtual ~AudioOutputController();

public: // implements OutputController
    /**
     * init the output controller
     */
    virtual void init();

    /**
     * control the scene ouput.
     * 
     * @param scene [description]
     */
    virtual void output(Scene* scene);

    /**
     * destroy the output controller
     */
    virtual void destroy(); 
    
protected:
    AudioRenderer* render;
    
};//AudioOutputController

EndPackage4 //(com, dragon3d, output, audio)

#endif //AudioOutputController_Audio_Output_Dragon3d_Com_H
