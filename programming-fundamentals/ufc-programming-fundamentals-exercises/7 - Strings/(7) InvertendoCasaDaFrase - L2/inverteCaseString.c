#include <stdio.h>
#include <string.h>

char acordaPedrinho(char c)
{
	int a_to_A_Length = 'a' - 'A';
	
	if(c == 'z')
	{
		return 'Z';
	}
	
	//Maísculo
	if(c >= 'A' && c < 'a')
	{
		return c + a_to_A_Length;
	}
	//Minúculo
	if(c >= 'a' && c < (char)('a' + 23))
	{
		return c - a_to_A_Length;
	}
	//Nenhum do dois
	else
	{
		return c;
	}
}


int main()
{
	char phrase[100];//A frase que vai ser passa pelo usuário
	
	scanf("%[^\n]",phrase);
	
	for(int i = 0; i < strlen(phrase); i++)
	{
		printf("%c" , acordaPedrinho(phrase[i]));
	}
}


