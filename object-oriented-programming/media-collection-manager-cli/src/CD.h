#ifndef CD_H
#define CD_H

#include "Midia.h"

class CD : public Midia{
private: 
	/* ==================================
	 * = Inicialização dos valores como =
	 * = forma de evita um undefined    =
	 * = behavior                       =
	 * ================================== */
	uint duracao   {0};
	float volume   {0};
	bool coletanea {0};
public:
	/* ==================
	 * =  Construtores  =
	 * ================== */
	CD(const string&, const string&, vector<string>*, const Data&, const string&, vector<string>*, const uint&, const float&, const bool&);
	CD(const string&, const string&, const vector<string>&, const Data&, const string&, const vector<string>&, const uint&, const float&, const bool&);
	CD();
	
	/* ==================
	 * =  Construtores  =
	 * ================== */
	 ~CD(){ };
	
	/* ==================
	 * =   Gets e Sets  = 
	 * ================== */
	void setDuracao(uint);
	uint getDuracao();
	
	void setVolume(float);
	float getVolume();
	
	void setColetanea(bool);
	bool getColetanea();
	
	/* ==================
	 * =     Métodos    = 
	 * ================== */
	 void print();
};

#endif
