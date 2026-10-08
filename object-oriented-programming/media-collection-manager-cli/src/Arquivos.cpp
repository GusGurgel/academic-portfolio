#include "Arquivos.h"

bool folderExist(const string& path){
	struct stat info;

	if(stat(path.c_str(), &info) != 0){
		return false;
	}else if(info.st_mode & S_IFDIR){
		return true;
	}else{
		return false;
	}
}

vector<string>* getAllArquives(const string& folder,const string& ext){
	if(!folderExist(folder)){
		throw runtime_error("Folder: " + folder + " not exist\n");
	}

	vector<string>* ret = new vector<string>();

	for(const auto & entry : fs::directory_iterator(folder)){
		string entry_ext = entry.path().string();
		entry_ext = entry_ext.substr(entry_ext.size()-ext.size());
		if(entry_ext == ext){
			ret->push_back(entry.path().string());
		}
	}


	return ret;
}

string oneLineVec(vector<string>* vec){
	stringstream ss;

	bool first {true};

	for(const string& str : *(vec) ){
		if(!first)
			ss << " ";
		ss << str;
		first = false;
	}
	return ss.str();
}

string toStringData(const Data& data){
	stringstream ret;
	ret << data.dia << " ";
	ret << data.mes << " ";
	ret << data.ano;

	return ret.str();
}

string MidiaFile::getTypeStr(){
	string ret = TypeStr(this->getMidia());
	return ret;
}

MidiaFile::MidiaFile(Midia* m){
	//Pegando o endereço para utilizar no nome do arquivo
	const void * address = static_cast<const void*>(m);
	stringstream ss;
	ss << address;
	//Cria uma path para esse arquivo (já que ele foi criado em memória ram)
	this->m_path = "Resources/" + m->getArtista() + "-" + m->getTitulo() + "-" + ss.str().substr(2) + ".txt";
	this->m_midia = m;

	this->m_type = getFileType(m);
}

vector<string>* oneVecByLine(const string& line){
	stringstream ss {line};
	string aux;
	vector<string>* ret = new vector<string>();

	while(ss >> aux){
		ret->push_back(aux);
	}

	return ret;
}

void MidiaFile::openMidia(Midia* m, ifstream& in_file){
	string aux; //string auxiliar

	getline(in_file, aux); //Necessário para remover primeira linha já lida

	//Segunda linha: Artista
	getline(in_file, aux);
	m->setArtista(aux);

	//Terceira linha: Título
	getline(in_file, aux);
	m->setTitulo(aux);

	//Quarta linha: Faixas
	getline(in_file, aux);
	vector<string>* faixas = oneVecByLine(aux);
	m->setFaixas(faixas);

	//Quinta linha: Lancamento
	Data d;
	getline(in_file, aux);
	stringstream ss{aux};
	ss >> d.dia;
	ss >> d.mes;
	ss >> d.ano;
	m->setLancamento(d);

	//Sexta linha: Gênero
	getline(in_file, aux);
	m->setGenero(aux);

	//Sétima linha: keywords
	getline(in_file, aux);
	vector<string>* keywords = oneVecByLine(aux);
	m->setKeywords(keywords);
}

MidiaFile::MidiaFile(const string& path){
	ifstream in_file;

	this->m_path = path;

	in_file.open(m_path);
	if(!in_file.is_open()){
		throw runtime_error("Fail trying to open: " + m_path + "\n");
	}

	//Pegando tipo: DVD/CD/MIDIA
	int type;
	in_file >> type;
	this->m_type = (fileType)type;

	if(m_type == fileType::T_CD){
		CD* temp = new CD();
		openMidia(temp, in_file);

		int int_aux;
		float float_aux;

		//Oitava linha: Duração
		in_file >> int_aux;
		temp->setDuracao(int_aux);

		//Nona linha: Volume
		in_file >> float_aux;
		temp->setVolume(float_aux);

		//Décima linha: Coletânea
		in_file >> int_aux;
		temp->setColetanea(int_aux);

		this->m_midia = temp;

	}else if(m_type == fileType::T_DVD){
		DVD* temp = new DVD();
		openMidia(temp, in_file);

		string line;

		//Oitava linha: Formato Audio
		getline(in_file, line); //Quarta linha: Faixas
		vector<string>* FormatoAudio = oneVecByLine(line);
		temp->setFormatoAudio(FormatoAudio);

		//Nona linha: Formato Tela
		getline(in_file, line); //Quarta linha: Faixas
		vector<string>* FormatoTela = oneVecByLine(line);
		temp->setFormatoTela(FormatoTela);

		//Nona linha: Legendas
		getline(in_file, line); //Quarta linha: Faixas
		vector<string>* Legendas = oneVecByLine(line);
		temp->setLegendas(Legendas);

		this->m_midia = temp;

	}else if(m_type == fileType::T_MIDIA){
		Midia* temp = new Midia();
		openMidia(temp, in_file);

		this->m_midia = temp;
	}

	//Fechando arquivo
	in_file.close();
}

MidiaFile::~MidiaFile(){
	if(m_midia)
		delete m_midia;
}

void MidiaFile::save(){
	ofstream out_file;
	out_file.open(this->m_path);
	if(!out_file.is_open()){
		throw runtime_error("Fail trying to open: " + m_path + "\n");
	}

	out_file << m_type << endl;
	out_file << m_midia->getArtista() << endl;
	out_file << m_midia->getTitulo() << endl;
	out_file << oneLineVec(m_midia->getFaixas()) << endl;
	out_file << toStringData(m_midia->getLancamento()) << endl;
	out_file << m_midia->getGenero() << endl;
	out_file << oneLineVec(m_midia->getKeywords()) << endl;

	if(m_type == T_CD){
		CD* cd_ref = dynamic_cast<CD*>(m_midia);
		if(cd_ref){
			out_file << cd_ref->getDuracao() << endl;
			out_file << cd_ref->getVolume() << endl;
			out_file << cd_ref->getColetanea();
		}

	}else if(m_type == T_DVD){
		DVD* dvd_ref = dynamic_cast<DVD*>(m_midia);
		if(dvd_ref){
			out_file << oneLineVec(dvd_ref->getFormatoAudio()) << endl;
			out_file << oneLineVec(dvd_ref->getFormatoTela()) << endl;
			out_file << oneLineVec(dvd_ref->getLegendas());
		}
	}

	//Fechando arquivo
	out_file.close();
}

Midia* MidiaFile::getMidia(){
	return this->m_midia;
}

string MidiaFile::getPath(){
	return this->m_path;
}

fileType MidiaFile::getType(){
	return this->m_type;
}

fileType getFileType(Midia*& m){
	if(dynamic_cast<CD*>(m)){
		return fileType::T_CD;
	}else if(dynamic_cast<DVD*>(m)){
		return fileType::T_DVD;
	}else{
		return fileType::T_MIDIA;
	}
}

string TypeStr(Midia* m){
	int type = (int)getFileType(m);

	switch(type){
		case 0:
			return "Midia";
			break;
		case 1:
			return "CD";
			break;
		case 2:
			return "DVD";
			break;
		default:
			return "Unknown";
	}
}
