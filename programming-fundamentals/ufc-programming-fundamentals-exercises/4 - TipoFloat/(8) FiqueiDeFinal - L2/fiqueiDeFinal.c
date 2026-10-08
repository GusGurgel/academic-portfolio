#include <stdio.h>

int main(int argc, char **argv)
{
	float n1, n2, media, final;
	scanf("%f\n%f", &n1, &n2);
	media = ((n1 + n2) / 2.0);
	
	if(media >= 7)
	{
		printf("aprovado");
	}
	else if(media < 4 )
	{
		printf("reprovado");
	}
	else if(media > 4 && media < 7)
	{
		scanf("%f", &final);
		media = ((media + final) / 2);
		if(media >= 5)
		{
			printf("aprovado na final");
		}
		else
		{
			printf("reprovado na final");
		} 
	}
	
	
	return 0;
}
