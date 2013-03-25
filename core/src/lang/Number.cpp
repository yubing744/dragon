#include "Number.h"

Import ProjectName::lang;

Number::Number(){}


int Number::ParseInt(String num) throw(NumberFormatException)
{
	int result = _wtoi(num);

	if ( !num.equals(L"0") && (result ==0) )
	{
		throw NumberFormatException(String(L"NumberFormatException: ") + num );
	}

	return result;
}

long  Number::ParseLong(String num) throw(NumberFormatException)
{
	long result = _wtol(num);

	if ((!num.equals(L"0")) && (result ==0) )
	{
		throw NumberFormatException(String(L"NumberFormatException: ") + num );
	}

	return result;
}

double  Number::ParseDouble(String num) throw(NumberFormatException)
{
	double result = _wtof(num);

	if ((!num.equals(L"0.0")) && (result ==0) )
	{
		throw NumberFormatException(String(L"NumberFormatException: ") + num );
	}

	return result;
}

float  Number::ParseFloat(String num) throw(NumberFormatException)
{
	float result = (float)_wtof(num);

	if ((!num.equals(L"0.0")) && (result ==0) )
	{
		throw NumberFormatException(String(L"NumberFormatException: ") + num );
	}

	return result;
}

