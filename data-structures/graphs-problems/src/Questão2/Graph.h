/**************************************************
//
// Projeto Final - Estrutura de Dados Avançada UFC
//
// Graph (Header file)
//
// Criação:     01 Jul 2023
// Atualização: 01 Jul 2023
//
// Criado Por:
// Gustavo Gurgel Medeiros
// Número de Matrícula [UFC]: 539226
//
************************************************/

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdexcept>   // Exceções
#include <iostream>    // cout
#include <stack>	   // Simulação de recursão
#include <list>        // Adjacências
#include <iomanip>	   // Manipulação de entrada e saida
#include <cmath>       // Módulo
#include <utility>	   // Pair 
#include <queue>	   // Fila para busca em largura

#include "HashTable.h" // Tabela de listas de adjacência
#include "AvlTree.h"   // Lista ordenada com os vértices

//------ { Typedefs and Usings} -----
typedef unsigned int uint;
using std::string;
using std::list;
using std::cout;
using std::endl;
using std::stack;
using std::pair;
using std::queue;
using std::make_pair;
//-----------------------------------

//Estrutura que representa uma ator
struct Actor
{
	string name; 
	string film;
};


//DELETAR DEPOIS DELETAR DEPOIS DELETAR DEPOIS DELETAR DEPOIS
void makeLine(){
	for(int i = 0; i < 40; i++){
		cout << "-";
	}
	cout << endl;
}

//-------{ Class Graph }-------
// Classe simples que represen-
// ta um grafo NÃO DIRECIONADO
// usando listas de adjacencias.
//
// !IMPORTATE!
// Essa classe foi modificada
// para funcionar com strings
// em vez de inteiros. Assim,
// usando uma HashTable como
// lista de adjacência
//-----------------------------
class Graph{
private: 
	uint _E; 	            			  //Número de arestas
	uint _V;							  //Número de vértices
	
	HashTable<string, list<Actor>> _adj;  //Lista de adjacências
	AvlTree<string> _VTree; 		      //Ávore com os vértices ; Nome + Filme

	//Adiciona apenas a aresta u->v.
	//Por isso leva o nome half, pois
	//não uma inserção completa de
	//um grafo não direcionado
	void halfInsert(Actor u, Actor v){
		//O grafo ainda não possuí o vértice u
		if(!_adj.hasKey(u.name)){
			//Lista é criada
			_adj.add(u.name, list<Actor> {v});
			//Vértice é adicionado a árvore de vértices
			_VTree.add(u.name);
			_V++;
		}
		//O grafo já tem o vértice u
		else{
			//Aresta é adicionada na lista de adj
			_adj.at(u.name).push_back(v);
		}
	}

	

public:

//********************************
//  Construtores e Destrutores
//********************************
	
	//Construtor padrão
	Graph() = default;

	~Graph(){

	}

//************************
//    Métodos Públicos
//************************

	//Adicina uma aresta de forma completa
	void insert(Actor u, Actor v){
		halfInsert(u, v);
		halfInsert(v, u);
		_E++; //Aresta adicionada
	}

	//Printa a lista de adjacências
	void print(){
		vector<string> Vs;

		_VTree.inoderVec(Vs);
		
		for(string u : Vs){
			makeLine();

			cout << "[" << u << "]";

			list<Actor>& adj = _adj.at(u);

			cout << endl;

			for(Actor v : adj){
				cout << " -> {NOME: " << v.name << " / " << "FILME: " << v.film << "}";
				cout << endl;
			}

			cout << endl;
		}

		cout << "Número de vértices = " << _V << endl;
		cout << "Número de arestas = " << _E << endl;
	}

	//------------{ getBaconTable }------------
	// Essa é a função pricipal do problema 2.
	// Utilizando busca por lagura,essa função
	// Modifica uma HashTable ligando um nome
	// de uma ator a um pair composto por
	// seu número de bacon e o filme fez essa 
	// ator receber esse número de bacon.
	//-----------------------------------------
	void getBaconTable(HashTable<string,pair<uint,string>>& ref_table){
		HashTable<string, char> colors(_V); // w = branco; g = cinza; b = preto
		vector<string> V;			        // vetor de vértices 
		queue<string> Q;				    // fila de exploração

		_VTree.inoderVec(V);                // pega todos os vértices

		//Toda os vértices ficam brancos
		for(string str : V){
			colors.add(str, 'w');
		}

		//A origem da nossa busca é o Kevin Bacon
		Q.push("Kevin Bacon");
		//Kevin Bacon tem número de bacon = 0
		ref_table.add("Kevin Bacon", make_pair(0, ""));

		while(!Q.empty()){
			string u = Q.front();
			Q.pop();

			// Exploramos todos os vértices adjacentes
			for(Actor& ac : _adj.at(u)){
				//Vertice não explorado
				if(colors.at(ac.name) == 'w'){
					//pintamos ele de cinza
					colors.add(ac.name, 'g');
					//Adicionamos seu número de bacon e o filme
					//Lembrando que:
					//Número de banco = (número de bacon origem) + 1
					ref_table.add(ac.name, make_pair(ref_table.at(u).first+1, ac.film));
					//Adicinamos vértice na fila
					Q.push(ac.name);
				}
			}

			//se chegou aqui é porque terminaos
			//de explorar u. Então pintar de preto
			colors.add(u, 'b');
		}
	}

//************************
//  Getters and Setters
//************************

	//Retorna uma lista com todos os vértices
	void getVecV(vector<string>& ref){
		ref.clear();
		_VTree.inoderVec(ref);
	}

	//Retorna o número de vértices
	//
	//        Número de vértices
	//                 =
	//  Quantidade delementos na HashTable
	//
	uint getV(){
		return _V;
	}

	//Retonra o número de arestas 
	uint getE(){
		return _E;
	}
};

#endif
