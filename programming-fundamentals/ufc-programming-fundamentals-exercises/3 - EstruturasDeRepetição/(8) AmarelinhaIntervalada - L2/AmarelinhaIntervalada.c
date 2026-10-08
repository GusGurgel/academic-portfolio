/*
 * variaveis:
 * 1. contElementos;
 * 2. limiteA
 * 3. limiteB
 * 
 * 
 * 
 * */
#include <stdio.h>

int main(int argc, char **argv)
{
	int contElementos = 0, limiteA = 0, limiteB = 0, elementoX = 0;
	int soma = 0;
	scanf("%d %d %d", &contElementos, &limiteA, &limiteB);
	
	
	
	while(contElementos > 0)
	{
		contElementos--;
		scanf("%d", &elementoX);
		if( (elementoX >= limiteA) && (elementoX <= limiteB) )
		{
			soma++;
		}
	}
	printf("%d", soma);
	
	return 0;
}

