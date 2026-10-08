#include <stdio.h>

int main(int argc, char **argv)
{
	int capBus = 0, onBus = 0, inputBus = 0;
	
	scanf("%d", &capBus);
	
	while(onBus <= (capBus*2 - 1))
	{
		
		scanf("%d", &inputBus);
		onBus += inputBus;
		
		if(onBus == 0)
		{
			printf("vazio\n");
		}
		else if(onBus < capBus && !(onBus > capBus))
		{
			printf("ainda cabe\n");
		}
		else if(onBus >= capBus && !(onBus >= 2*capBus))
		{
			printf("lotado\n");
		}
	}
	
	printf("hora de partir");
}
