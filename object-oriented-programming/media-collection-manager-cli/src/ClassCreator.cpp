#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>
#include <sstream>
#include <iterator>

using namespace std;

//Struct que representa um atributo de uma classe
struct attribute{
	string type;
	string name;
};

//Struct que representa um método
struct method{
	string ret;
	string name;
	vector<attribute> params;
	bool isConst;
};

//Struct relativa as configuração da classe, como includes
//, nome da classe...
struct classConfs{
	string className;
	vector<string> 	  includes;
	vector<attribute> attributes;
	vector<method>	  methods;
};

//Esse função cria um header file baseado em um classConfs
void createHeader(const classConfs&, ofstream&, string);

//Cria a implementação de uma classe usando um classConfs
//como base
void createImplementation(const classConfs&, ofstream&, string);

//Cria as funções de encapsulamento de um atributo
void addGetAndSet(const attribute&, ofstream&, const string&,bool isPrototype = true);

//Usa uma array de method para cirar o protótipo e implementação das funções
void addMethods(const vector<method>&, ofstream&, const string& ,bool isPrototype = true);

//Cria um vetor de strings baseado em uma linha
vector<string> getByLine(const string&);

//Pega uma linha espesífica de um arquivo
string getLineByIndex(int, ifstream&);

//Função que pega os atributos tendo como referência uma string de linha
vector<attribute> getAtributesByLine(const string&);

//Função que pegas os atributos em um vetor de linhas
vector<method> getMethodsByLines(const vector<string>&);

//Função que cria uma classe baseada em um arquivo
string makeClass(string filename);

//Cria um modelo de classe
void makeModel(string);

//Retorna a string com todas sua chars em maiúsculo
string stringUpper(const string&);

//Seta uma parte extra de um tipo.
//
//Exemplo 1: se o tipo é *int, então essa função
//vai mudar para const int.
//Exemplo 2: se o tipoe é _int, então essa função
//vai mudar para int&
void setExtra(string&);

int main(){
	while(true){
		string linha, comando;
		getline(cin, linha);
		stringstream lineStream {linha};
		lineStream >> comando;
		if(comando == "create"){
			string filename;
			lineStream >> filename;
			cout << "Classe { " << makeClass(filename) << " } criada com exito" << endl;
		}else if(comando == "exit"){
			cout << "Exiting...";
			exit(EXIT_SUCCESS);
		}else if(comando == "model"){
			string className;
			lineStream >> className;
			makeModel(className);
			cout << "Modelo { " << className << " } criado com exito " << endl;
		}
		else{
			cout << "comando inexistente" << endl;
		}
	}
}

string makeClass(string filename)
{
	ifstream in_file;   			//In file buffer
	ofstream out_file;  			//Out file buffer
	
	string   className; 			//O Nome da classe
	string   includeLine;			//Linha que representa os include da classe
	string   atributesLine;			//Linha que representa os atributos da classe
	string 	 fileNameToCreate{""};	//O nome do arquivo a ser criado
	
	
	vector<string> methodsLines; 	//Linhas que representam os métodos
	
	classConfs _classConfs;			//Struct com as configurações da classe
	
	//Abre o arquivo (O programa termina se o arquivo não existir)
	in_file.open(filename);
	if(!in_file.is_open()){
		cout << "file " << filename << " does not exist" << endl;
		exit(EXIT_FAILURE);
	}
	
	//Pega o nome da classe
	in_file >> className;
	if(!in_file.good() && !in_file.eof()){
		cout << "no class name defined";
	}
	
	//Pega os includes
	includeLine = getLineByIndex(2, in_file);
	
	//Pega os atributos
	getline(in_file, atributesLine);
	
	//Pega os methodos
	string temp;
	while(!in_file.eof()){
		getline(in_file, temp);
		if(!temp.empty())
			methodsLines.push_back(temp);
	}
	
	//Seta as configurações de classConfs
	_classConfs.className  = className;
	_classConfs.includes   = getByLine(includeLine);
	_classConfs.attributes = getAtributesByLine(atributesLine);
	_classConfs.methods	   = getMethodsByLines(methodsLines);
	
	//Fecha o arquivo que tinha as configurações da classe
	in_file.close();
	
	//File name vai ter o mesmo nome que o arquivo modelo da classe
	for(char& c : filename){
		if(c == '.')
			break;
		fileNameToCreate += c;
	}
	
	//Cria o header file
	createHeader(_classConfs, out_file, fileNameToCreate);
	
	//Cria o arquivo de implementação
	createImplementation(_classConfs, out_file, fileNameToCreate);
	
	//Retorna o nome da classe (Retorno utilizado na main)
	return _classConfs.className;
}

