#include <stdio.h>

int main(int argc, char **argv)
{
	//1. ler o valor da despesa de um restaurante + valor da gorjeta + ...
	//gorjeta + número de pessoas para dividir
	//2. imprimir o valor para ser pago igualmente para cada pessoa.
	
	float dispesa, porcentoGojeta ,valorTotal, valorPorPessoa;
	short int numeroPessoas;
	
	//Get conta do restaurante
	printf("Digite a conta do restaurante: ");
	scanf("%f", &dispesa);
	
	//Get porcentagem da gorjeta
	printf("Digite a gorjeta (%%) : ");
	scanf("%f", &porcentoGojeta);
	
	//Definir valor total paseado na gorjeta
	valorTotal = dispesa + (dispesa * (porcentoGojeta / 100));
	
	//Get número de pessoas
	printf("Digite o número de pessoas para dividir a conta: ");
	scanf("%hi", &numeroPessoas);
	
	//Definir valor por pessoa	
	valorPorPessoa = valorTotal / numeroPessoas;
	
	//Printar valor
	printf("\nO valor a ser pago por cada pessoa será: %.2fR$", valorPorPessoa);
	
	
	return 0;
}

