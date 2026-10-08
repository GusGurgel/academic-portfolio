#include <stdio.h>

int main(int argc, char **argv)
{
	/*
	cada dígito par da matrıícula vale 3 FUP$ e;
	cada dıígito ıímpar da matrıícula vale 1 FUP$.
	 */
	 
	 // 0 é par
	 // 1 é impar
	 
	int digito = 0, fups = 0;
	int i = 0;
	
	
	while(i < 6)
	{
		scanf("%d", &digito);
		
		//Caso par
		if(digito % 2 == 0)
		{
			fups += 3;
		}
		//Caso impar
		else
		{
			fups += 1;
		}
		
		i++;
	}
	
	printf("%d", fups);
	
	return 0;
}
