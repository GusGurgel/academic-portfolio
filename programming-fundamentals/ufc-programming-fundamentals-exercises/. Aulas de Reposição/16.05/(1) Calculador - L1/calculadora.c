// 1 soma 2 sub 3 mult 4 divi
#include <stdio.h>

int main(int argc, char **argv)
{
	int num1, num2, opType;
		
	scanf("%d\n%d\n%d", &num1, &num2,&opType);
	
	
	if(opType == 1)
	{
		printf("%d", num1 + num2);
	}
	else if(opType == 2)
	{
		printf("%d", num1 - num2);
	}
	else if(opType == 3)
	{
		printf("%d", num1 * num2);
	}
	else if(opType == 4 && num2 == 0)
	{
		printf("invalida");
	}
	else if(opType == 4)
	{
		printf("%d", num1 / num2);
	}
	else
	{
		printf("invalida");
	}
	
	
	return 0;
}

