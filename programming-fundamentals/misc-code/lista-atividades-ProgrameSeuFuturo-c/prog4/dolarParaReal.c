#include <stdio.h>

int main(int argc, char **argv)
{
	//Real para dolar
	
	float valor;
	
	printf("Digite um valor em real para ser convertido em dolar - ");
	scanf("%f", &valor);
	
	printf("\nValor convertido em dolar igual a: %.2f$", valor / 5.30);  
	
	
	
	return 0;
}

