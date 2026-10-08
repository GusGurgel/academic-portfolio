#include <stdio.h>

int main(int argc, char **argv)
{
	int jog1 = 0, jog2 = 0;
	scanf("%d\n%d", &jog1, &jog2);
	
	if(jog1 == jog2)
	{
		printf("empate");
	}
	else if( (jog1 == 1 && jog2 == 3) || (jog1 == 1 && jog2 == 4) || (jog1 == 2 && jog2 == 1) || (jog1 == 2 && jog2 == 5) )
	{
		printf("jog1");
	}
	else if( (jog1 == 3 && jog2 == 4) || (jog1 == 3 && jog2 == 5) || (jog1 == 4 && jog2 == 2) || (jog1 == 4 && jog2 == 5) )
	{
		printf("jog1");
	}
	else if( (jog1 == 5 && jog2 == 1) || (jog1 == 5 && jog2 == 3) )
	{
		printf("jog1");	
	}
	else
	{
		printf("jog2");
	}
	
	return 0;
}

