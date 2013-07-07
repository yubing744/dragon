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

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

/*
#include <dragon/config.h>
#include <dragon/lang/String.h>
#include <stdio.h>

Import dragon::lang;

int main(int argc, char** argv) {
	String* str = new String("Hello World!");
	printf("%s\n", str);
}
*/

/*
#include <stdio.h>

int main(int argc, char** argv) {
	printf("%s\n", "Hello World\n");
}
*/