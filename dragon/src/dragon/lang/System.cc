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
 * Created:     2013/03/31
 **********************************************************************/

#include <stdlib.h>

#include <dragon/lang/System.h>
#include <dragon/lang/String.h>
#include <dragon/lang/Arrays.h>
#include <dragon/lang/internal/platform.h>
 
Import dragon::lang;
Import dragon::lang::internal;

void System::loadLibrary(const char* libname) {

}

dg_long System::currentTimeMillis() {
	dg_long nanoTime = GetSystemTime();
	return nanoTime / 1000;
}

dg_long System::nanoTime() {
	return GetSystemTime();
}

void System::exit(int code) {
    exit(code);
}

// ---------------------------------------
// system propertys
// 
typedef map<string, String*> PropMap;
typedef PropMap::iterator Iterator;

static bool isSetupClearSysPropMap = false;
static PropMap sysPropMap;

static void ClearSysPropMap() {
    for(Iterator it = sysPropMap.begin();sysPropMap.size()>0;it=sysPropMap.begin()) { 
        String* propVal = it->second;
        SafeDelete(propVal);

        sysPropMap.erase(it);
    }

    sysPropMap.clear();
}

const String* System::getProperty(const char* name) {
    if (!isSetupClearSysPropMap) {
        isSetupClearSysPropMap = true;

        atexit(ClearSysPropMap);
    }

    Iterator it = sysPropMap.find(name);

    if (it != sysPropMap.end()) {
        return it->second;
    } else {
        String* val = new String(getenv(name));
        sysPropMap[name] = val;
        return val;
    }
}


void System::arraycopy(const byte* src, int srcPos,
                    const byte* dest, int destPos, int length) {
    Arrays<byte>::copyOf(src, srcPos, const_cast<byte*>(dest), destPos, length);
}


void System::arraycopy(const Array<byte> src, int srcPos,
                                        const Array<byte> dest, int destPos,
                                        int length) {
    Arrays<byte>::copyOf(src.raw(), srcPos, const_cast<byte*>(dest.raw()), destPos, length);
}
