#include <stdio.h>

int main()
{
	//1. Receber três valoes rufinho1, rufinho2, rufinho3
	//2. Atribuir charRufinho1, charRufinho2, charRufinho3 (G) para o maior
	//(M) Para o do meio e (P) para o menor
	
	//Nunca vão ser iguais
	int alturaRufinho1, alturaRufinho2, alturaRufinho3, maior, menor;
	char charRufinho1, charRufinho2, charRufinho3;
	
	scanf("%d\n%d\n%d", &alturaRufinho1, &alturaRufinho2, &alturaRufinho3);
	
	if(alturaRufinho1 > alturaRufinho2 && alturaRufinho1 > alturaRufinho3){
		charRufinho1 = 'G';
		maior = alturaRufinho1;
	}else if(alturaRufinho2 > alturaRufinho3 && alturaRufinho2 > alturaRufinho1){
		charRufinho2 = 'G';
		maior = alturaRufinho2;
	}else{
		charRufinho3 = 'G';
		maior = alturaRufinho3;
	}
	
	if(alturaRufinho1 < alturaRufinho2 && alturaRufinho1 < alturaRufinho3){
		charRufinho1 = 'P';
		menor = alturaRufinho1;
	}else if(alturaRufinho2 < alturaRufinho3 && alturaRufinho2 < alturaRufinho1){
		charRufinho2 = 'P';
		menor = alturaRufinho2;
	}else{
		charRufinho3 = 'P';
		menor = alturaRufinho3;
	}
	
	if(alturaRufinho1 != maior && alturaRufinho1 != menor){
		charRufinho1 = 'M';
	}else if(alturaRufinho2 != maior && alturaRufinho2 != menor){
		charRufinho2 = 'M';
	}else{
		charRufinho3 = 'M';
	}
	
	printf("%c %c %c", charRufinho1, charRufinho2, charRufinho3);
	
	return 0;
}

