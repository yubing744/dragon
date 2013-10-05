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

#ifndef Math_Lang_Dragon_H
#define Math_Lang_Dragon_H

#include <dragon/config.h>

BeginPackage2(dragon, lang)

/**
 * math utils
 * 
 */
class _DragonExport Math
{
public:
	static const double E;
	static const double PI;

public:
	static double sin(double a);
	static double cos(double a);
	static double tan(double a);
	static double asin(double a);
	static double acos(double a);
	static double atan(double a);

	static double toRadians(double angdeg);
	static double toDegrees(double angrad);

	static double exp(double a);
	static double log(double a);
	static double log10(double a);

	static float sqrt(float a);
	static double sqrt(double a);

	static double cbrt(double a);
	static double ceil(double a);
	static double floor(double a);
	static double atan2(double y,double x);
	static double pow(double a,double b);
	static double pow(double a,int b);

	static int round(float a);
	static long round(double a);

	static double random();

	static int abs(int a);
	static long abs(long a);
	static float abs(float a);
	static double abs(double a);

	static int max(int a,int b);
	static long max(long a,long b);
	static float max(float a,float b);
	static double max(double a,double b);

	static int min(int a,int b);
	static long min(long a,long b);
	static float min(float a,float b);
	static double min(double a,double b);

	static double signum(double d);
	static float signum(float f);

	static double hypot(double x,double y);
};

EndPackage2//(dragon, lang)

#endif//Math_Lang_Dragon_H
