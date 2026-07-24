/**************************************************
//
// Projeto Final - Estrutura de Dados Avançada UFC
//
// Main (Implementation file)
//
// Criação:     01 Jul 2023
// Atualização: 01 Jul 2023
//
// Criado Por:
// Gustavo Gurgel Medeiros
// Número de Matrícula [UFC]: 539226
//
************************************************/

#include <iostream>  //Entrada e saida
#include <fstream>   //Leitura de arquivos
#include <stdexcept> // Exceções
#include <regex>     // Expressões regulares
#include <sstream>   // stringstream

#include "Graph.h"   //Representação de grafos

using namespace std;

//-------{ readFromFile }-------
// Lé todos os atores de uma arquivo
// e cria grafo com a relação dos atores 
// e seus filmes
//
// path = "endereço do arquivo"
// vec  = "vetor de referência"
//------------------------------------
void readFromFile(string path, Graph& G);

int main(){
	HashTable<string, pair<uint, string>> baconTable; //HashTable dos números de bacon
	vector<string> actorsNames; //Nome de todos os atores em ordem alfabética
	Graph G; //Grafo de Atores

	readFromFile("input.txt", G);
	G.getVecV(actorsNames);
	G.getBaconTable(baconTable);

	cout << endl;

	for(string& name : actorsNames){
		//Par com o número de bacon e filme do ator
		pair<uint, string>& actorInfo = baconTable.at(name);
		uint baconNumber = actorInfo.first;
		string film = actorInfo.second;

		cout << "O numero de Bacon de " << name << " é " << baconNumber;
		cout << " pelo filme " << film;
		cout << endl;
	}

	return 0;
}

void readFromFile(string path, Graph& G){
	const regex regexActors("(.*?);(.*?);(.*?\n|$)"); //regex para ler Atores
	smatch regexMatch; //recebe os resulados do regex
	ifstream in_stream; //stream de leitura
	stringstream ss;    //stringstream
	string file_str;    //arquivo lido

	in_stream.open(path);

	if(!in_stream.is_open()){
		throw invalid_argument("Arquivo não encontrado: " + path);
	}


	ss << in_stream.rdbuf();
	file_str = ss.str();

	while(regex_search(file_str, regexMatch, regexActors)){
		string name1 = regexMatch.str(1);
		string name2 = regexMatch.str(3);
		string film  = regexMatch.str(2);
		
		name2 = name2.substr(0, name2.size()-1); // tirar o \n


		Actor actor1 = Actor{ name1, film};
		Actor actor2 = Actor{ name2, film};

		G.insert(actor1, actor2);

		file_str = regexMatch.suffix().str();
	}
}