#ifndef MIDIA_H
#define MIDIA_H

#include <string>
#include <vector>
#include <iostream>
#include <cctype>

/* ===========
 * =  Using  =
 * =========== */
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::ostream;

//Apelido para unsigned int
typedef unsigned int uint;

/* ===========
 * = Structs =
 * =========== */
typedef struct{
	uint dia;
	uint mes;
	uint ano;
} Data;

/* ===========
 * = Classes =
 * =========== */
class Midia{
private: 
	/* ==================================
	 * = Inicialização dos valores como =
	 * = forma de evita um undefined    =
	 * = behavior                       =
	 * ============================== */
	string artista {""};
	string titulo  {""};
	vector<string>* faixas {nullptr};
	Data lancamento{0,0,0};
	string genero {""};
	vector<string>* keywords{nullptr};
public: 
	/* ===================
	 * =   Construtores  =
 	 * =================== */
	Midia(const string&, const string&, vector<string>*, const Data&, const string&, vector<string>*);
	
	Midia(const string&, const string&, const vector<string>&, const Data&, const string&, const vector<string>&);
	
	Midia();
	
	/* ===================
	 * =    Destrutor    =
 	 * =================== */
	virtual ~Midia();
	
	/* ==================
	 * =   Gets e Sets  = 
	 * ================== */
	void setArtista(string);
	string getArtista();
	
	void setTitulo(string);
	string getTitulo();
	
	void setFaixas(vector<string>*);
	vector<string>* getFaixas();
	
	void setLancamento(Data);
	Data getLancamento();
	//Pega lançamento de forma constante
	const Data getLancamento() const;
	
	void setGenero(string);
	string getGenero();
	
	void setKeywords(vector<string>*);
	vector<string>* getKeywords();
	
	/* ==================
	 * =     Métodos    = 
	 * ================== */
	bool getFaixa(string);
	
	/* ===================================
	 * = LL = last line                  =
	 * = informa se deve ou não colocar  =
	 * = uma linha no final do debug.    =
	 * =================================== */
	virtual void print();       
};

/* ===========
 * = Funções =
 * =========== */
 
/* =================================
 * = Compara duas Midias pela data =
 * =  (versão dinamica e estatica) =
 * ================================= */
bool data_crescente(Midia*, Midia*);
bool data_decrescente(Midia*, Midia*);

bool alfabetica(Midia*, Midia*);
 
/* ============================
 * = Faz uma linha no console =
 * ============================ */
void makeLine(uint = 53, char = '=');

/* ==================
 * =    Operators   = 
 * ================== */
 
/* ==============================
 * = vector<string> to string   = 
 * ==============================*/
ostream& operator<<(ostream&, const vector<string>&);

/* ====================
 * = Data to string   = 
 * ====================*/
ostream& operator<<(ostream&, const Data&);

/* ===============
 * = Data < Data = 
 * ===============*/
bool operator < (const Data&, const Data&);

/* ================
 * = Data != Data = 
 * ================*/
bool operator != (const Data&, const Data&);


#endif
