#include <stdio.h>

int main(int argc, char **argv)
{
	float ap1 = 0, ap2 = 0, ap3 = 0, premio;
	float total = 0;

	scanf("%f\n%f\n%f\n%f", &ap1, &ap2, &ap3, &premio);
	total = ap1 + ap2 + ap3;
	
	ap1 = premio * (ap1 / total);
	ap2 = premio * (ap2 / total); 
	ap3 = premio * (ap3 / total);
	
	printf("%0.2f\n%0.2f\n%0.2f\n", ap1, ap2, ap3);
	
	return 0;
}
