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

#include <stdexcept> // Exceções
#include <iostream>  // cout
#include <vector>    // Lista de adjacências
#include <stack>	 // Simulação de recursão
#include <list>      // Adjacências
#include <iomanip>	 // Manipulação de entrada e saida
#include <cmath>      // Módulo

//------ { Typedefs and Usings} -----
typedef unsigned int uint;
using std::vector;
using std::list;
using std::cout;
using std::endl;
using std::stack;
//-----------------------------------

//-------{ Class Graph }-------
// Classe simples que represen-
// ta um grafo NÃO DIRECIONADO
// usando listas de adjacencias.
//-----------------------------
class Graph{
private: 
	uint _V; 	             //Número de vértices
	uint _E; 	             //Número de arestas
	vector<list<uint>> _adj;     //lista de adjacências

public:

//************************
//      Construtores 
//************************
	
	//Construtor por número de vértices
	Graph(uint V){
		this->_V = V;
		_adj.resize(V); //Reserva vetor de adjacências
	}

//************************
//    Métodos Públicos
//************************

	//Redefine quantidade de vértice do
	//Grafo e limpa seus elementos
	void reset(uint E){
		_V = 0;
		_E = E;
		_adj.clear();
		_adj.resize(E);
	}

	//Adicina uma aresta
	void insert(uint u, uint v){
		//Valor invalido de vértices
		if(u < 0 || v < 0 || u >= _V || v >= _V){
			throw std::invalid_argument("Valores de inserção de arresta invalidos:  (" + std::to_string(u) + "," + std::to_string(v) + ")\n");
		}

		//Adiciona as arestas		
		_adj[u].push_back(v);
		_adj[v].push_back(u);

		//Incrementa quantiade arestas.
		_E++;
	}

	//Printa a lista de adjacências
	void print(){
		for(int i = 0; i < _V; i++){
			list<uint>& curr = _adj[i];

			cout << std::setw(5) << std::left << "[" + std::to_string(i) + "] "  ;

			if(curr.empty()){
				cout << " -> NIL";
			}

			for(uint n : curr){
				cout << " -> " << n;
			}

			cout << endl;
		}
	}

	// -----------------{canBeColored}--------------
	// > Função que retorna se existir uma coloração 
	// > de vértices válida do grafo com duas cores.
	// >
	// > Em outra palavras, a função utiliza a busca
	// > em profundidade para encontra cíclos de tamanho
	// > impar. Se ao menos um ciclo de tamanho impar
	// > for encontrado, então o grafo não pode ser
	// > bipartido, por tanto não pode ser colorido
	// > com duas cores. Caso o contrário, existe uma 
	// > coloração válida.
	// ----------------------------------------------
	bool canBeColored(){
		//Error, grafo vazio
		if(_V <= 0){
			throw std::underflow_error("Função canBeColored() chado em um grafo vazio");
		}

		stack<uint> st;  //Stack de exploração
		char colors[_V]; //vetor de cores, w = branco, g = cinza, b = preto
		int dists[_V];   //vetor de distâncias

		//Inicializamos os vetores do cores e distâncias
		for(int i = 0; i < _V; i++){
			colors[i] = 'w';
			dists[i]  = 0;
		}

		//Procuramos uma origem
		for(int i = 0; i < _V; i++){
			//Origem encontrada.
			if(colors[i] == 'w'){
				st.push(i);	//Colocamos a origem na stack

				//Inicia-se a exploração da origem
				while(!st.empty()){
					//Flag para dizer se um vértice
					//adjacente branco foi encontrado
					bool adjFound = false;  
					uint u = st.top(); //Vértice de origem é tirado da pilha

					colors[u] = 'g'; //Descobrimos o vértice

					//Procuramos um vétice adjacente não descoberto
					//para colocar na pilha
					for(uint v : _adj[u]){
						//Vértice adjacente não explorado encontrado
						if(colors[v] == 'w'){
							adjFound = true;		//Um valor adj foi encontrado
							dists[v] = dists[u]+1;	//A distância de v a u é igual a (u+1)
							st.push(v); 			//Empilha-mos a nova origem
							break;					//Saimos do loop
						//!!!possível ciclo encontrado
						}else if(colors[v] == 'g'){
							//Tamanho do cíclo é dado pela distâcia absoluta 
							//de u até v, +1 da aresta que fecha o ciclo.
							uint cLen = std::abs(dists[u] - dists[v]) + 1; 
							//Ciclo de tamanho ímpar encontrado
							//logo a coloração não é possível
							if(cLen > 2 && cLen % 2 == 1){
								return false;
							}
						}
					}
					
					//explorado for encontrado, então sua
					//exploração acabou. Dessa forma ele
					//removido na stack e será pintado
					//de preto.
					if(adjFound == false){
						colors[u] = 'b';
						st.pop();
					}
				}
			}
		}

		//Debug que todos os vértices estão pretos

		//Se a função chegou aqui, então é porque não
		//existem ciclos de tamanho impar. Logo a colo-
		//ração é possível
		return true;
	}

//************************
//  Getters and Setters
//************************

	//Retorna o número de vértices
	uint getV(){
		return this->_V;
	}

	//Retonra o número de arestas
	uint getE(){
		return this->_E;
	}
};

#endif
