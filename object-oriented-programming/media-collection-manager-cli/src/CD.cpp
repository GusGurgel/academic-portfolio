#include "CD.h"

/* ==================
 * =  Construtores  =
 * ================== */
CD::CD(const string& artista, const string& titulo, vector<string>* _faixas, const Data& lancamento, const string& genero, vector<string>* _keywords, const uint& duracao, const float& volume, const bool& coletanea)
: Midia(artista, titulo, _faixas, lancamento, genero, _keywords)
{
	this->duracao   = duracao;
	this->volume    = volume;
	this->coletanea = coletanea;
}

CD::CD(const string& artista, const string& titulo, const vector<string>& _faixas, const Data& lancamento, const string& genero, const vector<string>& _keywords, const uint& duracao, const float& volume, const bool& coletanea)
: Midia(artista, titulo, _faixas, lancamento, genero, _keywords){
	this->duracao   = duracao;
	this->volume    = volume;
	this->coletanea = coletanea;
}

CD::CD(): Midia(){
	
}
/* ==================
*  =   Gets e Sets  = 
*  ================== */
void CD::setDuracao(uint duracao){
	this->duracao = duracao;
}
uint CD::getDuracao(){
	return this->duracao;
}

void CD::setVolume(float volume){
	this->volume = volume;
}
float CD::getVolume(){
	return this->volume;
}

void CD::setColetanea(bool coletanea){
	this->coletanea = coletanea;
}
bool CD::getColetanea(){
	return this->coletanea;
}

/* ==================
 * =     Métodos    = 
 * ================== */
void CD::print(){
	Midia::print();
	cout << "Duração: " << duracao << endl;
	cout << "Volume: "  << volume << endl;
	cout << "coletanea: " << coletanea << endl;
}
