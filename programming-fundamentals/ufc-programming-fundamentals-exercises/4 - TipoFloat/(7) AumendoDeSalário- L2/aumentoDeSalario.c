
/*
* até 1000 20% de almento
* até 1500 15% de almento
* até 2000 10% de almento 
* mais de 2000 5% de alment0
*/
#include <stdio.h>

int main(int argc, char **argv)
{
	 
	float salario; 
	scanf("%f", &salario);
	
	if(salario <= 1000)
	{
		salario = salario * 1.20;
	}
	else if(salario > 1000 && salario <= 1500)
	{
		salario = salario * 1.15;
	}
	else if(salario > 1500 && salario <= 2000)
	{
		salario = salario * 1.10;
	}
	else
	{
		salario = salario * 1.05;
	}
	 
	printf("%0.2f", salario);
	 
	return 0;
}

