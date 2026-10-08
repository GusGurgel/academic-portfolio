#include <stdio.h>



int main(int argc, char **argv)
{
	//0 para par 1 para impar
	int jog1, dedosJog1, dedosJog2;
	
	scanf("%d\n%d\n%d", &jog1, &dedosJog1, &dedosJog2);
	
	//Caso para ganhar par
	if(jog1 == 0 && ((dedosJog1+dedosJog2) % 2) == 0)
	{
		printf("Venceu");
	}
	else if(jog1 == 1 && ((dedosJog1+dedosJog2) % 2) != 0)
	{
		printf("Venceu");
	}
	else
	{
		printf("Perdeu");
	}
		
	
	return 0;
}

