#include <stdio.h>
#include <math.h>

int bhaskara(double a, double b, double c, double* x1, double* x2)
{
	double delta = sqrt( (b*b) - 4*a*c);
	
	if(delta > 0)
	{
		*x1 = (-b + delta) / (2*a);
		*x2 = (-b - delta) / (2*a);
		return 1;
	}
	else if(delta == 0)
	{
		*x1 = (-b + delta) / (2*a);
		*x2 = (-b - delta) / (2*a);
		return 0;
	}
	else
	{
		return -1;
	}
}
