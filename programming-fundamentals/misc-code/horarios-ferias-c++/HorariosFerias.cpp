#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>

using namespace std;

int main()
{	
	#ifdef _WIN32
		/*Utilização de caracteres com acentuação no windows*/
		system("chcp 65001 > nul"); 
	#endif
	
	string filename = "HorarioFerias.txt";
	string outfilename;
	string mediaHora;
	string desc;
	
	ifstream file;				/*Filestream de entrada*/
	ofstream file_out;			/*Filestream de saida*/

	stringstream ss;
	
	file.open(filename);
	
	/*Arquivo padrão não encontrado*/
	if(!file.is_open()){
		cout << "Digite o nome do arquivo: ";
		cin >> filename;
	
		file.open(filename);
	}
	
	outfilename = "out.txt";
	file_out.open(outfilename);
	
	if(file.is_open() && file_out.is_open()){
		while(file >> mediaHora && getline(file, desc)){
			ss << "\t\t\\gi{" << stof(mediaHora) << "}";
			ss << "{" << desc.substr(1) << "}" << endl;
		}
	}else{
		cout << "fail trying to open file" << endl;
		return EXIT_FAILURE;
	}
	
	file_out << ss.str();

	file_out.close();
	file.close();
	
	return EXIT_SUCCESS;
}
