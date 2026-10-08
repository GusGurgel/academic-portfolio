#include <stdio.h>
#include <string.h>


int main()
{
	char phrase[100];//A frase que vai ser passa pelo usuário
	char toFind;//O caractere a ser procurado
	
	int findCount = 0;//Quantas vezes o caractere foi encontrado
	
	scanf("%[^\n]\n%c",phrase,&toFind);
	
	for(int i = 0; i < strlen(phrase); i++)
	{
		if(phrase[i] == toFind)
		{
			findCount++;
		}
	}
	
	printf("%d", findCount);
	
	return 0;
}


