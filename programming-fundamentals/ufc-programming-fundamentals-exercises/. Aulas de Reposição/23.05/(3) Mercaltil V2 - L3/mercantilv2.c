#include <stdio.h>

int main(int argc, char **argv)
{
		/*
		 * linha 1: Chute do primeiro jogador
		 * linha 2: Segundo jogar 1 para maior 0 para menor
		 * linha 3: Valor real do produto
		*/
		
		float jog1, valorReal;
		int jog2;
		
		
		scanf("%f\n%d\n%f", &jog1, &jog2, &valorReal);
		
		if(jog1 == valorReal)
		{
			printf("primeiro");
		}
		else if(jog1 > valorReal && jog2 == 0)
		{
			printf("segundo");
		}
		else if(jog1 < valorReal && jog2 == 1)
		{
			printf("segundo");
		}
		else
		{
			printf("primeiro");
		}
		
		
	return 0;
}

