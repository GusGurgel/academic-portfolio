#include <stdio.h>

/*
Deixei implementado uma forma que concidera os números maiores repetidos
mas ele ainda tem problema
*/

int main(int argc, char **argv)
{
	int numeroJuizes = 0, elementoX = 0, maior = 0, menor = 10;
	//int contMaior = 1, contMenor = 1;
	int soma = 0;
	scanf("%d", &numeroJuizes); 
	  
	while(numeroJuizes > 0)
	{
		numeroJuizes--;
		scanf("%d", &elementoX);
		soma += elementoX;
		if(elementoX > maior)
		{
			maior = elementoX;
		}	
		/*	
		else if(elementoX == maior)
		{	
			contMaior++;
		}
		*/
		if(elementoX < menor)
		{
			menor = elementoX;
		}
		/*
		else if(elementoX == menor)
		{
			contMenor++;
		}
		*/
		
	}
	//soma -= ((menor * contMenor) + (maior * contMaior));
	soma -= (menor + maior);
	printf("%d", soma);
	return 0;
}

