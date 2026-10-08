#include <stdio.h>
//Um array está contido em outro ?

int main()
{
	int vet1Length = 0, vet2Length = 0;
	
	scanf("%d", &vet1Length);
	int vet1[vet1Length];
	
	for(int i = 0; i < vet1Length; i++)
	{
		scanf("%d", &vet1[i]);
	}
	
	scanf("%d", &vet2Length);
	int vet2[vet2Length];
	
	
	for(int i = 0; i < vet2Length; i++)
	{
		scanf("%d", &vet2[i]);
	}
	
	//Valores inicializados
	
	for(int i = 0; i < vet1Length; i++)
	{
		//Procure
		for(int y = 0; y < vet2Length; y++)
		{
			if(vet1[i] == vet2[y])
			{
				break;
			}
			if(y == (vet2Length-1))
			{
				printf("nao");
				return 0;
			}
		}
	}
	
	printf("sim");
	
	return 0;
}


