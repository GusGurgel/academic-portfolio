#include <stdio.h>

int main()
{
	
	int vetLength = 0, grito = 0;
	
	scanf(" %d %d", &vetLength, &grito);	
	int vet[vetLength];
	
	for(int y = 0; y < vetLength; y++)
	{
		scanf("%d", &vet[y]);
	}
	for(int y = 0; y < vetLength; y++)
	{
		if(vet[y] == grito)
		{
			if(y != 0)
			{ 
				vet[y-1] = (vet[y-1]) * -1; 
			}
			if(y != (vetLength-1) ) 
			{ 
				vet[y+1] = (vet[y+1] * -1); 
			}
		}
	}
	for(int y = 0; y < vetLength; y++)
	{
		printf("%d ", vet[y]);
	}
	
	return 0;
}
	

