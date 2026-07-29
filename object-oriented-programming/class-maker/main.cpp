/**
 * \file main.cpp
 * \brief C++ class generator from template text files.
 */

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

/**
 * \brief Represents a class attribute.
 */
struct attribute {
  string type; ///< Attribute type (e.g., int, string).
  string name; ///< Attribute name.
};

/**
 * \brief Represents a class method.
 */
struct method {
  string ret;               ///< Return type of the method.
  string name;              ///< Method name.
  vector<attribute> params; ///< Parameter list.
  bool isConst = false;     ///< Indicates whether the method is const.
};

/**
 * \brief Structural configuration for the generated class.
 */
struct classConfs {
  string className;             ///< Name of the class.
  vector<string> includes;      ///< Included headers/libraries.
  vector<attribute> attributes; ///< List of attributes.
  vector<method> methods;       ///< List of methods.
};

/**
 * \brief Generates the header file (.h) for the class.
 * \param _classConfs Class configuration struct.
 * \param out_buffer Output file stream.
 * \param filename Base file name.
 */
void createHeader(const classConfs &_classConfs, ofstream &out_buffer,
                  string filename);

/**
 * \brief Generates the implementation file (.cpp) for the class.
 * \param _classConfs Class configuration struct.
 * \param out_buffer Output file stream.
 * \param filename Base file name.
 */
void createImplementation(const classConfs &_classConfs, ofstream &out_buffer,
                          string filename);

/**
 * \brief Generates encapsulation methods (Getters and Setters) for an
 * attribute.
 * \param att Target attribute.
 * \param out_file Output stream.
 * \param className Name of the class.
 * \param isPrototype If true, generates prototype signatures for the header.
 */
void addGetAndSet(const attribute &att, ofstream &out_file,
                  const string &className, bool isPrototype = true);

/**
 * \brief Generates signatures or implementations for methods.
 * \param _methods List of methods.
 * \param out_file Output stream.
 * \param className Name of the class.
 * \param isPrototype If true, generates prototype signatures for the header.
 */
void addMethods(const vector<method> &_methods, ofstream &out_file,
                const string &className, bool isPrototype = true);

/**
 * \brief Extracts tokens (e.g., includes) from a single line.
 * \param line Line containing space-separated inclusions.
 * \return Vector of strings with inclusion tokens.
 */
vector<string> getByLine(const string &line);

/**
 * \brief Retrieves a specific line from a file stream.
 * \param index 1-based line index.
 * \param in_buffer Input file stream.
 * \return The target line string.
 */
string getLineByIndex(int index, ifstream &in_buffer);

/**
 * \brief Extracts attributes from a formatted string line.
 * \param line String with type-name pairs (e.g., "int age string name").
 * \return Vector of attributes.
 */
vector<attribute> getAtributesByLine(const string &line);

/**
 * \brief Extracts methods from a vector of formatted lines.
 * \param lines Vector where each string represents a method declaration.
 * \return Vector of methods.
 */
vector<method> getMethodsByLines(const vector<string> &lines);

/**
 * \brief Parses input file and triggers class file creation.
 * \param filename Path to input text file.
 * \return Name of generated class.
 */
string makeClass(string filename);

/**
 * \brief Creates an empty template file for class definition.
 * \param className Target class name for the model.
 */
void makeModel(string className);

/**
 * \brief Converts a string to uppercase.
 * \param str Input string.
 * \return Uppercase string.
 */
string stringUpper(const string &str);

/**
 * \brief Applies C++ type modifiers based on prefix syntax (*, _, *_).
 * \param str Type string to modify.
 */
void setExtra(string &str);

void printComandoInvalid(string &comando);

int main() {
  std::string empty_string = "";
  printComandoInvalid(empty_string);

  while (true) {
    string linha, comando;
    getline(cin, linha);
    stringstream lineStream{linha};
    lineStream >> comando;

    if (comando == "create") {
      string filename;
      lineStream >> filename;
      cout << "Classe { " << makeClass(filename) << " } criada com exito\n";
    } else if (comando == "exit") {
      cout << "Exiting...\n";
      exit(EXIT_SUCCESS);
    } else if (comando == "model") {
      string className;
      lineStream >> className;
      makeModel(className);
      cout << "Modelo { " << className << " } criado com exito\n";
    } else {
      printComandoInvalid(comando);
    }
  }
}