void createHeader(const classConfs& _classConfs, ofstream& out_buffer, string filename){
	//Nome que irá ser atribuido ao header file
	string headerName = filename + ".h";
	
	//Cria o arquivo se baseando no nome da classe
	out_buffer.open(headerName);
	if(!out_buffer.is_open()){
		cout << "fail trying to make " << headerName;
	}
	
	//Inicia o pragma once
	out_buffer << "#ifndef " << stringUpper(_classConfs.className) << "_H" << endl;
	out_buffer << "#define " << stringUpper(_classConfs.className) << "_H" << endl;
	out_buffer << endl;
	
	//Adiciona includes a o header file, caso ela tenha
	if(!_classConfs.includes.empty()){
		for(string include : _classConfs.includes){
			out_buffer << "#include " << include << endl;
		}
		out_buffer << endl;
	}
	
	//Adiciona o início da classe
	out_buffer << "class " << _classConfs.className << "{" << endl;
	
	//Adiciona os atributos da classe
	if(!_classConfs.attributes.empty()){
		out_buffer << "private: " << endl;
		for(attribute att : _classConfs.attributes){
			out_buffer << "\t" << att.type << " " << att.name;
			
			//Se o tipo for constante ele inicaliza
			if(att.type.substr(0, 5) == "const"){
				out_buffer << " = {}";
			}
			out_buffer << ";" << endl;
		}
		//Adiciona os Gets e Sets
		out_buffer << "public: " << endl;
		for(const attribute& att : _classConfs.attributes){
			addGetAndSet(att, out_buffer, _classConfs.className, true); 
		}
	}
	
	//Adiciona os metodos
	addMethods(_classConfs.methods, out_buffer, _classConfs.className, true);

	//Finaliza a classe e o  pragma once
	out_buffer << "};" << endl << endl << "#endif";
	
	//Fecha o arquivo
	out_buffer.close();
}

void createImplementation(const classConfs& _classConfs, ofstream& out_buffer, string filename){
	//Nome que ira ser atribuido ao header file
	filename[0] = toupper(filename[0]);
	string implementationName = filename + ".cpp";
	
	//Cria o arquivo se baseando no nome da classe
	out_buffer.open(implementationName);
	if(!out_buffer.is_open()){
		cout << "fail trying to make " << implementationName;
	}
	
	//Da include no arquivo de implementação
	out_buffer << "#include \"" << _classConfs.className << ".h\"" << endl << endl;
	
	//Adiciona os gets e sets se a classe tiver atributos
	if(!_classConfs.attributes.empty()){
		for(const attribute& att : _classConfs.attributes){
			addGetAndSet(att, out_buffer,_classConfs.className, false);
			out_buffer << endl;
		}
	}
	
	//Adiciona os métodos
	addMethods(_classConfs.methods, out_buffer, _classConfs.className, false);
	
	//Fecha o arquivo
	out_buffer.close();
}

string getLineByIndex(int index, ifstream& in_buffer){
	string ret;
	for(int i = 1; i <= index; i++)
		getline(in_buffer, ret);
	return ret;
}

vector<string> getByLine(const string& line){
	stringstream includes;
	string       include;
	vector<string> ret;
	
	includes << line;
	
	while(includes >> include){
		ret.push_back(include);
	}
	
	return ret;
}

string stringUpper(const string& str){
	string ret = "";
	for(const char& c : str){
		ret += toupper(c);
	}
	return ret;
}

vector<attribute> getAtributesByLine(const string& line){
	stringstream     	lineStream;
	vector<attribute> 	ret;
	attribute 			to_push;
	
	lineStream << line;
	
	while(lineStream >> to_push.type >> to_push.name){
		//Seta a parte extra do tipo.
		//Leia a declaração da função para exemplos
		setExtra(to_push.type);
		ret.push_back(to_push);
		to_push = {};
	}
	
	return ret;
}

