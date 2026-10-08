#include "DVD.h"

/* ==================
* =  Construtores  =
* ================== */
DVD::DVD(const string& artista, const string& titulo, vector<string>* _faixas, const Data& lancamento, const string& genero, vector<string>* keywords, vector<string>* _formatoAudio, vector<string>* _formatoTela, vector<string>* _legendas) :
Midia(artista, titulo, _faixas, lancamento, genero, keywords)
{
	if(_formatoAudio == nullptr){
		_formatoAudio = new vector<string>();
	}else{
		this->formatoAudio = _formatoAudio;
	}
	if(_formatoTela == nullptr){
		_formatoTela = new vector<string>();
	}else{
		this->formatoTela = _formatoTela;
	}
	if(_legendas == nullptr){
		_legendas = new vector<string>();
	}else{
		this->legendas = _legendas;
	}
}

DVD::DVD(const string& artista, const string& titulo, const vector<string>& _faixas, const Data& lancamento, const string& genero, const vector<string>& keywords, const vector<string>& formatoAudio, const vector<string>& formatoTela, const vector<string>& legendas) :
Midia(artista, titulo, _faixas, lancamento, genero, keywords)
{
	this->formatoAudio = new vector<string>;
	this->formatoTela  = new vector<string>;
	this->legendas     = new vector<string>;
	
	*(this->formatoAudio) = formatoAudio;
	*(this->formatoTela)  = formatoTela;
	*(this->legendas)     = legendas;
}

DVD::DVD(){
	//Apenas alocação dos vetores
	this->formatoAudio = new vector<string>;
	this->formatoTela  = new vector<string>;
	this->legendas     = new vector<string>;
}

/* ===================
 * =    Destrutor    =
 * =================== */
DVD::~DVD(){
	delete formatoAudio;
	delete formatoTela;
	delete legendas;
}

/* ==================
*  =   Gets e Sets  = 
*  ================== */
void DVD::setFormatoAudio(vector<string>* formatoAudio){
	this->formatoAudio = formatoAudio;
}
vector<string>* DVD::getFormatoAudio(){
	return this->formatoAudio;
}

void DVD::setFormatoTela(vector<string>* formatoTela){
	this->formatoTela = formatoTela;
}
vector<string>* DVD::getFormatoTela(){
	return this->formatoTela;
}

void DVD::setLegendas(vector<string>* legendas){
	this->legendas = legendas;
}
vector<string>* DVD::getLegendas(){
	return this->legendas;
}

/* ==================
 * =     Métodos    = 
 * ================== */
 void DVD::print(){
	Midia::print();
	cout << "Formato Audio: " << *formatoAudio << endl;
	cout << "Formato Tela: "  << *formatoTela  << endl;
	cout << "Legendas: "      << *legendas     << endl;
}
