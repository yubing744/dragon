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
 * Description: base config for all other classes
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/07/08
 **********************************************************************/

#include <com/dragon3d/config.h>


#if !defined(DG_OBJECT)
#define DG_OBJECT

BeginPackage3(com, dragon3d, framework)

class _DragonExport Object
{
public:
	Object(void);
	virtual ~Object(void);
};

EndPackage3 //(com, dragon3d, framework)

#endif
