#include <stdio.h>

int main(int argc, char **argv)
{
	//Empresa contrata encanador 45R$ por dia
	//1. Pegar número de dias
	//2. -8% pelo imposto de renda
	
	int numeroDias;
	
	printf("Digite o número de dias que o encanador trabalhou: ");
	scanf("%i", &numeroDias);

	printf("\nA renda líquida do encanado é de: %.2fR$", (numeroDias * 45) * 0.92);
	
	return 0;
}

