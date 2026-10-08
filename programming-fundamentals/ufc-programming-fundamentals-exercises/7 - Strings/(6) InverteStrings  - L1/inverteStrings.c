#include <stdio.h>
#include <string.h>


int main()
{
	char phrase[100];//A frase que vai ser passa pelo usuário
	int pharseLength = 0;//Tamanho da frase
	
	scanf("%[^\n]",phrase);
	
	pharseLength = strlen(phrase);
	
	for(int i = 0; i < pharseLength; i++)
	{
		printf("%c" , phrase[ (pharseLength - i - 1)]);
	}
}


