#include <stdio.h>

int maior(int v[], int tam)
{
	int maior = 0;
	for(int i = 0; i < tam; i++)
	{
		if(v[i] > maior){ maior = v[i]; }
	}
	return maior; 
}

int menor(int v[], int tam)
{
	int menor = 0;
	for(int i = 0; i < tam; i++)
	{
		if(i == 0) {menor = v[i]; }
		if(v[i] < menor){ menor = v[i]; }
	}
	return menor; 
}

int somaMaiorMenor(int v[], int tam)
{
	return (maior(v, tam) + menor(v, tam));
}


