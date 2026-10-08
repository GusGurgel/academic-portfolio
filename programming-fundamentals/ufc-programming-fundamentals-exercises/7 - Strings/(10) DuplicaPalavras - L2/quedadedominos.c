#include <stdio.h>
#include <string.h>

/*Escreve uma string entre dois pontos*/
void writeBetween(int start, int end, char cArray[])
{
	for(int i = start; i < end; i++)
	{
		printf("%c",cArray[i]);
	}
}

int main()
{
	char stringInp[100];//String de entrada
	int start = 0;//Começo da repetição
	
	scanf("%[^\n]", stringInp);
	
	for(int i = 0; i < (strlen(stringInp)+ 1); i++)
	{
		if(stringInp[i] == ' ' || stringInp[i] == '\0')
		{
			writeBetween(start, i, stringInp);
			if(start == 0) { printf(" "); }
			writeBetween(start, i, stringInp);
			start = i;
		}
	}
}

