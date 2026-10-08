

#include <stdio.h>

int main(int argc, char **argv)
{
	int arrayLength = 0, inp = 0;
	scanf("%d", &arrayLength);
	
	int arrayPar[arrayLength];
	int arrayImpar[arrayLength];
	
	for(int i = 0; i < arrayLength; i++)
	{
		arrayPar[i] = 0;
		arrayImpar[i] = 0;
	}	
	
	for(int i = 0; i < arrayLength; i++)
	{
		scanf("%d", &inp);
		//caso Par
		if( (inp % 2) == 0 )
		{
			arrayPar[i] = inp;
		}
		//caso impar
		else
		{
			arrayImpar[i] = inp;
		}
	}
	
	
	for(int i = 0; i < arrayLength; i++)
	{
		if(arrayImpar[i] != 0)
		{
			printf("%d ",arrayImpar[i]);
		}
	}
	
	printf("\n");
	
	for(int i = 0; i < arrayLength; i++)
	{
		if(arrayPar[i] != 0)
		{
			printf("%d ",arrayPar[i]);
		}
	}

	return 0;
}


