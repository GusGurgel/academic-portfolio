#include <stdio.h>

int main(int argc, char **argv)
{
	int arrayLength = 0;
	scanf("%d", &arrayLength);
	int array[arrayLength];
	
	for(int i = 0; i < arrayLength; i++)
	{
		scanf("%d", &array[i]);
	}	

	for(int i = 0; i < arrayLength; i++)
	{
		printf("%d ", array[(arrayLength-1)- i] );
	}	
	
	
	return 0;
}


