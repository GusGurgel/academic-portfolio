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
#include <cmath>     // Módulo
#include <utility>	 // Pair
#include <algorithm> // sort

//------ { Typedefs and Usings} -----
typedef unsigned int uint;
using std::vector;
using std::list;
using std::cout;
using std::endl;
using std::stack;
using std::pair;
//-----------------------------------


//retorna aonde em que bucket um inteiro está
uint getBucket(const uint& n, const vector<vector<uint>>& ref){
	for(int i = 0; i < ref.size(); i++){
		for(int j = 0; j < ref[i].size(); j++){
			if(ref[i][j] == n){
				return i;
			}
		}
	}

	throw std::invalid_argument("Valor não está em nenhum buket");
}

bool element(const uint& e, const list<uint>& l){
	for(const uint& u : l){
		if(u == e){
			return true;
		}
	}

	return false;
}

//Temp
void makeline(){
	for(int i = 0; i < 40; i++){
		cout << '-';
	}
	cout << endl;
}

//-------{ Class Graph }-------
// Classe simples que represen-
// ta um grafo NÃO DIRECIONADO
// usando listas de adjacencias.
//-----------------------------
class Graph{
private: 
	uint _V; 	                 //Número de vértices
	uint _E; 	                 //Número de arestas
	bool _direc;			     //Diz se o grafo é o ou não direcionado
	vector<list<uint>> _adj;     //lista de adjacências

	//--------{malformedConvert}--------
	// > Essa função retorna uma repre-
	// > sentação do grafo não direci-
	// > nado que chamou em uma forma-
	// > direcionada. Porém, como o nome
	// > da função diz, de uma maneira
	// > mal fomada, com caminhos fal-
	// > tando.
	// >
	// > A função é privada pois para
	// > mim não faz sentido o usuário
	// > querer usar isso
	//---------------------------------
	Graph malformedConvert(){
		Graph ret(_V, true); //Grafo direcionado de retorno

		stack<uint> st;  //Stack de exploração
		char colors[_V]; //Vetor de cores : w = branco; g = cinza; b = preto
		int dists[_V];	 //Vetor de distâncias

		//Inicia vetor de cores e distâncias
		for(int i = 0; i < _V; i++){
			colors[i] = 'w';
			dists[i] = 0;
		}
		
		//Conversão utilizando busca em largura -> 


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

							//Nova ligação do vértice retorno
							ret.insert(u, v);

							break;					//Saimos do loop
						//!!!possível ciclo encontrado
						}else if(colors[v] == 'g'){
							//Tamanho do cíclo é dado pela distâcia absoluta 
							//de u até v, +1 da aresta que fecha o ciclo.
							uint cLen = std::abs(dists[u] - dists[v]) + 1; 
							//Ciclo maior de 2 achado, então fazer ligação
							if(cLen > 2){
								//Nova ligação do vértice retorno
								ret.insert(u, v);
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

		return ret;
	}

public:

	Graph temp(){
		return malformedConvert();
	}

//************************
//      Construtores 
//************************
	
	//Construtor por número de vértices
	Graph(uint V, bool direc = false){
		this->_direc = direc;
		this->_V = V;
		this->_E = 0;
		_adj.resize(V); //Reserva vetor de adjacências
	}

	/*
	//Construtor de copia
	Graph(Graph& ref){
		this->_V = ref._V;
		this->_E = ref._E;
		this->_adj = ref._adj;
		this->_direc = _direc;
	}
	*/
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
		if(!element(v, _adj[u])){
			_adj[u].push_back(v);
			//Incrementa quantiade arestas.
			_E++;
		}		
		//Adiciona aresta contrária apenas
		//se não for direcionado
		if(!_direc){
			if(!element(u, _adj[v])){
				_adj[v].push_back(u);
			}		
		}
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

	void printDirectedList(){
		if(_direc == false){
			throw std::invalid_argument("printDirectedList não funciona com grafos não direcionados");
		}
		vector<pair<uint,uint>> EVec;

		for(int i = 0; i < _V; i++){
			for(const uint& u : _adj[i]){
				EVec.push_back(std::make_pair(i, u));
			}
		}

		std::sort(EVec.begin(), EVec.end());

		for(const pair<uint,uint>& ref : EVec){
			cout << "(" << ref.first << "," << ref.second << ")" << endl;
		}
		cout << "#" << endl;
	}

	//--------{getTransversal}--------
	// > Retrona o grafo transposto
	// > do grafo chamado
	//---------------------------------
	Graph getTransversal(){
		if(this->_direc == false){
			throw std::invalid_argument("calculo de graph transposto com grafo não direcionado");
		}
		
		Graph ret(_V, true); //Grafo de retorno

		for(int i = 0; i < _V; i++){
			int u = i;

			//Vértices adjacentes a u
			for(uint v : _adj[i]){
				//se existe (u, v) então a existe (v, u) na transposta
				ret.insert(v, u);
			}
		}

		return ret;
	}

	//--------{getComponets}--------
	// > Retorna um vetor com as com-
	// > ponentes do grafo
	// > 
	// > usa o Kosaraju's Algorithm
	//---------------------------------
	vector<uint> getComponets(){
		if(_direc == false){
			throw std::invalid_argument("Buscando componetes de grafo não direcionado");
		}

		Graph transv = getTransversal(); //Grafo transversal

		uint ret[_V];            //vetor com as componentes
		uint i_ret = 0;           //índice do vetor de retorno

		stack<uint> st_aux;       //stack auxilar

		stack<uint> st;           //Stack de exploração
		char colors[_V];          //Vetor de cores : w = branco; g = cinza; b = preto

		//Inicia vetor de cores
		for(int i = 0; i < _V; i++){
			colors[i] = 'w';
		}

		//Criando stack auxilar com os elmentos
		//na order inversa de descobrimento
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
							st.push(v); 			//Empilha-mos a nova origem
							break;					//Saimos do loop
						}
					}
					
