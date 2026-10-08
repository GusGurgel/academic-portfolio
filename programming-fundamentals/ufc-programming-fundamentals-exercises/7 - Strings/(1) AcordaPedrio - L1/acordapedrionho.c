
#include <stdio.h>


char acordaPedrinho(char c)
{
	int a_to_A_Length = 'a' - 'A';
	
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


int main(){

	char c;
	scanf("%c", &c);
	printf("%c",acordaPedrinho(c));
	
	return 0;
}


