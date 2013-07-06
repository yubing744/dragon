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

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <gtest/gtest.h>

#include <dragon.h>
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

    SafeDelete(m);
    SafeDelete(p);

    SafeDelete(regex);
    SafeDelete(subject);
}

TEST(Dragon_Util_Regex_RegexTest, UnicodeStrMatch) {
    String* regex = new String("[\\x{4e00}-\\x{9fa5}]");
    String* subject = new String(L"好");

    Pattern* p = Pattern::compile(regex);
    Matcher* m = p->matcher(subject);
    dg_boolean b = m->matches();

    EXPECT_EQ(dg_true, b);

    SafeDelete(m);
    SafeDelete(p);

    SafeDelete(regex);
    SafeDelete(subject);
}

TEST(Dragon_Util_Regex_RegexTest, MatchSimpleNum) {
    String* regex = new String("\\d{3}");
    String* subject = new String("222");

    Pattern* p = Pattern::compile(regex);
    Matcher* m = p->matcher(subject);
    dg_boolean b = m->matches();

    EXPECT_EQ(dg_true, b);

    SafeDelete(m);
    SafeDelete(p);

    SafeDelete(regex);
    SafeDelete(subject);
}

TEST(Dragon_Util_Regex_RegexTest, MatchPhoneNum) {
    String* regex = new String("\\(\\d{3}\\)\\s\\d{3}-\\d{4}");
    String* subject = new String("(222) 555-1212");

    Pattern* p = Pattern::compile(regex);
    Matcher* m = p->matcher(subject);
    dg_boolean b = m->matches();

    EXPECT_EQ(dg_true, b);

    SafeDelete(m);
    SafeDelete(p);

    SafeDelete(regex);
    SafeDelete(subject);
}

TEST(Dragon_Util_Regex_RegexTest, findBasic) {
    String* regex = new String("\\w+");
    String* subject = new String("Hello World");

    Pattern* p = Pattern::compile(regex);
    Matcher* m = p->matcher(subject);

    dg_boolean result1 = m->find();
    ASSERT_EQ(dg_true, result1);

    String* match1 = new String("Hello");
    String* group1 = m->group();
    dg_boolean strEqu = match1->equals(group1);
    EXPECT_EQ(dg_true, strEqu);
    SafeDelete(match1);
    SafeDelete(group1);

    dg_boolean result2 = m->find();
    ASSERT_EQ(dg_true, result2);

    String* match2 = new String("World");
    String* group2 = m->group();
    dg_boolean strEqu2 = match2->equals(group2);
    EXPECT_EQ(dg_true, strEqu2);
    SafeDelete(match2);
    SafeDelete(group2);

    SafeDelete(m);
    SafeDelete(p);

    SafeDelete(regex);
    SafeDelete(subject);
}