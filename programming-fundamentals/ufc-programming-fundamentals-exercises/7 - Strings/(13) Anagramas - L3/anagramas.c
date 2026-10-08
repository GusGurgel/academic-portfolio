#include <stdio.h>
#include <string.h>

int findRemove(char find, char search[])
{
	for(int i = 0; i < strlen(search); i++)
	{
		if(search[i] == find)
		{
			search[i] = ' '; 
			return 1;
		}
	}
	return 0; 
}

int main()
{
	char name1[100];
	char name2[100];

	int same = 0;
	
	scanf("%[^\n]\n%[^\n]", name1, name2);
	
	for(int i = 0; i < strlen(name1); i++)
	{
		if(strlen(name1) > strlen(name2) || strlen(name1) < strlen(name2))
		{
			break;
		}
		if(!(findRemove(name1[i], name2)))
		{
			break;
		}
		same++;
		if(same >= (int)strlen(name1))
		{
			printf("sim");
			return 0;
		}
	}
	
	printf("nao");
	
	return 0;
}


