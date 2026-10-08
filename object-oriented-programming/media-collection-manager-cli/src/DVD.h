#ifndef DVD_H
#define DVD_H

#include "Midia.h"

class DVD : public Midia{
private: 
	vector<string>* formatoAudio;
	vector<string>* formatoTela;
	vector<string>* legendas;
public: 
	/* ==================
	* =  Construtores  =
	* ================== */
	DVD(const string&, const string&, vector<string>*, const Data&, const string&, vector<string>*, vector<string>*, vector<string>*, vector<string>*);
	DVD(const string&, const string&, const vector<string>&, const Data&, const string&, const vector<string>&, const vector<string>&, const vector<string>&, const vector<string>&);
	DVD();

	/* ===================
	 * =    Destrutor    =
 	 * =================== */
	~DVD();
	
	/* ==================
	*  =   Gets e Sets  = 
	*  ================== */
	void setFormatoAudio(vector<string>*);
	vector<string>* getFormatoAudio();
	void setFormatoTela(vector<string>*);
	vector<string>* getFormatoTela();
	void setLegendas(vector<string>*);
	vector<string>* getLegendas();

	/* ==================
	 * =     Métodos    = 
	 * ================== */
	 void print();
};

#endif
