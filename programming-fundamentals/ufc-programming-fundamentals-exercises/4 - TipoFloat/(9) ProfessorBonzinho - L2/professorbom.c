#include <stdio.h>

/*
 * n1
 * n2
 * n3
 * t1
 * 
 * descarta menor nota e soma com trabalho e divide por 4
 * aprovado se maior ou igual a 7 
 * 
 * */

int main(int argc, char **argv)
{
	float n1 = 0, n2 = 0, n3 = 0, trabalho = 0;
	float media = 0;
	
	scanf("%f\n%f\n%f\n%f", &n1, &n2, &n3, &trabalho);
	if(n1 < n2 && n1 < n3)
	{
		n1 = 0;
	}else if(n2 < n1 && n2 < n3)
	{
		n2 = 0;
	}else
	{
		n3 = 0;
	}
	
	media = ((n1 + n2 + n3 + trabalho) / 3.0 );
	
	if(media >= 7)
	{
		printf("Aprovado com %0.1f", media);
	}else
	{
		printf("Final com %0.1f", media);
	}
	
	return 0;
}

