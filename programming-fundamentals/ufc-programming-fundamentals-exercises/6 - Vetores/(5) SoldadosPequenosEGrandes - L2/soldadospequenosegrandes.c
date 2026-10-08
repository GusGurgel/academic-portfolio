#include <stdio.h>

int main(int argc, char **argv)
{
	int arrayLength = 0;
	scanf("%d", &arrayLength);
	double array[arrayLength], media;
	
	for(int i = 0; i < arrayLength; i++) { array[i] = 0; }	
	
	for(int i = 0; i < arrayLength; i++)
	{
		scanf("%lf", &array[i]);
		media += array[i];
	}
	
	media /= arrayLength;
	printf("%0.2lf\n", media);
	
	for(int i = 0; i < arrayLength; i++)
	{
		if(array[i] < media)
		{
			printf("P ");
		}
		else if(array[i] == media)
		{
			printf("M ");
		}
		else
		{
			printf("G ");
		}
	}
	
	
	
	return 0;
}