void addGetAndSet(const attribute& att, ofstream& out_file, const string& className, bool isPrototype){
	string nameFor = att.name;
	//Primeira Letra fica em maiúsuclo
	nameFor[0] = toupper(nameFor[0]);
	
	bool isConst = att.type.substr(0, 5) == "const";
	
	//Se a variável não for const ele cria o set
	if(!isConst){
		if(isPrototype){
			out_file << "\t";
		}
		out_file << "void ";
		if(!isPrototype){
			out_file << className << "::";
		}
		out_file << "set" << nameFor << "(" << att.type;
		if(!isPrototype){
			out_file << " " << att.name;
		}
		out_file << ")";
		if(isPrototype){
			out_file << ";" << endl;
		}else{
			out_file << "{" << endl;
			out_file << "\t" << "this->" << att.name << " = " << att.name << ";" << endl;
			out_file << "}" << endl;
		}
	}
	if(isPrototype){
		out_file << "\t";
	}
	out_file  << att.type << " ";
	if(!isPrototype){
		out_file << className << "::";
	}
	out_file << "get" << nameFor << "()";
	if(isConst)
		out_file << " const";
	if(isPrototype){
		out_file << ";" << endl;
	}else{
		out_file << "{" << endl;
		out_file << "\t" << "return this->" << att.name << ";" << endl;
		out_file << "}" << endl;
	}
}

vector<method> getMethodsByLines(const vector<string>& lines){
	method 	   	   metToPush;
	attribute	   paramToPush;
	vector<method> ret;
	
	for(string line : lines){
		stringstream   lineStream;
		lineStream << line;
		if(lineStream >> metToPush.ret >> metToPush.name){
			if(metToPush.ret[0] == '%'){
				metToPush.isConst = true;
				metToPush.ret = metToPush.ret.substr(1, metToPush.ret.size()-1);
			}
			setExtra(metToPush.ret);
			//Se entrar aqui é porque tem atributos
			while(lineStream >> paramToPush.type >> paramToPush.name){
				setExtra(paramToPush.type);
				metToPush.params.push_back(paramToPush);
				paramToPush = {};
			}
			ret.push_back(metToPush);
			metToPush = {};
		}
	}
	
	return ret;
}

void addMethods(const vector<method>& _methods, ofstream& out_file, const string& className, bool isPrototype){
	for(method _method : _methods){
		if(isPrototype){
			out_file << "\t";
		}
		out_file << _method.ret << " ";
		if(!isPrototype){
			out_file << className << "::";
		}
		out_file << _method.name << "(";
		for(auto at = _method.params.begin(); at < _method.params.end(); at++){
			out_file << at->type;
			if(!isPrototype){
				out_file << " " << at->name;
			}
			if(at+1 != _method.params.end())
				out_file << ", ";
		}
		out_file << ")";
		if(_method.isConst){
			out_file << " const";
		}
		if(isPrototype){
			out_file << ";" << endl;
			continue;
		}
		out_file << "{}" << endl << endl;
	}
}

void setExtra(string& str){
	if((str[0] == '*' && str[1] == '_') || (str[0] == '_' && str[1] == '*')){
		//Remove a parte que tem *_
		str = str.substr(2, str.size()-2);
		str = "const " + str + '&';
	}else if(str[0] == '*'){
		//Remove a parte que tem *
		str = str.substr(1, str.size()-1);
		str = "const " + str;
	}else if(str[0] == '_'){
		//Remove a parte que tem _
		str = str.substr(1, str.size()-1);
		str = str + '&';
	}
}

void makeModel(string className){
	ofstream out_buffer;

	string filename = className + ".txt";
	
	out_buffer.open(filename);
	if(!out_buffer.is_open()){
		cout << "fail trying to make " << filename;
	}
	
	out_buffer << className << endl;
	out_buffer << "*ADD INCLUDES HERE / EXAMPLE : <iostream>*" << endl;
	out_buffer << "*ADD ATTRIBUTES HERE / EXAMPLE : string name int age*" << endl;
	out_buffer << "*ADD METHODS HERE / EXAMPLE : " << endl << "string toString" << endl;
	out_buffer << "REMEBER: " << endl << "_int = int& / *int = const int / *_int = const int&" << endl;
	out_buffer.close();
}
