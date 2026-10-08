#include <stdio.h>

int main(int argc, char **argv)
{
	//Ordenados 0 para verdadeiro 1 para falso
	int rufCount = 0, rufinhoX = 0, ordenados = 1;
	int rufinhoA = 0;
	
	scanf("%d", &rufCount);
	
	while(rufCount > 0)
	{
		scanf("%d", &rufinhoX);
		
		//Se achar falha na ordenação torna ordenados falso, caso não ordenados sera verdade
		if(rufinhoX < rufinhoA)
		{
			ordenados = 0;
		}
		rufinhoA = rufinhoX;
		
		rufCount--;
	}
	
	if(ordenados)
	{
		printf("sim");
	}else
	{
		printf("nao");
	}
	
	return 0;
}
