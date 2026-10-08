/*5 valores, dar o menor*/

#include <stdio.h>

int main(int argc, char **argv)
{
	int x = 0, vezes = 0, menor;
	
	while (vezes < 5)
	{
		vezes++;
		scanf("%d", &x);
		if(vezes == 1)
		{
			menor = x;
		}else if(x < menor)
		{
			menor = x;
		}
	}
	printf("%d", menor);
	
	
	return 0;
}

