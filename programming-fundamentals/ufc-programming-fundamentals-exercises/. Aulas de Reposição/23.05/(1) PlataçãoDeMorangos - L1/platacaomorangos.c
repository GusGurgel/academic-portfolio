#include <stdio.h>

//linha 1: comp1
//linha 2: larg1
//linha 3: comp2
//linha 4: larg2

int main(int argc, char **argv)
{
	int comp1 = 0, comp2 = 0, larg1 = 0, larg2 = 0;
	
	scanf("%d\n%d\n%d\n%d", &comp1, &larg1, &comp2 ,&larg2);
	
	if( (comp1 * larg1) > (comp2 * larg2))
	{
		printf("%d\n", (comp1 * larg1) );
	}else
	{
		printf("%d\n", (comp2 * larg2) );
	}
	
	return 0;
}

