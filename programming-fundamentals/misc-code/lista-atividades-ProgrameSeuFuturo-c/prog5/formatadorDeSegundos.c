#include <stdio.h>

int main(int argc, char **argv)
{
	//1. Recerber uma quantidade de segudos
	//2. Imprimir na seguite formatação horas : minutos : segundos
	
	unsigned int segundosInput, segundos, minutos, horas;
	
	printf("Digite um quantidade de segundos: ");
	scanf("%d", &segundosInput);
	
	horas = segundosInput / 3600;
	minutos = (segundosInput % 3600) / 60;
	segundos = (segundosInput % 3600) % 60;
	
	printf("%d : %d : %d",horas, minutos, segundos);
	
	
	return 0;
}

