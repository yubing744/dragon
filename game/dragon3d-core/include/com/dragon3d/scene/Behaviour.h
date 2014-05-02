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


#ifndef Behaviour_Scene_Dragon3d_Com_H
#define Behaviour_Scene_Dragon3d_Com_H

#include <dragon/config.h>

#include <com/dragon3d/scene/Component.h>

BeginPackage3(com, dragon3d, scene)

Import com::dragon3d::scene;

class _DragonExport Behaviour 
    extends(Component) {
public:
    static const Type* TYPE;

public:
	Behaviour();
	virtual ~Behaviour();

public:
    /**
     * the component is type of type.
     * 
     * @param  type [description]
     * @return      [description]
     */
    virtual bool isTypeOf(const Type* type);

public:
    /**
     * Enabled Behaviours are Updated, disabled Behaviours are not.
     */
	bool enabled;

};//Behaviour

EndPackage3 //(com, dragon3d, scene)

#endif //Behaviour_Scene_Dragon3d_Com_H

/*
#pragma once

#include "dg_component.h"

#if !defined(DG_BEHAVIOR)
#define DG_BEHAVIOR

class DGBehaviour :
    public DGComponent
{
public:
    DGBehaviour(void);
    virtual ~DGBehaviour(void);

public:
	virtual void init(DGGameObject* gameObject, DGContext* ctx);
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
	virtual void destroy();

public:
    virtual void start();

public:
    DGboolean enabled;
};

#endif

 */