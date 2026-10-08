/*
 * Receber dois números x e n. x = tamanho da calça
 * n = número de calças que irão ser usadas
 * dizer os valores n < x;
 * */
 
 
#include <stdio.h>

int main(int argc, char **argv)
{
	int tamanhoC = 0, nCalcas = 0, repete = 0, xCalca = 0; 
	
	scanf("%d %d", &tamanhoC, &nCalcas);
	
	while(nCalcas > 0)
	{
		nCalcas--;
		scanf("%d", &xCalca);
		if(xCalca > tamanhoC)
		{
			repete++;
		}
	}
	printf("%d", repete);
	return 0;
}

