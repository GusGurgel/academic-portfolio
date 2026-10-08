#include <stdio.h>

int ehPrimo(int n)
{
	int sN = 0;
	
	sN = (n-1);
	
	if(n == 1){ return 0; }
	
	while(sN > 1)
	{
		if( (n % sN) == 0)
		{
			return 0;
		}
		sN--;
	}
	
	return 1;
}

int somaPrimos(int n)
{
	int soma = 0;
	
	while(n > 0)
	{
		if(ehPrimo(n))
		{
			soma += n;
		}
		n--;
	}
	return soma;
}

int somaNaoPrimos(int n)
{
	int soma = 0;
	
	while(n > 0)
	{
		if( (!ehPrimo(n)) )
		{
			soma += n;
		}
		n--;
	}
	return soma;
}

int naoPrimosMenosPrimos(int n)
{
	return somaNaoPrimos(n) -(somaPrimos(n));
}


