#include <stdio.h>

int main(int argc, char **argv)
{
	float n1, n2;
	
	scanf("%f\n%f", &n1, &n2);
	
	//Formato inteiro
	printf("%d\n", (int)(n1 / n2) );
	
	//Resto
	printf("%d\n", ((int)n1 % (int)n2) );
	
	//Formato float
	printf("%0.2f\n", (float)(n1 / n2) );

	
	return 0;
}

