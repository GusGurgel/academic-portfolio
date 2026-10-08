#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdexcept>
#include <experimental/filesystem>
#include <sstream>
#include <fstream>

#include "Midia.h"
#include "CD.h"
#include "DVD.h"

namespace fs = std::experimental::filesystem;

using std::stringstream;
using std::ofstream;
using std::ifstream;
using std::runtime_error;


enum fileType { T_MIDIA = 0, T_CD = 1, T_DVD = 2};

//retorna se uma pasta existe
bool folderExist(const string&);

//retorna um vetor com o endereço de todos os arquivos em um pasta
//com um extenção específica
vector<string>* getAllArquives(const string&, const string& = ".txt");

//Transforma um verto de strings em uma string de uma linha só
string oneLineVec(vector<string>*);

//Transforma uma data em string
string toStringData(const Data&);

//Tranforma uma string em um vetor de strings
vector<string>* oneVecByLine(const string&);

//Retorna o tipo de uma midia
fileType getFileType(Midia*&);

//Retorna o tipo de uma midia em string
string TypeStr(Midia*);

//Representa um arquivo de salvamento do programa
class MidiaFile{
public:
	fileType m_type { fileType::T_MIDIA }; //Representa o tipo do arquivo, se é CD ou DVD
	string   m_path;					   //Caminho atrelado ao arquivo
	Midia*   m_midia {nullptr};			   //Ponterio para midia atrealada ao arquivo
	
	void openMidia(Midia*, ifstream&);  //Método auxiliar para leitura de arquivo
	
public:
	//Cria uma MidiaFile atraves de um arquivo de texto no disco
	MidiaFile(const string&);
	
	//Cria uma MidiaFile atraves de uma Mídia em memoria ram
	MidiaFile(Midia*);
	
	//O delete salva as informações mudadas
	~MidiaFile();
	
	//Salva a mídia em memória de disco
	void save();
	
	string getTypeStr();
	
	Midia* getMidia();
	
	string getPath();
	
	fileType getType();
};

#endif
