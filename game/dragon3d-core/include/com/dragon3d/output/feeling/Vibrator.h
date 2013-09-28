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


#ifndef Vibrator_Feeling_Output_Dragon3d_Com_H
#define Vibrator_Feeling_Output_Dragon3d_Com_H

#include <dragon/config.h>

BeginPackage4(com, dragon3d, output, feeling)

Import com::dragon3d::output::feeling;

class _DragonExport Vibrator {
public:
	Vibrator();
	virtual ~Vibrator();

public:
	
protected:
	
};//Vibrator

EndPackage4 //(com, dragon3d, output, feeling)

#endif //Vibrator_Feeling_Output_Dragon3d_Com_H
