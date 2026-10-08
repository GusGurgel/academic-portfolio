/*
 * -------------Objetivo--------------
 * 
 *   Calcular intervalos de classe
 * 
 * -----------------------------------
 */

#include <iostream>
#include <math.h>

using namespace std;

void makeLine(int n = 20){
	for(int i {0}; i < n; i++)
		cout << "-";
	cout << endl;
}

int main()
{
	int   num; //Número de classes
	int   amp; //Amplitude de classe
	float min; //Valor mínimo das classes
	float max; //Valor máximo das classes
	
	cout << "Number of classes: ";
	cin >> num;
	cout << "Class min: ";
	cin >> min;
	cout << "Class max: ";
	cin >> max;

	amp = ceil((max - min)/num);
	
	makeLine();
	for(int i {1}; i <= num; i++){
		cout << i << ": ";
		cout << min << " - ";
		min += amp;
		cout << min-1 << endl;
	}
	makeLine();
}
