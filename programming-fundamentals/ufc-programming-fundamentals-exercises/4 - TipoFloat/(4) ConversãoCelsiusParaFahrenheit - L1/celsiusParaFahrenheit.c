#include <stdio.h>

int main()
{
	float valorCelsius;
	scanf("%f", &valorCelsius);
	printf("%0.2f", (valorCelsius * (9.0 / 5)) + 32);
	
	return 0;
}
