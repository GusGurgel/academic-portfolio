#include <stdio.h>

int main(int argc, char **argv)
{
	int resp1 = 0, resp2 = 0, resp3 = 0, resp4 = 0;
	int points = 0; 
	
	scanf("%d\n%d\n%d\n%d", &resp1, &resp2, &resp3, &resp4);
	if(resp1 == 4)
	{
		points++;
	}
	if(resp2 == 1)
	{
		points++;
	}
	if(resp3 == 3)
	{
		points++;
	}
	if(resp4 == 4)
	{
		points++;
	}
	
	if(points == 0)
	{
		printf("Nunca assistiu");
	}
	
	if(points == 1)
	{
		printf("Ja ouviu falar");
	}
	
	if(points == 2)
	{
		printf("Interessado no assunto");
	}
	
	if(points == 3)
	{
		printf("Fa");
	}
	
	if(points == 4)
	{
		printf("Super fa");
	}
	return 0;
}

