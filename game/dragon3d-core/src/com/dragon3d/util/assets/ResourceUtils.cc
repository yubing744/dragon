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
 * Created:     2014/04/18
 **********************************************************************/

#include <dragon/lang/gc/Reference.h>
#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/util/assets/ResourceUtils.h>

Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::util::assets;

const Type* ResourceUtils::TYPE = TypeOf<ResourceUtils>();
static Logger* logger = Logger::getLogger(ResourceUtils::TYPE, ERROR);

static String* ResourceUtils::readResourceToString(Resource* res, const String& charset) {
    Ref<InputStream> is = res->getInputStream();
    Ref<InputStreamReader> isr = new InputStreamReader(is, charset);

    Ref<StringBuffer> sb = new StringBuffer();

    wchar_u buf[512];

    int readCount = 0;

    while((readCount = irs->read(buf, 512)) > 0) {
        sb->append(buf, readCount);
    }

    return sb->toString();
}