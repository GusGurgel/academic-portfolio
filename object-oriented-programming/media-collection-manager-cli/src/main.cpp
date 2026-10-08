#include "Arquivos.h"
#include "CD.h"
#include "DVD.h"
#include "Midia.h" //includes: <iostream> <vector> <string>
#include <algorithm>
#include <cstdio>
#include <unordered_set>

using namespace std;

// Media registration routine
MidiaFile *createMedia();

// Element removal routine
void removeMedia(vector<MidiaFile *> &);

// Loads saved files into memory
void load(vector<MidiaFile *> &, const string &);

// Deletes and saves the files that were read
void unload(vector<MidiaFile *> &);

// Gets an integer from the user, preventing invalid inputs
void getInt(int &);

// Gets a float from the user, preventing invalid inputs
void getFloat(float &);

// Prints all media from an artist
void byArtist(const string &, const fileType &, vector<MidiaFile *>);

// Prints all media in a specific year
void byYear(const int &, vector<MidiaFile *>);

// Prints all media of a specific genre
void byGenre(const string &, vector<MidiaFile *>);

// Prints all keywords without repetition
void allKeywords(vector<MidiaFile *>);

// Prints the available commands
void printHelp();

int main() {
  system("chcp 65001 > nul");

  vector<MidiaFile *> main_vec;
  // Indicates if it's the first command to be executed
  bool firstCommand{true};

  // Prints the available commands on startup
  printHelp();

  // Loading saved media into memory
  load(main_vec, "Resources/");

  //----------------CRUD------------------
  while (true) {
    if (firstCommand)
      makeLine();

    // Command stream
    stringstream commandStream;
    // Full command line
    string commandLine;
    // Just the command
    string command;

    getline(cin, commandLine);
    commandStream << commandLine;
    commandStream >> command;

    if (command == "create") {
      makeLine();
      main_vec.push_back(createMedia());
    } else if (command == "show") {
      makeLine();
      for (MidiaFile *&mf : main_vec) {
        cout << "{" << mf->getTypeStr() << "}\n";
        mf->getMidia()->print();
        if (*(main_vec.end() - 1) != mf)
          makeLine();
      }
    } else if (command == "search") {
      string line;
      int year{0};

      makeLine();
      cout << "{a} - All CDs from an artist ordered by date" << endl;
      cout << "{b} - All DVDs from an artist ordered by date" << endl;
      cout << "{c} - All Media from an artist ordered by date" << endl;
      cout << "{d} - All Media released in a specific year in alphabetical order" << endl;
      cout << "{e} - Given a title, show tracks in common and specific to the same artist" << endl;
      cout << "{f} - CDs and DVDs separated by the same genre in alphabetical order" << endl;
      cout << "{g} - All keywords without repetition" << endl;
      cout << "Option: ";

      getline(cin, line);

      switch (tolower(line[0])) {
      case 'a':
        cout << "Artist name: ";
        getline(cin, line);
        byArtist(line, fileType::T_CD, main_vec);
        break;
      case 'b':
        cout << "Artist name: ";
        getline(cin, line);
        byArtist(line, fileType::T_DVD, main_vec);
        break;
      case 'c':
        cout << "Artist name: ";
        getline(cin, line);
        byArtist(line, fileType::T_MIDIA, main_vec);
        break;
      case 'd':
        cout << "Release year: ";
        getInt(year);
        byYear(year, main_vec);
        break;
      case 'f':
        cout << "Genre: ";
        getline(cin, line);
        byGenre(line, main_vec);
        break;
      case 'g':
        allKeywords(main_vec);
        break;
      default:
        makeLine();
        cout << "Not implemented" << endl;
        break;
      }
    } else if (command == "remove") {
      removeMedia(main_vec);
    } else if (command == "help") {
      printHelp();
    } else if (command == "exit") {
      cout << "Exiting..." << endl;
      makeLine();
      break;
    } else {
      // Handles invalid commands and shows the right ones
      makeLine();
      cout << "Error: Command '" << command << "' not found." << endl;
      printHelp();
    }

    makeLine();
    firstCommand = false;
  }
  //--------------------------------------
  // Unloading saved media from memory
  unload(main_vec);

  return EXIT_SUCCESS;
}

