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

#include <math.h>
#include <dragon/lang/math.h>

import dragon::lang;

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
	return rand()/(double)RAND_MAX;
}

#define DD_ABS(a) (a > 0 ? a : -a)

int Math::abs(int a){
//	return ::abs(a);
//    return a > 0 ? = a : -a;
     return DD_ABS(a);
}

long Math::abs(long a){
//	return ::abs(a);
    return DD_ABS(a);
}

float Math::abs(float a){
//	return ::abs(a);
    return DD_ABS(a);
}

double Math::abs(double a){
       //	return ::abs(a);
    return DD_ABS(a);
}

//int Math::max(int a,int b)
//{
//	return 0;
//}
//
//long Math::max(long a,long b)
//{
//	return 0;
//}
//
//float Math::max(float a,float b)
//{
//	return 0;
//}
//
//double Math::max(double a,double b)
//{
//	return 0;
//}
//
//int Math::min(int a,int b)
//{
//	return 0;
//}
//long Math::min(long a,long b)
//{
//	return 0;
//}
//float Math::min(float a,float b)
//{
//	return 0;
//}
//
//double Math::min(double a,double b)
//{
//	return 0;
//}

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
