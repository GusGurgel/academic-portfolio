#include <stdio.h>
#include <string.h>

//Remove uma char de uma string
void remv (char ch, char str[])
{
	for(int i = 0; i < strlen(str); i++)
	{
		if(str[i] == ch)
		{
			str[i] = ' ';
		}
	}
}

//Tudo é zero ????? 
int allZero(char str[], int *special)
{
	for(int i = 0; i < strlen(str); i++)
	{
		if( (str[i] != '0') && (str[i] != ' ') && (str[i] != '\n'))
		{
			if(i < strlen(str))
			{
				*special = i;
				return 75;
			}
			return 0;
		}
	}
	return 1;
}

int main()
{
	char str[100]; /*String passa pelo usuário*/
	char qTelca; /*tecla quebrada*/
	
	int allZ = 0; /*Tudo é zero ?*/
	
	int special = 0;
	
	scanf("%c\n%[^\n]", &qTelca, str);
	
	remv(qTelca, str);
	
	allZ = allZero(str, &special);
	
	if(allZ == 1 && allZ != 75)
	{
		printf("0");
		return 0;
	}
	
	for(int i = special; i < strlen(str); i++)
	{
		if(str[i] != ' ')
		{
			printf("%c", str[i]);
		}
	}
	
	return 0;
}

