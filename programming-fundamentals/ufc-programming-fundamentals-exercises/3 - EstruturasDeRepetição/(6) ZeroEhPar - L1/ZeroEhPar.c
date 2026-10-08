#include <stdio.h>

int main(int argc, char **argv)
{
	int a = 0,b = 0, soma = 0;
	scanf("%d\n%d",&a , &b);
	b++;
	if(a < b)
	{
		while(a < b)
		{
			if( (a % 2) == 0 )
			{
				soma += a;
			}
			a++;
		}
		printf("%d", soma);
	}
	else if(a == b)
	{
		if((a % 2) == 0)
		{
			printf("%d", a);
		}
		else
		{
			printf("%d", 0);
		}
	}
	else
	{
		printf("invalido");
	}
	
	return 0;
}

