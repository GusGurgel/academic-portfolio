#include <stdio.h>

int main(int argc, char **argv)
{
	
	int P = 0; //Prufundidade, se chegar ele fica vivo
	int S = 0; //Alutura de cada salto
	int E = 0; //Depois de um salto ele escorrega E
	
	//Valora antes e depois do pulo
	int preSalto = 0, posSalto = 0;
	
	//Quando 1 mando o loop parar
	int parar = 0;
	
	scanf("%d\n%d\n%d", &P, &S, &E);
	
	posSalto += S;
	
	//Valores iniciais
	printf("%d %d\n", preSalto ,posSalto);
	
	//Sempre que o sapo morrer ou viver o loop vai dar break e tornar para 1
	while(!parar)
	{
		//Hora de escorregar
		preSalto = posSalto;
		preSalto -= E;
		
		if(preSalto < 0)
		{
			parar = 1;
			printf("%d morreu\n", preSalto);
			break;
		}
		if(preSalto >= P)
		{
			parar = 1;
			printf("saiu\n");
			break;
		}
		printf("%d ", preSalto);
		
		//Ficou cansado
		if(S > 0) 
		{ 
			S -= 10; 
		} 
		
		//Pulou
		posSalto = preSalto;
		posSalto += S;
		
		if(posSalto < 0 && !parar)
		{
			parar = 1;
			printf("%d morreu\n", posSalto);
			break;
			
		}
		if(posSalto >= P && !parar)
		{
			parar = 1;
			printf("saiu\n");
			break;
		}
		printf("%d\n", posSalto);
	}
	
	return 0;
}

