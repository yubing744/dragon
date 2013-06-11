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

#include <dragon/config.h>

#include <gtest/gtest.h>
#include <stdio.h>
#include <string.h>
#include <pcre.h>


//Import dragon::lang;

TEST(Dragon_Util_Regex_RegexTest, BasicTest) {
    pcre *re;
    const char *error;
    char *pattern;
    char *subject;
    unsigned char *name_table;
    unsigned int option_bits;
    int erroffset;

    pattern = "[\\d]";

    re = pcre_compile(
        pattern,              /* the pattern */
        0,                    /* default options */
        &error,               /* for error message */
        &erroffset,           /* for error offset */
        NULL);                /* use default character tables */

    if (re == NULL){
        printf("PCRE compilation failed at offset %d: %s\n", erroffset, error);
    }
}