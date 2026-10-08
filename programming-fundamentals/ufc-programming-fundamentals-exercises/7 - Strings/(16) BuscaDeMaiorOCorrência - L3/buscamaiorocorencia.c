#include <stdio.h>
#include <string.h>

/*retorna o a letra maíuscula*/
char upper(char c)
{
	if( ((c >= 'a' ) && (c <= 'z')) )
	{
		return c - ('a' - 'A');
	}
	else
	{
		return c;
	}
	
}

/*Retorna se um caractére esta dentro
 *de uma coleção*/
int isIn(char c, char search[])
{
	for(int i = 0; i < strlen(search); i++)
	{
		if(c == search[i] || c == upper(search[i]) )
		{
			return 1;
		}
	}
	return 0;
}

/*Remove uma coleção de caractéres de uma
 *string
 * */
void removeCharCol(char str[], char toRemove[])
{
	for(int i = 0; i < strlen(str); i++)
	{
		if(! (isIn(str[i], toRemove)) )
		{
			str[i] = ' ';
		}
	}
}

/*Print específico para essa questão*/
void marioPrint(int start, int end, char str[])
{
	if( (end - start) == 1)
	{
		printf("%c", str[ (end - start) ]);
	}
	else
	{
		for(int i = start; i < end; i++)
		{
			printf("%c", str[i]);
		}
	}
}

void giveWinners(int *startWinner, int*endWinner, char str[], char vogais[])
{
	int testing = 0;
	int start = 0;
	int end = 0;
	
	for(int i = 0; i < strlen(str)+1; i++)
	{
		if( (!testing) && isIn(str[i],vogais))
		{
			start = i;
			testing = 1;
		}
		
		if(testing && isIn(str[i],vogais))
		{
			end = i;
		}
		
		if(testing && (!isIn(str[i],vogais)))
		{
			end = i;
			
			//printf("Parei com o end:%d e o start:%d\n", end, start);
			
			if( (end - start) > (*endWinner - *startWinner) )
			{
				*startWinner = start;
				*endWinner = end;
			}
			testing = 0;
		}
	}
}


int main()
{
	char str[100]; /*string de input*/ 
	char vogais[6] = {'a', 'e', 'i', 'o', 'u'}; 
	
	int startWin = 0; /*Começo da sequência de vogais ganhadora*/
	int endWin = 0; /*Final da sequência de vogais ganhadora*/
	int cases = 0;/*Quantidade de casos de teste*/
	
	scanf("%d", &cases);

	for(int i = 0; i < cases; i++)
	{
		scanf("%s", str);
		
		removeCharCol(str, vogais);
		
		giveWinners(&startWin, &endWin, str, vogais);
		
		marioPrint(startWin, endWin, str);
		
		startWin = 0;
		endWin = 0;
		
		printf("\n");
	}
	
	return 0;
}

