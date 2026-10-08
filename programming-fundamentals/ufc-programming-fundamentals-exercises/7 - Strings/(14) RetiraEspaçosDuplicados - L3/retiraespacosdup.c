#include <stdio.h>
#include <string.h>

int main()
{
	char str[100]; /*String passa pelo usuário*/
	
	int canPrint = 1; /*Posso printar ?*/
	
	scanf("%[^\n]", str); 
	
	for(int i = 0; i < strlen(str); i++)
	{
		if(str[i] == ' ' && canPrint)
		{
			printf("%c", str[i]);
			canPrint = 0;
		}
		else if(str[i] != ' ')
		{
			printf("%c", str[i]);
			canPrint = 1;
		}
		
	}
	
	return 0;
}

