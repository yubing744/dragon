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

#include <dragon/lang/math.h>

#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <ctime>

Import std;
Import dragon::lang;

const double Math::E=2.718281828459045;
const double Math::PI=3.141592653589793;

double Math::sin(double a){
	return ::sin(a);
}

double Math::cos(double a){
	return ::cos(a);
}

double Math::tan(double a){
	return ::tan(a);
}

double Math::asin(double a){
	return ::asin(a);
}

double Math::acos(double a){
	return ::acos(a);
}

double Math::atan(double a){
	return ::atan(a);
}

double Math::toRadians(double angdeg){
	return angdeg*Math::PI/90.0;
}

double Math::toDegrees(double angrad){
	return 90.0*angrad/Math::PI;
}

double Math::exp(double a){
	return ::exp(a);
}

double Math::log(double a){
	return ::log(a);
}

double Math::log10(double a){
	return ::log10(a);
}

double Math::sqrt(double a){
	return ::sqrt(a);
}

double Math::cbrt(double a){
	return Math::pow(a,1.0/3.0);
}

double Math::ceil(double a){
	return ::ceil(a);
}

double Math::floor(double a){
	return ::floor(a);
}


double Math::atan2(double y,double x){
	return ::atan2(y,x);
}

double Math::pow(double a,double b){
	return ::pow(a,b);
}

double Math::pow(double a,int b){
	return ::pow(a,b);
}

int Math::round(float a){
	return (int)Math::floor(a + 0.5f);
}

long Math::round(double a){
	return (long)Math::floor(a + 0.5);
}

double Math::random(){
	return ::rand()/(double)RAND_MAX;
}

int Math::abs(int a){
	return ::abs(a);
}

long Math::abs(long a){
	return ::abs(a);
}

float Math::abs(float a){
	return ::abs(a);
}

double Math::abs(double a){
    return ::abs(a);
}

#define DRAGON_MAX(x, y) (x > y ? x : y)

int Math::max(int a,int b){
	return DRAGON_MAX(a, b);
}

long Math::max(long a,long b){
	return DRAGON_MAX(a, b);
}

float Math::max(float a,float b){
	return DRAGON_MAX(a, b);
}

double Math::max(double a,double b){
	return DRAGON_MAX(a, b);
}

#define DRAGON_MIN(x, y) (x > y ? y : x)

int Math::min(int a,int b){
	return DRAGON_MIN(a, b);
}

long Math::min(long a,long b){
	return DRAGON_MIN(a, b);
}

float Math::min(float a,float b){
	return DRAGON_MIN(a, b);
}

double Math::min(double a,double b){
	return DRAGON_MIN(a, b);
}

double Math::signum(double d){
	if(d>0)
	{
		return 1.0;
	}
	else if(d<0)
	{
		return -1.0;
	}

	return 0;
}

float Math::signum(float f)
{
	if(f>0)
	{
		return 1.0f;
	}
	else if(f<0)
	{
		return -1.0f;
	}

	return 0;
}

double Math::hypot(double x,double y)
{
	return Math::sqrt(x*x +y*y);
}
