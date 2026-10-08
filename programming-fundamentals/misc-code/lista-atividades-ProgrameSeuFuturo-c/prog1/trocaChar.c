#include <stdio.h>

int main(int argc, char **argv)
{
/*
 * 1. receber variável (a) e (b)
 * 2. fazer troca de (a) --> (b) e (b) --> (a)
 * 
 */
	
	char a, b;
	char old = ' '; 
	
	//Get a
	printf("Digite o valor da char A: ");
	scanf("%c", &a);
	
	//Get b
	printf("Digite o valor da char B: ");
	scanf(" %c", &b);
	
	printf("\nValores antes da troca (A) --> (%c) | (B) --> (%c)", a, b);
	
	old = a;
	a = b;
	b = old;
	
	printf("\nValores depois da conversão (A) --> (%c) | (B) --> (%c)", a, b);
	
	return 0;
}

