#include <stdio.h>
#include <string.h>

/* Procura um único caractere em um array de caracteres
 * se esse caractere for encontrado no array - retorna 1
 * se não for encontrado- retorna 0 */
int findCharInArray(char c, char toFind[])
{
	for(int i = 0; i < strlen(toFind); i++)
	{
		if(c == toFind[i])
		{
			return 1;
		}
	}
	return 0;
}

/* Retorna quantidade de elementos semelhantes entre dois array
 * char nifo[5] = {'n','i','f','o'}
 * char gustavo[8] = {'g','u','s','t','a','v','o'} 
 * charCount(nifo, gustavo) -> retorno = 1*/
int charCount(char arrayToSearch[], char charsToFind[])
{
	int ret = 0;
	
	for(int i = 0; i < strlen(arrayToSearch); i++)
	{
		if(findCharInArray(arrayToSearch[i], charsToFind))
		{
			ret++;
		}
	}
	return ret; 
}

int main()
{
	char myName[100];//Seu nome
	char crushName[100];//Nome do crush
	char vogais[11] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
	char myNameTerminaVogal; //Se myNameTermina ou não em vogal
	char crushNameTerminaVogal; //Se crushNameTerminaVogal ou não em vogal

	int points = 0;//Pontos do Crushômetro
	
	scanf("%[^\n]\n%[^\n]", myName, crushName);
	
	myNameTerminaVogal = findCharInArray(myName[strlen(myName)-1], vogais);
	crushNameTerminaVogal = findCharInArray(crushName[strlen(crushName)-1], vogais);
	
	//Primeira letra
	if(myName[0] == crushName[0])
	{
		points += 20;
	}
	
	//Mesmo tamanho
	if(strlen(myName) == strlen(crushName))
	{
		points += 30;
	}
	
	//Mesma quantidade de vogais
	if(charCount(myName, vogais) == charCount(crushName, vogais))
	{
		points += 30;
	}
	
	//Ambos terminam com vogal ou ambos terminam com consoante
	if(myNameTerminaVogal && crushNameTerminaVogal)
	{
		points += 20;
	}
	else if( (!myNameTerminaVogal) && (!crushNameTerminaVogal) )
	{
		points += 20;
	}
	else
	{
		if(points > 10)
		{
			points -= 10;
		}
	}
	
	printf("As chances do crush te dar bola sao: %d%%!", points);
	
	return 0;
}

