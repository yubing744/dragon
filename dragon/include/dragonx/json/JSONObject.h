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
 * Created:     2013/12/15
 **********************************************************************/


#ifndef JSONObject_Json_Dragonx_H
#define JSONObject_Json_Dragonx_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/lang/String.h>
#include <dragon/util/HashMap.h>

BeginPackage2(dragonx, json)

Import dragon::util;
Import dragon::lang;

class _DragonExport JSONObject 
    :public HashMap<String, Object> {
public:
    static JSONObject* parse(const String& json);

public:
    JSONObject();
    JSONObject(const String& json);
    virtual ~JSONObject();

public:
    String* getString(const String& key);
    int getInt(const String& key);
    
    float getFloat(const String& key);
    double getDouble(const String& key);

    bool getBoolean(const String& key);
    JSONObject* getJSONObject(const String& key);
    Object* getObject(const String& key);

};//JSONObject

EndPackage2 //(dragonx, json)

#endif //JSONObject_Json_Dragonx_H