void load(vector<MidiaFile *> &mfs, const string &folder) {
  // Getting all files in the folder
  vector<string> *resources = getAllArquives(folder);

  // Creating files and putting them in the main vector
  for (const string &str : *(resources)) {
    mfs.push_back(new MidiaFile(str));
  }
}

void unload(vector<MidiaFile *> &mfs) {
  for (MidiaFile *mf : mfs) {
    mf->save();
    delete mf;
  }
}

MidiaFile *createMedia() {
  Midia *m{nullptr};
  MidiaFile *ret{nullptr};
  string line;
  int type{0};

  cout << "{0} Media" << endl;
  cout << "{1} CD" << endl;
  cout << "{2} DVD" << endl << endl;
  cout << "Type: ";

  // Getting the desired type
  getInt(type);

  switch (type) {
  case 0:
    m = new Midia();
    break;
  case 1:
    m = new CD();
    break;
  case 2:
    m = new DVD();
    break;
  default:
    m = new Midia();
  }

  cout << "Artist: ";
  getline(cin, line);
  m->setArtista(line);

  cout << "Title: ";
  getline(cin, line);
  m->setTitulo(line);

  cout << "Tracks: ";
  getline(cin, line);
  vector<string> *faixas = oneVecByLine(line);
  m->setFaixas(faixas);

  // Loop for correctly entering the date
  while (true) {
    cout << "Date (dd/mm/yyyy): ";
    getline(cin, line);
    Data d;
    try {
      d.dia = stoi(line.substr(0, 2));
      d.mes = stoi(line.substr(3, 2));
      d.ano = stoi(line.substr(6, 4));
    } catch (exception e) {
      cout << "Date format is incorrect, please try again." << endl;
      continue;
    }
    m->setLancamento(d);
    break;
  }

  cout << "Genre: ";
  getline(cin, line);
  m->setGenero(line);

  cout << "Keywords: ";
  getline(cin, line);
  vector<string> *keywords = oneVecByLine(line);
  m->setKeywords(keywords);

  if (type == 1) {
    int int_aux;
    float float_aux;

    CD *cd_ref = dynamic_cast<CD *>(m);

    if (cd_ref) {
      cout << "Duration: ";
      getInt(int_aux);
      cd_ref->setDuracao(int_aux);

      cout << "Volume: ";
      getFloat(float_aux);
      cd_ref->setVolume(float_aux);

      cout << "Compilation (yes/no): ";
      cin >> line;
      if (line == "yes") {
        cd_ref->setColetanea(1);
      } else {
        cd_ref->setColetanea(0);
      }
      getline(cin, line); // To clear the buffer
    }

  } else if (type == 2) {
    DVD *dvd_ref = dynamic_cast<DVD *>(m);

    if (dvd_ref) {
      cout << "Audio Format: ";
      getline(cin, line);
      vector<string> *formatoAudio = oneVecByLine(line);
      dvd_ref->setFormatoAudio(formatoAudio);

      cout << "Screen Format: ";
      getline(cin, line);
      vector<string> *formatoTela = oneVecByLine(line);
      dvd_ref->setFormatoTela(formatoTela);

      cout << "Subtitles: ";
      getline(cin, line);
      vector<string> *legendas = oneVecByLine(line);
      dvd_ref->setLegendas(legendas);
    }
  }

  // Creating the media file
  ret = new MidiaFile(m);

  return ret;
}

void removeMedia(vector<MidiaFile *> &mf) {
  int index{0};
  string temp;

  makeLine();

  // Printing all paths
  for (size_t i{0}; i < mf.size(); i++)
    cout << i << ": " << mf[i]->getPath() << endl;

  cout << endl << "Enter the index to be deleted: ";
  getInt(index);
  try {
    MidiaFile *ref = mf.at(index);
    cout << "Deleting: " << ref->getPath() << endl;
    mf.erase(mf.begin() + index);   // Removing from vector
    remove(ref->getPath().c_str()); // Removing from physical memory
    delete ref;                     // Freeing RAM memory
  } catch (out_of_range exc) {
    cout << "Invalid index value" << endl;
  }
}

