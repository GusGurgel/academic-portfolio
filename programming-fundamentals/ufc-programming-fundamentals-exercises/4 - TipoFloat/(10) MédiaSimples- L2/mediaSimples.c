#include <stdio.h>

int main(int argc, char **argv)
{
	int quantNotas = 0, total = 0;
	float notaSoma = 0, notaX;
	
	
	scanf("%d", &quantNotas);
	total = quantNotas;
	while(quantNotas > 0)
	{
		quantNotas--;
		scanf("%f", &notaX);
		notaSoma += notaX;
	}
	printf("%0.1f", (notaSoma/total) );
	
	return 0;
}

