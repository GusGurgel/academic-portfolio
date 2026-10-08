/*
 * 1 = Ás (11 Mas vale 1 se estourar)
 * 11 = J (Vale 10)
 * 12 = Q (Vale 10)
 * 13 = K (Vale 10)
 * 
 * 
 * 
 * 
 * */

#include <stdio.h>

int main(int argc, char **argv)
{
	int nCartas = 0, blackSoma = 0, inputCarta = 0;
	int asCount = 0;
	
	scanf("%d", &nCartas);
	
	while(nCartas > 0)
	{
		nCartas--;
		scanf("%d", &inputCarta);
		if( (inputCarta == 11) || (inputCarta == 12) || (inputCarta == 13))
		{
			inputCarta = 10;
		}
		if(inputCarta == 1)
		{
			asCount++;
			inputCarta = 11;
		}
		blackSoma += inputCarta;
	}
	if(asCount > 0 && blackSoma > 21)
	{
		while(asCount > 0 && blackSoma > 21)
		{
			asCount--;
			blackSoma -= 10;
		}
	}
	
	printf("%d",blackSoma);
	
	return 0;
}

