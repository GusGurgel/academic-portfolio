/*
 * -------------Objetivo--------------
 * 
 *   Calcular a frequência de valores
 * 	 em um intervalo de classes
 * 
 * -----------------------------------
 */

#include <iostream>
#include <math.h>
#include <vector>
#include <sstream>

using namespace std;

void makeLine(int n = 25){
	for(int i {0}; i < n; i++)
		cout << "-";
	cout << endl;
}

struct freque 	 /*Estrutura de uma frequência*/ {
	float min;   //Valor Mínimo da classe
	float max;   //Valor Máximo da classe
	float med;   //Ponto média da classe
	
	int   freq;  //Frequência
};

int main()
{
	int   num; 				//Número de classes
	int   amp; 				//Amplitude de classe
	int   tempI;    		//Int temporária
	int   vals_size {0};	//Quantidade de valores
	
	float min; 				//Valor mínimo das classes
	float max; 				//Valor máximo das classes
	
	string line;			//Valores em uma linha
	
	stringstream ss; 		//Stringstream de valores
	
	vector<freque> arrF;  	// Array de frequências
	
	cout << "One line values: ";
	getline(cin, line);
	ss << line;
	cout << "Number of classes: ";
	cin >> num;
	cout << "Class min: ";
	cin >> min;
	cout << "Class max: ";
	cin >> max;
	
	amp = ceil((max - min)/num);
	
	//Construção dos máximos e minimos das classes
	for(int i {0}; i < num; i++){
		freque f {min, (min + amp - 1), 0, 0};
		f.med = (f.min+f.max)/2;
		min += amp;
		arrF.push_back(f);
	}
	
	//Distribuição de frequência
	while(ss >> tempI){
		for(int i {0}; i < num; i++){
			if(tempI <= arrF[i].max && tempI >= arrF[i].min){
				arrF[i].freq++;
				vals_size++;
				break;
			}
		}
	}
	
	tempI = 1; //Utilizado como index
	makeLine();
	//Debugação das classes com suas devidas frequêcias distribuidas
	for(freque f : arrF){
		cout << tempI << ": " << f.min << " - " << f.max << " (" << f.med << ")" << " = "
		 << f.freq << " (" << ((float)f.freq/vals_size*100) << "%)" << endl;
		tempI++;
	}
	makeLine();
}
