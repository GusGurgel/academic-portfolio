/*Todo os números pares e divisíveis por 3 de x a y*/

#include <stdio.h>

int main(int argc, char **argv)
{
	int x = 0,y = 0,soma = 0;
	
	scanf("%d\n%d", &x, &y);
	
	if( (x < y) && !(x == y) )
	{
		while(x < y)
		{
			x++;
			if( ( (x % 3) == 0 ) && ( (x % 2) == 0 ) )
			{
				soma += x;
			}
		}
		printf("%d", soma);
	}
	else if( (x == y) && ( (x % 3) == 0 ) && ( (x % 2) == 0 ) )
	{
		printf("%d", x);
	}
	else if( (x == y) && (( (x % 3) != 0 ) || ( (x % 2) != 0 )) )
	{
		printf("0");
	}
	else
	{
		printf("invalido");
	}
	
	
	return 0;
}

