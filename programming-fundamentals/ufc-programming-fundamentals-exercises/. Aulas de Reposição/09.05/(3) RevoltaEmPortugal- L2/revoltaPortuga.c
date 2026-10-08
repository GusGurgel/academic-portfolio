#include <stdio.h>

int main(int argc, char **argv)
{
	int limInf = 0, limSup = 0, soldados = 0, rebeldes = 0;
	
	scanf("%d\n%d", &limInf, &limSup);
	
	while(limInf < limSup)
	{
		limInf++;
		if((limInf % 2) == 0)
		{
			soldados += limInf;
		}
		else
		{
			rebeldes += limInf;
		}
	}
	if(soldados > rebeldes)
	{
		printf("soldados");
		return 0;
	}
	printf("rebeldes");
	return 0;
}

