/* ======Objetivo=========
 * Efetuar gagueira em uma
 * string
 * */
#include <iostream>
#include <cctype>
#include <sstream>

using namespace std;

//-----------------------------------------------------
//Declarações

//retorna se uma char eh uma vogal
bool ehVogal(char, const string /*vogais*/ = "aeiou");

//Retorna quantidade de subStrings
int cSubString(const string &);

//Retorna quantidade de silabas
int cSilabas(const string &);

//Retorna parte da string que deve ser repetida
string getRepPart(string &);

//Pega as substrings de um arr
string* getSub(string &, int &);

//Retorna string formatada com gagueira
string fGagueira(string* &, const int &);

//----------------------------------------------------

int main()
{
	string str { 0 }; //String de input
	int size   { 0 }; //Tamanho do array de substring
	getline(cin, str);
	
	//Alocação dinâmica de array de strings
	string * arrget = getSub(str, size);
	
	cout << fGagueira(arrget, size);
	
	//Desalocação dinâmica de array de strings
	delete [] arrget;
}

bool ehVogal(char c, string vogais)
{
	
	for(char v : vogais)
	{
		if(c == v || c == toupper(v))
			return true;
	}
	return false;
}

int cSubString(const string & str)
{
	int ret { 1 };
	for(char c : str)
	{
		if(isspace(c))
			ret++;
	}
	return ret;
}

string* getSub(string & str, int & size)
{
	int start { 0 };
	int strLenght = str.length();
	int nextIndex = 0;

	size = cSubString(str);
	string* ret = new string[size];
	
	for(int i = 0; i < strLenght; i++)
	{
		if(isspace(str[i]))
		{
			ret[nextIndex] = str.substr(start, (i - start));
			nextIndex++;
			start = i+1;
		}
		if(i > strLenght-2)
		{
			ret[nextIndex] = str.substr(start, (i+1 - start));
			nextIndex++;
			start = i+1;
		}
	}
	
	return ret;
}

int cSilabas(const string & str)
{
	int ret { 0 };
	int str_length = str.length();
	
	for(int i = 0; i < str_length; i++)
	{
		if(i > str_length-2)
			continue;
		if(ehVogal(str[i]) && !ehVogal(str[i+1]))
		{
			//cout << str[i] << "<- Vogal;Nao Vogal ->" << str[i+1] << endl;
			ret++;
			i++;
		}
		else if(!ehVogal(str[i]) && ehVogal(str[i+1]))
		{
			//cout << str[i] << "<- Nao Vogal;Vogal ->" << str[i+1] << endl;
			ret++;
			i++;
		}
	}
	return ret;
}

string getRepPart(string & str)
{
	int str_length = str.length();
	stringstream ret;
	if(ehVogal(str[0]))
	{
		ret << str[0];
		return ret.str();
	}
	ret << str[0];
	for(int i = 1; i < str_length; i++)
	{
		if(!ehVogal(str[i]) && ehVogal(str[i-1]) )
		{
			break;
		}
		ret << str[i];
	}
	return ret.str();
}

string fGagueira(string* & str, const int & size)
{
	stringstream ret; 
	for(int x { 0 } ; x < size; x++)
	{
		if(cSilabas(str[x]) > 1)
		{
			ret << getRepPart(str[x]);
			ret << getRepPart(str[x]);
			ret << str[x];
		}
		else
		{
			ret << str[x];
		}
		if(x < size-1)
		{
			ret << " ";
		}
	}
	return ret.str();
}