void printComandoInvalid(string &comando) {
  if (comando != "") {
    cout << "Comando invalido: '" << comando << "'\n";
  }
  cout << "Comandos disponiveis:\n"
       << "  model <nome_classe>    - Cria um arquivo de modelo (.txt)\n"
       << "  create <nome_arquivo>  - Gera os arquivos .h e .cpp a partir do modelo\n"
       << "  exit                   - Encerra a execucao\n";
}

string makeClass(string filename) {
  ifstream in_file;
  ofstream out_file;

  string className;
  string includeLine;
  string atributesLine;
  string fileNameToCreate{""};
  vector<string> methodsLines;
  classConfs _classConfs;

  in_file.open(filename);
  if (!in_file.is_open()) {
    cout << "file " << filename << " does not exist\n";
    exit(EXIT_FAILURE);
  }

  in_file >> className;
  if (!in_file.good() && !in_file.eof()) {
    cout << "no class name defined\n";
  }

  includeLine = getLineByIndex(2, in_file);
  getline(in_file, atributesLine);

  string temp;
  while (!in_file.eof()) {
    getline(in_file, temp);
    if (!temp.empty())
      methodsLines.push_back(temp);
  }

  _classConfs.className = className;
  _classConfs.includes = getByLine(includeLine);
  _classConfs.attributes = getAtributesByLine(atributesLine);
  _classConfs.methods = getMethodsByLines(methodsLines);

  in_file.close();

  for (char &c : filename) {
    if (c == '.')
      break;
    fileNameToCreate += c;
  }

  createHeader(_classConfs, out_file, fileNameToCreate);
  createImplementation(_classConfs, out_file, fileNameToCreate);

  return _classConfs.className;
}

void createHeader(const classConfs &_classConfs, ofstream &out_buffer,
                  string filename) {
  string headerName = filename + ".h";

  out_buffer.open(headerName);
  if (!out_buffer.is_open()) {
    cout << "fail trying to make " << headerName << "\n";
  }

  out_buffer << "#ifndef " << stringUpper(_classConfs.className) << "_H\n";
  out_buffer << "#define " << stringUpper(_classConfs.className) << "_H\n\n";

  if (!_classConfs.includes.empty()) {
    for (string include : _classConfs.includes) {
      out_buffer << "#include " << include << "\n";
    }
    out_buffer << "\n";
  }

  out_buffer << "class " << _classConfs.className << "{\n";

  if (!_classConfs.attributes.empty()) {
    out_buffer << "private:\n";
    for (attribute att : _classConfs.attributes) {
      out_buffer << "\t" << att.type << " " << att.name;
      if (att.type.substr(0, 5) == "const") {
        out_buffer << " = {}";
      }
      out_buffer << ";\n";
    }
    out_buffer << "public:\n";
    for (const attribute &att : _classConfs.attributes) {
      addGetAndSet(att, out_buffer, _classConfs.className, true);
    }
  }

  addMethods(_classConfs.methods, out_buffer, _classConfs.className, true);

  out_buffer << "};\n\n#endif";
  out_buffer.close();
}

void createImplementation(const classConfs &_classConfs, ofstream &out_buffer,
                          string filename) {
  filename[0] = toupper(filename[0]);
  string implementationName = filename + ".cpp";

  out_buffer.open(implementationName);
  if (!out_buffer.is_open()) {
    cout << "fail trying to make " << implementationName << "\n";
  }

  out_buffer << "#include \"" << _classConfs.className << ".h\"\n\n";

  if (!_classConfs.attributes.empty()) {
    for (const attribute &att : _classConfs.attributes) {
      addGetAndSet(att, out_buffer, _classConfs.className, false);
      out_buffer << "\n";
    }
  }

  addMethods(_classConfs.methods, out_buffer, _classConfs.className, false);
  out_buffer.close();
}

string getLineByIndex(int index, ifstream &in_buffer) {
  string ret;
  for (int i = 1; i <= index; i++)
    getline(in_buffer, ret);
  return ret;
}

