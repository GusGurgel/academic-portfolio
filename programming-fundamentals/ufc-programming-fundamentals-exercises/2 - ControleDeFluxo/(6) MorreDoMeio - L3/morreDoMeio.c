#include <stdio.h>

int main()
{
	int valor1, valor2, valor3, maior, menor;
	
	scanf("%d %d %d", &valor1, &valor2, &valor3);
	
    //Achar maior valor
	if(valor1 > valor2){
		maior = valor1;
	}else{
		maior = valor2;
	}
	if(maior < valor3){
		maior = valor3;
	}
	
	//Achar menor valor
	if(valor1 < valor2){
		menor = valor1;
	}else{
		menor = valor2;
	}
	if(menor > valor3){
		menor = valor3;
	}
	
	if(valor1 != maior && valor1 != menor){
		printf("%d", valor1);
	}else if(valor2 != maior && valor2 != menor){
		printf("%d", valor2);
	}else if(valor3 != maior && valor3 != menor){
		printf("%d", valor3);
	}
	
	
	return 0;
}
