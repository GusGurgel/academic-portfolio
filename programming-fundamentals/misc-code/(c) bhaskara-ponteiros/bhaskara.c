#include <stdio.h>
#include <math.h>

void bhaskara(int a, int b, int c, int* x1, int* x2, int *noValue)
{
	int delta = sqrt( (b*b) - 4*a*c);
	*noValue = 0;
	if(delta > 0)
	{
		*x1 = (-b + delta) / (2*a);
		*x2 = (-b - delta) / (2*a);
	}
	else
	{
		*noValue = 1;
	}
}

int main(int argc, char **argv)
{
	int x1 = 0, x2 = 0, noValue = 0, a = 1, b = 2, c = -15;
	
	bhaskara(a,b,c, &x1, &x2, &noValue);
	
	if(!noValue)
	{
		printf("%dx^2 - %dx + %d\nx1:%d\nx2:%d",a , b, c, x1, x2);
	}
	else
	{
		printf("%dx^2 - %dx + %d\nNão possui raizes reais",a , b, c);
	}
	
	return 0;
}

