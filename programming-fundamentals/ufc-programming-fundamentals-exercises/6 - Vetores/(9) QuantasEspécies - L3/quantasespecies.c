
#include <stdio.h>

int main(int argc, char **argv)
{
	int vetLength = 0, toAdd = 0, encontrado = 0, nextIndex = 0;
	int count = 0;
	scanf("%d", &vetLength);
	
	int vetEncontrado[vetLength];
	
	for(int i = 0; i < vetLength; i++)
	{	
		vetEncontrado[i] = 0;
	}
	
	for(int i = 0; i < vetLength; i++)
	{
		
		scanf("%d", &toAdd);
		
		for(int y = 0; y < vetLength; y++)
		{
			if(toAdd == vetEncontrado[y])
			{
				encontrado = 1;
			}
		}
		
		if(!encontrado)
		{
			vetEncontrado[nextIndex] = toAdd;
			nextIndex++;
		}
		encontrado = 0;
	}
	
	for(int i = 0; i < vetLength; i++)
	{
		if(vetEncontrado[i] != 0){ count++; }
	}
	
	printf("%d", count);
	
	return 0;
}


