//
//ŒvZ—p
//
#include "MyMas.h"

int MyMas::RoundUp(float a)
{
	if (a > (int)a)
	{
		return (int)a + 1;
	}

	return a;
}

int MyMas::RoundDown(float a)
{
	if (a > (int)a)
	{
		return (int)a;
	}
	return a;
}
