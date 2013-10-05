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


#ifndef Color_Model_Scene_Dragon3d_Com_H
#define Color_Model_Scene_Dragon3d_Com_H

#include <dragon/config.h>

BeginPackage4(com, dragon3d, util, math)

Import com::dragon3d::util::math;


class _DragonExport Color32 {
public:
	Color32();
	virtual ~Color32();

public:
    dg_byte a; //Alpha component of the color.
    dg_byte b; //Blue component of the color.
    dg_byte g; //Green component of the color.
    dg_byte r; //Red component of the color.
	
};//Color32

EndPackage4 //(com, dragon3d, util, math)

#endif //Color_Model_Scene_Dragon3d_Com_H
