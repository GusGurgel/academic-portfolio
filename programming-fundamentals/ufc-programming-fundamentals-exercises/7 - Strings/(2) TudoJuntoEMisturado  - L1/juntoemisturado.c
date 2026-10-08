#include <stdio.h>
#include <string.h>


int main()
{
	char word[100];
	
	scanf("%[^\n]", word);
	
	for(int i = 0; i < strlen(word); i++)
	{
		if(word[i] == '#' || word[i] == ';')
		{
			printf("\n");
		}else
		{
			printf("%c", word[i]);
		}

	}
	
	return 0;
}


