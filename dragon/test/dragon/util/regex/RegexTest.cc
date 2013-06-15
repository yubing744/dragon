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

#include <gtest/gtest.h>
#include <dragon/config.h>
#include <dragon/lang/String.h>

#include <dragon/util/regex/Pattern.h>
#include <dragon/util/regex/Matcher.h>


Import dragon::lang;
Import dragon::util::regex;

TEST(Dragon_Util_Regex_RegexTest, BasicTest) {
    String* regex = new String("a*b");
    String* subject = new String("aaaaab");

    Pattern* p = Pattern::compile(regex);
    Matcher* m = p->matcher(subject);
    dg_boolean b = m->matches();

    EXPECT_EQ(dg_true, b);
}

TEST(Dragon_Util_Regex_RegexTest, UnicodeStrMatch) {
    String* regex = new String("[^\\x{4e00}-\\x{9fa5}]$");
    String* subject = new String(L"好");

    Pattern* p = Pattern::compile(regex);
    Matcher* m = p->matcher(subject);
    dg_boolean b = m->matches();

    EXPECT_EQ(dg_true, b);
}