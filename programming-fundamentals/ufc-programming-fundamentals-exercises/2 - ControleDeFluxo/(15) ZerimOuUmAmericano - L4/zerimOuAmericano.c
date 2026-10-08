#include <stdio.h>

int main(int argc, char **argv)
{
	int jog1, jog2, jog3, jog4, total ,resto;
	
	scanf("%d\n%d\n%d\n%d", &jog1, &jog2, &jog3, &jog4);
	
	total = (jog1 + jog2 + jog3 + jog4);
	
	if(total == 0)
	{
		printf("nenhum");
	}else
	{
		if(total < 4)
		{
			total += 4;
		}
		resto = total % 4;
		if(resto == 1)
		{
			printf("jog1");
		}else if(resto == 2)
		{
			printf("jog2");
		}else if(resto == 3)
		{
			printf("jog3");
		}else if(resto == 0)
		{
			printf("jog4");
		}
	}
	
	return 0;
}
