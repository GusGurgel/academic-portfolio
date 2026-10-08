#include <stdio.h>

int main()
{
	int vet[5];
	int maior = 0, menor = 0;
	
	//~ scanf("%d %d %d %d %d",&vet[0], &vet[1],
	//~ &vet[2], &vet[3], &vet[4]);
	
	for(int i = 0; i < 5; i++)
	{
		scanf("%d",&vet[i]);
		if(i == 0){ menor = vet[i]; }
		
		if(vet[i] > maior)
		{
			maior = vet[i];
		}
		if(vet[i] < menor)
		{
			menor = vet[i];
		}
	}
	
	printf("%d", maior+menor);
		
	return 0;
}


