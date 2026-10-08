#include <stdio.h>

int main(int argc, char **argv)
{
	int nJogadores, distA, distB;
	int distAtual = 0;
	int ganhadorDist = -1;
	int ganhador = 0;
	int count = 0;
	
	scanf("%d", &nJogadores);
	
	while(nJogadores > 0)
	{
		nJogadores--;
		count++;
		
		scanf("%d %d", &distA, &distB);
		distAtual = distA - distB;
		
		if(distAtual < 0)
		{
			distAtual = distAtual * -1;
		}
	
		
		if(ganhadorDist == -1 && !((distA < 10) || (distB < 10)) )
		{
			ganhadorDist = distAtual;
			ganhador = count;
		}
		
		
		if( !((distA < 10) || (distB < 10)) )
		{
			if(distAtual < ganhadorDist)
			{
				ganhadorDist = distAtual;
				ganhador = count;
			}
		}
		
	}
	if(ganhadorDist == -1)
	{
		printf("sem ganhador");
	}
	else
	{
		ganhador--;
		printf("%d", ganhador);
	}
	
	return 0;
}