vector<string> getByLine(const string &line) {
  stringstream includes;
  string include;
  vector<string> ret;

  includes << line;
  while (includes >> include)
    ret.push_back(include);

  return ret;
}

string stringUpper(const string &str) {
  string ret = "";
  for (const char &c : str)
    ret += toupper(c);
  return ret;
}

vector<attribute> getAtributesByLine(const string &line) {
  stringstream lineStream;
  vector<attribute> ret;
  attribute to_push;

  lineStream << line;
  while (lineStream >> to_push.type >> to_push.name) {
    setExtra(to_push.type);
    ret.push_back(to_push);
    to_push = {};
  }

  return ret;
}

void addGetAndSet(const attribute &att, ofstream &out_file,
                  const string &className, bool isPrototype) {
  string nameFor = att.name;
  nameFor[0] = toupper(nameFor[0]);

  bool isConst = att.type.substr(0, 5) == "const";

  if (!isConst) {
    if (isPrototype)
      out_file << "\t";
    out_file << "void ";
    if (!isPrototype)
      out_file << className << "::";
    out_file << "set" << nameFor << "(" << att.type;
    if (!isPrototype)
      out_file << " " << att.name;
    out_file << ")";

    if (isPrototype) {
      out_file << ";\n";
    } else {
      out_file << "{\n\tthis->" << att.name << " = " << att.name << ";\n}\n";
    }
  }

  if (isPrototype)
    out_file << "\t";
  out_file << att.type << " ";
  if (!isPrototype)
    out_file << className << "::";
  out_file << "get" << nameFor << "()";
  if (isConst)
    out_file << " const";

  if (isPrototype) {
    out_file << ";\n";
  } else {
    out_file << "{\n\treturn this->" << att.name << ";\n}\n";
  }
}

vector<method> getMethodsByLines(const vector<string> &lines) {
  method metToPush;
  attribute paramToPush;
  vector<method> ret;

  for (string line : lines) {
    stringstream lineStream;
    lineStream << line;
    if (lineStream >> metToPush.ret >> metToPush.name) {
      if (metToPush.ret[0] == '%') {
        metToPush.isConst = true;
        metToPush.ret = metToPush.ret.substr(1, metToPush.ret.size() - 1);
      }
      setExtra(metToPush.ret);

      while (lineStream >> paramToPush.type >> paramToPush.name) {
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

void addMethods(const vector<method> &_methods, ofstream &out_file,
                const string &className, bool isPrototype) {
  for (method _method : _methods) {
    if (isPrototype)
      out_file << "\t";
    out_file << _method.ret << " ";
    if (!isPrototype)
      out_file << className << "::";
    out_file << _method.name << "(";

    for (auto at = _method.params.begin(); at < _method.params.end(); at++) {
      out_file << at->type;
      if (!isPrototype)
        out_file << " " << at->name;
      if (at + 1 != _method.params.end())
        out_file << ", ";
    }
    out_file << ")";

    if (_method.isConst)
      out_file << " const";

    if (isPrototype) {
      out_file << ";\n";
      continue;
    }
    out_file << "{}\n\n";
  }
}

void setExtra(string &str) {
  if ((str[0] == '*' && str[1] == '_') || (str[0] == '_' && str[1] == '*')) {
    str = str.substr(2, str.size() - 2);
    str = "const " + str + '&';
  } else if (str[0] == '*') {
    str = str.substr(1, str.size() - 1);
    str = "const " + str;
  } else if (str[0] == '_') {
    str = str.substr(1, str.size() - 1);
    str = str + '&';
  }
}

void makeModel(string className) {
  ofstream out_buffer;
  string filename = className + ".txt";

  out_buffer.open(filename);
  if (!out_buffer.is_open()) {
    cout << "fail trying to make " << filename << "\n";
    return;
  }

  out_buffer << className << "\n";
  out_buffer << "*ADD INCLUDES HERE / EXAMPLE : <iostream>*\n";
  out_buffer << "*ADD ATTRIBUTES HERE / EXAMPLE : string name int age*\n";
  out_buffer << "*ADD METHODS HERE / EXAMPLE : \nstring toString\n";
  out_buffer
      << "REMEBER: \n_int = int& / *int = const int / *_int = const int&\n";
  out_buffer.close();
}