void printHelp() {
  cout << "========================================" << endl;
  cout << "           AVAILABLE COMMANDS           " << endl;
  cout << "========================================" << endl;
  cout << " create - Register a new media" << endl;
  cout << " show   - Display all registered media" << endl;
  cout << " search - Query and filter media" << endl;
  cout << " remove - Delete a media by index" << endl;
  cout << " help   - Show this command list again" << endl;
  cout << " exit   - Close the application" << endl;
  cout << "========================================" << endl;
}

void getInt(int &i) {
  string line;

  while (true) {
    getline(cin, line);
    try {
      i = stoi(line);
      break;
    } catch (invalid_argument &) {
      cout << "Invalid input!!!!" << endl;
      continue;
    }
  }
}

void getFloat(float &f) {
  string line;

  while (true) {
    getline(cin, line);
    try {
      f = stof(line);
      break;
    } catch (invalid_argument &) {
      cout << "Invalid input!!!!" << endl;
      continue;
    }
  }
}

void byArtist(const string &artista, const fileType &tipo,
                vector<MidiaFile *> mfs) {
  vector<Midia *> main_vec;
  string typeString;

  for (MidiaFile *&mf : mfs) {
    if (mf->getMidia()->getArtista() == artista) {
      if (mf->getType() == tipo && tipo != fileType::T_MIDIA) {
        main_vec.push_back(mf->getMidia());
      } else if (tipo == fileType::T_MIDIA) {
        main_vec.push_back(mf->getMidia());
      }
    }
  }

  if (main_vec.empty()) {
    makeLine();
    cout << "None found" << endl;
    return;
  }

  sort(main_vec.begin(), main_vec.end(), data_crescente);

  for (Midia *m : main_vec) {
    makeLine();
    cout << "{" << TypeStr(m) << "}" << endl;
    m->print();
  }
}

void byYear(const int &ano, vector<MidiaFile *> mfs) {
  vector<Midia *> main_vec;
  string typeString;

  for (MidiaFile *mf : mfs) {
    if (mf->getMidia()->getLancamento().ano == ano) {
      main_vec.push_back(mf->getMidia());
    }
  }

  if (main_vec.empty()) {
    makeLine();
    cout << "None found" << endl;
    return;
  }

  sort(main_vec.begin(), main_vec.end(), alfabetica);

  for (Midia *m : main_vec) {
    makeLine();
    cout << "{" << TypeStr(m) << "}" << endl;
    m->print();
  }
}

void byGenre(const string &genero, vector<MidiaFile *> mfs) {
  vector<Midia *> vec_cds;
  vector<Midia *> vec_dvds;

  for (MidiaFile *mf : mfs) {
    if (mf->getMidia()->getGenero() == genero &&
        mf->getType() == fileType::T_CD) {
      vec_cds.push_back(mf->getMidia());
    } else if (mf->getMidia()->getGenero() == genero &&
               mf->getType() == fileType::T_DVD) {
      vec_dvds.push_back(mf->getMidia());
    }
  }

  if (vec_cds.empty() && vec_dvds.empty()) {
    makeLine();
    cout << "None found" << endl;
    return;
  }

  // Organizing vectors
  sort(vec_cds.begin(), vec_cds.end(), alfabetica);
  sort(vec_dvds.begin(), vec_dvds.end(), alfabetica);

  for (Midia *m : vec_cds) {
    makeLine();
    cout << "{" << TypeStr(m) << "}" << endl;
    m->print();
  }

  for (Midia *m : vec_dvds) {
    makeLine();
    cout << "{" << TypeStr(m) << "}" << endl;
    m->print();
  }
}

void allKeywords(vector<MidiaFile *> mfs) {
  unordered_set<string> keywords;
  bool first{true};

  for (MidiaFile *mf : mfs) {
    for (string str : *(mf->getMidia()->getKeywords())) {
      keywords.insert(str);
    }
  }

  if (keywords.empty()) {
    makeLine();
    cout << "None found" << endl;
    return;
  }

  makeLine();
  for (string str : keywords) {
    if (!first)
      cout << ", ";
    cout << str;
    first = false;
  }
  cout << endl;
}
