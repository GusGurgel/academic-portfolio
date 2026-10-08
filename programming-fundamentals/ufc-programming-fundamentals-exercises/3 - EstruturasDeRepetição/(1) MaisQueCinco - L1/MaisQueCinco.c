/*
 * Somar de x até y contando com x e y
 * */
#include <stdio.h>

int main(int argc, char **argv)
{
	int x = 0,y = 0,soma = 0;
	scanf("%d\n%d", &x, &y);
	
	if( (x < y) && !(x == y) )
	{
		x--;
		while(x < y){
			x++;
			soma += x;
		}
		printf("%d", soma);
	}
	else if(x == y)
	{
		printf("%d", x);
	}
	else
	{
		printf("invalido");
	}
	
	
	return 0;
}

