#include <stdio.h>

int modulo(int num)
{
	if(num < 0) 
	{
		return (num * -1); 
	}
	else
	{
		return num;
	}
}

int main()
{
	int vetLength = 0, movParkour = 0;
	scanf("%d", &vetLength);
	int vet[vetLength];
	
	
	for(int i = 0; i < vetLength; i++)
	{
		scanf("%d", &vet[i]);
		if(i > 0)
		{
			if( modulo( (vet[i] - vet[i-1]) ) > 1)
			{
				movParkour++;
			}
		}
	}
	
	printf("%d", movParkour);
	
	return 0;
}


