/*
 * Cabo de guerra 
 * Linha 1: Números de elementos, sempre é par;
 * Linha 2: Elementos em liha, metade Jedi/ Metade Sith
 * 
 * */
 

#include <stdio.h>

int main(int argc, char **argv)
{
	int numeroEle = 0, elementoX = 0, metade = 0, forcaJedi = 0, forcaSith = 0;  
	scanf("%d", &numeroEle);
	metade = (numeroEle/2);
	
	while(numeroEle > 0)
	{
		scanf("%d", &elementoX);
		if(numeroEle > metade)
		{
			//Jedi
			forcaJedi += elementoX;
		}
		else
		{
			//Sith
			forcaSith += elementoX;
		}
		numeroEle--;
	}
	if(forcaJedi == forcaSith)
	{
		printf("Empate");
	}
	else if (forcaJedi > forcaSith)
	{
		printf("Jedi");
	}else
	{
		printf("Sith");
	}
	return 0;
}

