#include <stdio.h>

int main()
{
	//Linha 1 vai ser a quantidade de caso de teste
	//Cada caso de teste é primeira linha Tamanho do vetor e o numero que ele grita
	//O vetor de tamanho da primeira linha dado o grito nele
	
	int quantCasos = 0, vetLength = 0, grito = 0;
	scanf("%d", &quantCasos);
	
	for(int i = 0; i < quantCasos; i++)
	{
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
		printf("\n");
	}
	
	return 0;
}

