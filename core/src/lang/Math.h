#include "lang.h"

#if !defined(Lang_Math_H)
#define Lang_Math_H
#pragma once

BeginPackage2(ProjectName,lang)

class _DragonExport Math :public Object
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