#include <stdio.h>
#include <string.h>

int main()
{
	char phrase[50];//A frase que vai ser passa pelo usuário
	char vogais[5] = {'a','e','i','o','u'}; //As vogais do alfabeto
	int a_to_A_Length = 'a' - 'A';//Distância de a até A
	
	scanf("%[^\n]",phrase);
	
	for(int i = 0; i < strlen(phrase); i++)
	{
		for(int y = 0; y < 5; y++)
		{
			if(phrase[i] == ' ')
			{
				printf(" ");
				break;
			}
			if(phrase[i] == vogais[y] || phrase[i] == (vogais[y]-a_to_A_Length))
			{
				printf("v");
				break;
			}
			if(y == 4)
			{
				printf("c");
			}
		}
	}
}


