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

#include <stdio.h>

int func(int n) {
	int sum = 0;

	for (int i=0; i<n; i++) {
		sum += i;
	}

	return sum;
}


int main(int argc, char** argv) {
	int i;
	long result = 0;

	for (i=1; i<=100; i++) {
		result += i;
	}

	printf("result [1-100] = %d \n", result);
	printf("result [1-250] = %d \n", func(250));
}