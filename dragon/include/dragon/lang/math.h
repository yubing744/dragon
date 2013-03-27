// Copyright 2013 the Dragon project authors. All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//     * Neither the name of Google Inc. nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef DRAGON_LANG_MATH_H_
#define DRAGON_LANG_MATH_H_

#include "lang.h"

BeginPackage2(dragon,lang)

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

	//static int max(int a,int b);
	//static long max(long a,long b);
	//static float max(float a,float b);
	//static double max(double a,double b);

	//static int min(int a,int b);
	//static long min(long a,long b);
	//static float min(float a,float b);
	//static double min(double a,double b);

	static double signum(double d);
	static float signum(float f);

	static double hypot(double x,double y);

};

EndPackage2

#endif