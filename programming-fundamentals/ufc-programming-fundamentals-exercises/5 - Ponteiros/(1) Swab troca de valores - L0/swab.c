#include <stdio.h>

void swap(int *x, int *y)
{
	int aux = *x;
	
	*x = *y;
	*y = aux;
}