					//Jogamos valor u na stack auxilar
					//para guardar valores na order
					//decresente de finalização
					if(adjFound == false){
						colors[u] = 'b';
						st_aux.push(u);
						st.pop();
					}
				}
			}
		}

		//Inicia vetor de cores
		for(int i = 0; i < _V; i++){
			colors[i] = 'w';
		}

		//Faz busca com o grafo transversal
		//e na ordem inversa de finalização
		while(!st_aux.empty()){
			uint i = st_aux.top();

			if(colors[i] == 'w'){

				st.push(i);	//Colocamos a origem na stack

				//Inicia-se a exploração da origem
				while(!st.empty()){
					//Flag para dizer se um vértice
					//adjacente branco foi encontrado
					bool adjFound = false;  
					uint u = st.top();       //Vértice de origem é tirado da pilha

					colors[u] = 'g'; //Descobrimos o vértice

					for(uint v : transv._adj[u]){
						//Vértice adjacente não explorado encontrado
						if(colors[v] == 'w'){
							adjFound = true;		//Um valor adj foi encontrado
							st.push(v); 			//Empilha-mos a nova origem
							break;					//Saimos do loop
						}
					}

					//Jogamos valor u na stack auxilar
					//para guardar valores na order
					//decresente de finalização
					if(adjFound == false){
						colors[u] = 'b';
						ret[u] = i_ret; //componente é adicinada
						st.pop();
					}
				}
				i_ret++;
			}

			st_aux.pop();
		}

		vector<uint> _ret;

		for(int i = 0; i < _V; i++){
			_ret.push_back(ret[i]);
		}

		return _ret;
	}

	
	Graph convertInDirected(){
		if(_direc == true){
			throw std::invalid_argument("tentando converter vertice não direcionado com um vértice direcionado");
		}

		Graph ret = malformedConvert();				  //grafo mal formado
		vector<uint> components = ret.getComponets(); //componentes do grafo mal formado

		stack<uint> st;           //Stack de exploração
		char colors[_V];          //Vetor de cores : w = branco; g = cinza; b = preto

		//Inicia vetor de cores
		for(int i = 0; i < _V; i++){
			colors[i] = 'w';
		}

		//Criando stack auxilar com os elmentos
		//na order inversa de descobrimento
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
							st.push(v); 			//Empilha-mos a nova origem

							//conexção de componentes
							//consertar caminho
							if(components[u] != components[v]){
								ret.insert(v, u);
							}

							break;					//Saimos do loop
						}
					}
					
					//Jogamos valor u na stack auxilar
					//para guardar valores na order
					//decresente de finalização
					if(adjFound == false){
						colors[u] = 'b';
						st.pop();
					}
				}
			}
		}

		return ret;
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
