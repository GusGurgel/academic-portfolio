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

#include "Graph.h"   //Representação de grafos

using namespace std;

// --------------{graphsFromFile}------------
// > Lé um grafo de um arquivo de texto
// > 
// > path = "endereço do arquivo"
// > vec  = "referência para vetor de grafos"
// ------------------------------------------
void graphsFromFile(string path, vector<Graph>& vec);

int main(){
	vector<Graph> graphs;
	uint caso = 1;


	graphsFromFile("grafos.txt", graphs);

	for(int i = 0; i < graphs.size(); i++){
		cout << caso << endl;
		graphs[i].convertInDirected().printDirectedList();
		caso++;
	}
	
	return 0;
}

void graphsFromFile(string path, vector<Graph>& vec){
	ifstream in_stream; //Stream de leitura
	int V, E; //Número de vértices, Número de arestas
	int u, v; //Origem, destino

	in_stream.open(path);

	//Confima se o arquivo foi aberto com sucesso
	if(!in_stream.is_open()){
		throw invalid_argument("Falha ao abir o arquivo: " + path);
	}

	while(in_stream >> V && in_stream >> E){
		Graph G(V);

		for(int i = 0; i < E; i++){
			in_stream >> u;
			in_stream >> v;
			G.insert(u, v);
		}

		vec.push_back(G);
	}

	in_stream.close();
}