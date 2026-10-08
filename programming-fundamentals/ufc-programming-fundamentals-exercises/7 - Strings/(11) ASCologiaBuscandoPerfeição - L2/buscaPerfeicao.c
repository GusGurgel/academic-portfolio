#include <stdio.h>
#include <string.h>

/*retorna o "poder ASCII" da palavra*/
int ascVal(char c[])
{
	int sum = 0;/*vai recerber a soma de todos os valores ASCII*/
	
	for(int i = 0; i < strlen(c); i++)
	{
		sum += c[i];
	}
	
	return sum%50;
}

int main()
{
	char name[30]; /*Nome digitado para usuário*/
	
	int sLength = 0; /*Variável para salvar o tamanho do nome*/
	
	scanf("%[^\n]", name);

	sLength = strlen(name);
	
	for(int i = 'a'; i < ('z'+1); i++)
	{
		name[sLength] = i;
		name[sLength+1] = '\0';
		
		if(ascVal(name) == 0)
		{
			printf("%c", i);
			return 0;
		}
	}
	
	printf("sem sorte");
	
	return 0;
}
