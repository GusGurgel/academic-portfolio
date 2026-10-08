#include <stdio.h>
#include <string.h>


int main()
{
	char phrase[100]; /*Frase digitada pelo usuário*/
	char toFind[100]; /*O que vai ser buscado*/
	
	int count = 0; /*Vai contar o número de char iguais
	entre pharse e to Find*/
	int nFinded = 0; /*Número de encontrados*/
	
	scanf("%[^\n]\n%[^\n]", phrase, toFind);
	
	
	for(int i = 0; i < strlen(phrase); i++)
	{
		for(int y = 0; y < strlen(toFind); y++)
		{
			if(phrase[i + y] == toFind[y])
			{
				count++;
			}
			else
			{
				break;	
			}
		}
		if(count == strlen(toFind))
		{
			nFinded++; 
		}
		count = 0;
	}
	
	printf("%d", nFinded);
	
	return 0;
}
