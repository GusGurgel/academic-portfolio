#include <stdio.h>

int main()
{
	/*
	 * p1 peso 5
	 * p2 peso 3
	 * t1 peso 2
	 * */
	float p1 = 0, p2 = 0, t1 = 0;
	
	scanf("%f\n%f\n%f", &p1, &p2, &t1);

	printf("%0.2f", ((p1 * 5) + (p2 * 3) + (t1 * 2)) / 10 );
	 
	return 0;
}
