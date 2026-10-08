/*
-------------Objetivo--------------
Fazer um programa que utiliza a
biblioteca fstream para criar
uma arquivo TXT com uma lista 
de pessoas passadas pelo usuário.
-----------------------------------
 */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
	//Utilização de assentos no Windows
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		system("chcp 65001 > nul"); /*Muda tabela de caracteres do terminal*/
	#endif 

	vector<string> lista_pessoas;
	string input_pessoa;
	ofstream file;
	int index { 0 };
	cout << "Digite a lista de pessoas: " << endl;
	while(getline(cin, input_pessoa)){
		if(input_pessoa == "\0")
			break;
		cout << "{" << input_pessoa << "}" << endl;
		lista_pessoas.push_back(input_pessoa);
	}
	file.open("lista.txt");
	file << "Última lista de pessoa registradas: " << endl;
	for(string element : lista_pessoas){
		file << "{" << ++index << "} " << element << endl; 
	}
	file.close();
	return 0;
}
