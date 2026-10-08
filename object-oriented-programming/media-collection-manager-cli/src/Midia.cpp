#include "Midia.h"

/* ==================
 * =  Construtores  =
 * ================== */
Midia::Midia(const string& artista, const string& titulo, vector<string>* _faixas, const Data& lancamento, const string& genero, vector<string>* _keywords){
	/* =====================
	 * = Evita passagem de =
	 * = ponteiros nulo    =
	 * ===================== */
	if(_faixas == nullptr){
		faixas = new vector<string>();
	}else{
		this->faixas = _faixas;
	}
	if(_keywords == nullptr){
		keywords = new vector<string>();
	}else{
		this->keywords = _keywords;
	}
	this->artista 	  = artista;
	this->titulo  	  = titulo;
	this->lancamento  = lancamento;
	this->genero      = genero;
}

Midia::Midia(const string& artista, const string& titulo, const vector<string>& _faixas, const Data& lancamento, const string& genero, const vector<string>& _keywords){
	this->faixas = new vector<string>();
	this->keywords = new vector<string>();
	
	this->artista 	  = artista;
	this->titulo  	  = titulo;
	*(this->faixas)   = _faixas;
	this->lancamento  = lancamento;
	this->genero      = genero;
	*(this->keywords) = _keywords;
}

Midia::Midia(){
	//Apenas alocação dos vetores
	this->faixas   = new vector<string>;
	this->keywords = new vector<string>;
}

/* ===================
 * =    Destrutor    =
 * =================== */
Midia::~Midia(){
	delete faixas;
	delete keywords;
}

/* ==================
 * =   Gets e Sets  = 
 * ================== */

void Midia::setArtista(string artista){
	this->artista = artista;
}
string Midia::getArtista(){
	return this->artista;
}

void Midia::setTitulo(string titulo){
	this->titulo = titulo;
}
string Midia::getTitulo(){
	return this->titulo;
}

void Midia::setFaixas(vector<string>* faixas){
	//Não possibilita passar um vetor nulo
	if(!faixas)
		return;
	this->faixas = faixas;
}
vector<string>* Midia::getFaixas(){
	return this->faixas;
}

void Midia::setLancamento(Data lancamento){
	this->lancamento = lancamento;
}
Data Midia::getLancamento(){
	return this->lancamento;
}
const Data Midia::getLancamento() const{
	return this->lancamento;
}

void Midia::setGenero(string genero){
	this->genero = genero;
}
string Midia::getGenero(){
	return this->genero;
}

void Midia::setKeywords(vector<string>* keywords){
	//Não possibilita passar um vetor nulo
	if(!keywords)
		return;
	this->keywords = keywords;
}
vector<string>* Midia::getKeywords(){
	return this->keywords;
}

/* ==================
 * =     Métodos    = 
 * ================== */
bool Midia::getFaixa(string unnamede){
	//retorna se a string não é vazia
	return unnamede != "";
}

//ll == last_line (fala se tem ou não que fazer a ultima linha)
void Midia::print(){
	cout << "Artista: " << artista << endl;
	cout << "Titulo: " << titulo << endl;
	cout << "Faixas: " << *faixas << endl;
	cout << "Lancamento: " << lancamento << endl;
	cout << "Genero: " << genero << endl;
	cout << "Keywords: " << *keywords << endl;
}

/* ===========
 * = Funções =
 * =========== */

//*Vesão Dinamica*
bool data_crescente(Midia* midia1,  Midia* midia2){
	return midia1->getLancamento() < midia2->getLancamento();
}
bool data_decrescente(Midia* midia1,  Midia* midia2){
	const Data& m1 = midia1->getLancamento();
	const Data& m2 = midia2->getLancamento();
	
	return !(m1 < m2) && m1 != m2;
}

bool alfabetica(Midia* midia1, Midia* midia2){
	if(midia1->getTitulo().size() == 0 || midia2->getTitulo().size() == 0)
		return false;
	
	return (tolower(midia1->getTitulo()[0])) < tolower((midia2->getTitulo()[0]));
}

void makeLine(uint size, char c){
	for(int i{0}; i < size; i++)
		cout << c;
	cout << endl;
}

/* ==================
 * =    Operators   = 
 * ================== */
ostream& operator<<(ostream& os, const vector<string>& vec){
	bool first{true};
	for(const string& str : vec){
		if(!first){
			os << ", ";
		}else{ first = false; }
		os << str;
	}
	return os;
}

ostream& operator<<(ostream& os, const Data& data){
	os << data.dia << '/' << data.mes << '/' << data.ano;
	return os;
}

bool operator < (const Data& data1, const Data& data2){
	if(data1.ano < data2.ano && data1.ano != data2.ano){
		return true;
	}else if(data1.ano == data2.ano){
		if(data1.mes < data2.mes && data1.mes != data2.mes){
			return true;
		}else if(data1.mes == data2.mes){
			return data1.dia < data2.dia;
		}else{
			return false;
		}
	}else{
		return false;
	}
}

bool operator != (const Data& data1, const Data& data2){
	return !(data1.ano == data2.ano && data1.mes == data2.mes && data1.dia == data2.dia);
}
