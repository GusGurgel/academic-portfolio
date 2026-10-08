#include <iostream>
#include <locale.h>

using namespace std;

int main() {
	system("chcp 65001 > nul");
	//~ setlocale(LC_ALL, "Portuguese_Brasil");
	cout << "Olá Mundo!!!" << endl 
	<< "Gurgelzão" << endl
	<< "Máriozão" << endl
	<< "Coração" << endl;
}
