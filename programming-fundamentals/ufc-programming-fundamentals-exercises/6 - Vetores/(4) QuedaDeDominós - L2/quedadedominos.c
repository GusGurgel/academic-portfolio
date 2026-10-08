#include <stdio.h>

int main(int argc, char **argv)
{
	//ordeando 0{false}
	//ordeando 1{true}
	int arrayLength = 0, ordenado = 1;
	scanf("%d", &arrayLength);
	int array[arrayLength];
	
	for(int i = 0; i < arrayLength; i++) { array[i] = 0; }	
	
	for(int i = 0; i < arrayLength; i++)
	{
		scanf("%d", &array[i]);
		if(i != 0)
		{  
		    if( array[i] < array[i-1])
	    	{
		    	ordenado = 0;
		    }
		}
	}
	
	if(ordenado)
	{
		printf("ok");
	}
	else
	{
		printf("precisa de ajuste");
	}
	
	return 0;
}


