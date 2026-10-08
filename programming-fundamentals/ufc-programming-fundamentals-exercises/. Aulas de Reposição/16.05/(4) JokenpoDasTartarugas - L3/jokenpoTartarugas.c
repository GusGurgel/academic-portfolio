//Jogo 1 pedra 2 papel 3 tesoura

#include <stdio.h>

int main(int argc, char **argv)
{
	int jog1 = 0, jog2 = 0;
	scanf("%d\n%d", &jog1, &jog2);
	
	if(jog1 == jog2)
	{
		printf("empate");
	}
	else if( (jog1 == 1 && jog2 == 3) || (jog1 == 2 && jog2 == 1) || (jog1 == 3 && jog2 == 2))
	{
		printf("jog1");
	}
	else
	{
		printf("jog2");
	}
	
	return 0;
}

