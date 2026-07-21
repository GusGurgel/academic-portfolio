/**
 * @file main.cpp
 * @brief Balanced Trees (Main file)
 *
 * Project 1 - Advanced Data Structures UFC
 *
 * @date Created: May 08, 2023
 * @date Updated: May 26, 2023
 *
 * @author Created by: Gustavo Gurgel Medeiros
 */

#include "avl.hpp"
#include "gdate.hpp"
#include "person.hpp"
#include "gtable.hpp"

#include <iostream> // Input and output
#include <fstream>  // File reading

using namespace std;

/**
 * @brief Clears the terminal screen.
 *
 * Tested and working on:
 * 1. bash
 * 2. git-bash
 * 3. windows cmd
 */
void clear_terminal();

/**
 * @brief Reads all persons defined in a .csv file and adds them to a vector by reference.
 *
 * In the text file, each person is represented by a line following this model:
 * NationalID,GivenName,Surname,Birthday,City
 *
 * @note This function considers the first line as a header, so it is always ignored.
 *
 * @param filePath Path to the file.
 * @param ref Reference to the vector of persons.
 */
void readCSVFile(const string& filePath, vector<Person>& ref);

/**
 * @brief Reads a text file and puts its entire content into a string.
 *
 * @param path Path to the file.
 * @return string The resulting string containing the file's text.
 */
string readTextFile(const string& path);

/**
 * @brief Checks if a string has a specific prefix.
 *
 * @param prefix The prefix to check.
 * @param str The string being verified.
 * @return true if 'str' starts with 'prefix', false otherwise.
 */
bool isPrefix(const string& prefix, const string& str);

/**
 * @brief Adds the data of a person (stored inside a node) into a table.
 *
 * @tparam T The data type of the node's key.
 * @param node Pointer to the node to be added.
 * @param table Reference to the table object.
 */
template<typename T>
void addNodeOnTable(Node<T>* node, GTable& table);

/**
 * @brief Displays a generic node in a table, including its duplicate values if they exist.
 *
 * @tparam T The data type of the node's key.
 * @param node Pointer to the node.
 * @return uint The number of rows in the table (excluding the header).
 */
template<typename T>
uint showNodeWhitTable(Node<T>* node);

/**
 * @brief Displays a vector of generic nodes formatted as a table.
 *
 * @tparam T The data type of the nodes' keys.
 * @param vec Pointer to the vector of nodes.
 * @return uint The number of rows in the table (excluding the header).
 */
template<typename T>
uint showVecNodeWhitTable(vector<Node<T>*>* vec);

/**
 * @brief Displays a default message for null or empty nodes.
 */
void showNullNode();

// ------- { Interactive Main Functions } ---------

/**
 * @brief Reads a full line from the terminal and returns only the first string (word).
 *
 * @return string The first word from the input line.
 */
string getLineFtsString();

/**
 * @brief Converts a string to a positive integer if it doesn't exceed the provided max value.
 *
 * Places the result in 'ref'. Returns true if the reading/conversion was successful.
 *
 * @param str The string to convert.
 * @param ref Reference to store the converted integer.
 * @param max The maximum allowed value for the conversion.
 * @return true if successful, false otherwise.
 */
bool stringToIntMax(string str, uint& ref, const uint max);

/**
 * @brief Converts a string in National ID (CPF) format into a long long int.
 *
 * @param str The string formatted as an ID.
 * @return llint The numeric representation of the ID.
 */
llint idStringToLLINT(string str);

/**
 * @brief Displays search information inside a table cell.
 *
 * @param info String containing the search information.
 * @param cont The number of search matches found.
 */
void showSearchInfo(const string& info, uint cont);

/**
 * @brief Pauses the execution, waiting for the user to press a key (ENTER).
 */
void menuPause();


int main()
{
	vector<Person> persons;      // Vector containing all persons

	avl_tree<llint> cpfTree;     // Tree for National IDs (CPFs)
	avl_tree<string> nameTree;   // Tree for Names
	avl_tree<GDate> dateTree;    // Tree for Dates

	// Regular expression for National ID
	regex idRegex ("\\d{3}\\.\\d{3}\\.\\d{3}-\\d{2}");

	//------ { Menu Variables Definition } -------

	// Search information string
	string serachInfo;

	// Number of options in the main menu
	const uint mainMenuLen = 5;

	// Indicates if the last terminal reading was successful
	bool readResult = true;

	// Divider shown in the terminal indicating it is waiting for input
	const string terminalDiv = ">>> ";

	// Invalid value message
	const string invalid_menssage = terminalDiv + "[Write a valid value!]";

	// Folder containing menu text files
	const string menuFolder = "menu-files/";

	// File Paths
	const string mainMenuPath = menuFolder + "main-menu.txt";
	const string mainIDPath =  menuFolder + "main-id.txt";
	const string mainBirthPath =  menuFolder + "main-birthday.txt";
	const string mainNamePath =  menuFolder + "main-name.txt";

	// Reading menu files
	const string mainMenuText = readTextFile(mainMenuPath);
	const string mainIDText = readTextFile(mainIDPath);
	const string mainBirthText = readTextFile(mainBirthPath);
	const string mainNameText = readTextFile(mainNamePath);

	//------ { Building the Person Trees } -------

	// Read persons from the CSV file
	readCSVFile("data.csv", persons);

	// Populate the trees
	for(Person& p : persons){
		cpfTree.add(p.getNumNationalID(), &p);
		nameTree.add(p.getFullName(), &p);
		dateTree.add(p.getBirthDay(), &p);
	}

	//----- { Interactive Main Loop } -----

	while(true){
		uint command_idx;  // Command index
		string command;	   // Command string

		// Show main menu
		clear_terminal();
		cout << mainMenuText;

		// If the last reading had an issue
		if(!readResult){
			cout << invalid_menssage << endl;
		}

		cout << terminalDiv;

		// Read command inputted by the user
		command = getLineFtsString();


		// Try conversion with stoi and handle exceptions
		readResult = stringToIntMax(command, command_idx, mainMenuLen);

		// If reading was not successful
		if(!readResult){
			continue;
		}

		/* Search by National ID */
		if(command_idx == 1){
			smatch regexMatch;        // Regular expression search match
			string idToFind;          // ID string to search for
			llint  idNumToFind;		  // Numeric value of the ID
			bool idReadSucess = true; // Read success flag

			// Loop to get correct input value
			while(true){
				clear_terminal();

				// Show the ID menu
				cout << mainIDText;

				// Invalid input handling
				if(!idReadSucess){
					cout << invalid_menssage << endl;
				}

				// Print terminal divider
				cout << terminalDiv;

				// Get first string passed by user
				idToFind = getLineFtsString();

				// Check if exit option was selected
				try{
					if(stoi(idToFind) == 1){
						break;
					}
				}catch(exception const&e){}

				// Search for the ID format
				regex_search(idToFind, regexMatch, idRegex);

				if(regexMatch.empty()){
					idReadSucess = false;
					continue;
				}

				// Get ID as a number
				idNumToFind = idStringToLLINT(idToFind);

				// Clear terminal
				clear_terminal();

				// Search in tree and show the table
				Node<llint>* res = cpfTree.searchNodeByKey(idNumToFind);

				// Show table and get element count
				uint cont = showNodeWhitTable(res);
				cout << endl;

				// Show search info
				serachInfo = "ID searched: " + idToFind;
				showSearchInfo(serachInfo, cont);

				menuPause();
			}
		/* Date Interval Search */
		}else if(command_idx == 2){
			// Informs if the last reading was successful
			bool birthReadSucess = true;

			string dateStr1;
			string dateStr2;
			GDate date1;
			GDate date2;

			// Loop to get correct input value
			while(true){
				// Clear terminal
				clear_terminal();

				stringstream input_stream; // Input stream
				string line;               // Read line

				// Show birthday menu
				cout << mainBirthText << endl;

				if(!birthReadSucess){
					cout << invalid_menssage << endl;
				}

				// Print terminal divider
				cout << terminalDiv;

				// Read line inputted by the user
				getline(cin, line);

				// Extract the first and second dates
				input_stream << line;
				input_stream >> dateStr1;
				input_stream >> dateStr2;

				// Check if exit option was selected
				try{
					// Size must be exactly 1 to avoid
					// conflicting with January dates like 1/1/2023
					if(dateStr1.size() == 1 && stoi(dateStr1) == 1){
						break;
					}
				}catch(exception const &e){}

				try{
					date1 = GDate(dateStr1);
					date2 = GDate(dateStr2);
					// If minimum is greater than maximum
					if(date1 > date2){
						throw invalid_argument("Min date > Max date");
					}
				}catch(exception const& e){
					birthReadSucess = false;
					continue;
				}

				// Clear terminal
				clear_terminal();

				// Get vector with dates in the interval
				vector<Node<GDate>*> res = dateTree.searchNodeByInterval(date1, date2);

				// Show in table format
				uint cont = showVecNodeWhitTable(&res);
				cout << endl;

				// Show search info
				serachInfo = "Date interval: [" + dateStr1 + "] - [" + dateStr2 + "]";
				showSearchInfo(serachInfo, cont);

				// Pause menu
				menuPause();
			}
		/* Name Prefix Search */
		}else if(command_idx == 3){
			string prefix;

			// Reading loop
			while(true){
				// Clear terminal
				clear_terminal();

				// Show name search menu
				cout << mainNameText << endl;

				// Print terminal divider
				cout << terminalDiv;

				// Get the prefix
				getline(cin, prefix);

				try{
					if(stoi(prefix) == 1){
						break;
					}
				}catch(exception const& e){}

				vector<Node<string>*> res = nameTree.searchNodeByPrefix(prefix, isPrefix);

				// Clear terminal
				clear_terminal();

				uint cont = showVecNodeWhitTable(&res);
				cout << endl;

				// Show search info
				serachInfo = "Prefix: \"" + prefix + "\"";
				showSearchInfo(serachInfo, cont);

				menuPause();
			}
		/* Show all registered persons */
		}else if(command_idx == 4){
			// Clear terminal
			clear_terminal();

			// Every name has an empty string as a prefix
			vector<Node<string>*> all = nameTree.searchNodeByPrefix("", isPrefix);

			reverse(all.begin(), all.end());

			// Show the table
			uint cont = showVecNodeWhitTable(&all);
			cout << endl;

			serachInfo = "All persons registered";

			showSearchInfo(serachInfo, cont);

			menuPause();
		/* Exit */
		}else if(command_idx == 5){
			cout << "Exiting..." << endl;
			break;
		}
	}

    return 0;
}

// ------------------------------------
//     { Implementations }
// ------------------------------------

void clear_terminal(){
    printf("\033c");
}

bool isPrefix(const string& prefix, const string& str){
	if(prefix > str){
		return false;
	}

	for(uint i = 0; i < prefix.size(); i++){
		if(prefix[i] != str[i]){
			return false;
		}
	}

	return true;
}

void readCSVFile(const string& path, vector<Person>& vet){
	ifstream in_stream; // Reading buffer
	string line;        // Line read from the file

	// Clear string
	line = "";

	in_stream.open(path);

	getline(in_stream, line); // Header line

	// Check if file opened successfully
	if(in_stream){
		// Add all persons to the vector
		while(getline(in_stream, line)){
			vet.push_back(Person(line));
		}
	}else{
		// Exception when trying to open the file
		throw invalid_argument("Problem trying to read file or " + path + " not exists");
	}

	// Close the file
	in_stream.close();
}

string readTextFile(const string& path){
	ifstream in_stream; // Reading buffer
	string line;        // Line read from the buffer
	string ret; 		// Return string

	// Clear strings
	line = ret = "";

	in_stream.open(path);

	if(in_stream){
		// Add all lines to the string
		while(getline(in_stream, line)){
			// Add line and line break
			ret += (line + "\n");
		}
	}else{
		// Exception when trying to open the file
		throw invalid_argument("Problem trying to read file or " + path + " not exists");
	}

	return ret;
}

template<typename T>
void addNodeOnTable(Node<T>* node, GTable& table){
	Person* p = node->toPerson;

	// Adding person from the node to the table
	table.addRow(vector<string> {p->getNationalID(), p->getGivenName(), p->getSurname(), p->getBirthDayString(), p->getCity()});

	// Adding duplicate values
	if(node->dupes != nullptr){
		for(Node<T>* dupe : (*node->dupes)){
			Person* pd = dupe->toPerson;
			table.addRow(vector<string> {pd->getNationalID(), pd->getGivenName(), pd->getSurname(), pd->getBirthDayString(), pd->getCity()});
		}
	}
}

template<typename T>
uint showNodeWhitTable(Node<T>* node){
	// If node is null
	if(node == nullptr){
		showNullNode();
		return 0;
	}

	// Create a table
	GTable table(1);

	// Header
	table.addRow(vector<string> {"National ID", "Given Name", "Surname", "Birthday", "City"});

	// Add node to the table
	addNodeOnTable(node, table);

	table.show();

	// -1 to disregard the header row
	return table.getRowSize() - 1;
}

template<typename T>
uint showVecNodeWhitTable(vector<Node<T>*>* vec){
	// If vector is null or empty
	if(vec == nullptr || vec->size() == 0){
		showNullNode();
		return 0;
	}

	// Create a table
	GTable table(1);

	// Header
	table.addRow(vector<string> {"National ID", "Given Name", "Surname", "Birthday", "City"});

	// Add all nodes
	for(Node<T>* node : (*vec)){
		addNodeOnTable(node, table);
	}

	table.show();

	// -1 to disregard the header row
	return table.getRowSize() - 1;
}

void showNullNode(){
	GTable table(1);

	const string text = "No matches found";
	table.addRow(vector<string> {text});

	table.show();
}

// ------- { Interactive Main Functions } ---------

string getLineFtsString(){
	stringstream ss; // String stream
	string line;     // Line read from terminal
	string ret;      // Return string

	getline(cin, line);

	ss << line;
	ss >> ret;

	return ret;
}

bool stringToIntMax(string str, uint& ref, const uint max){
	try{
		// Try to convert
		ref = stoi(str);
		// Conversion successful
		if(ref > 0 && ref <= max){
			return true;
		// Value out of bounds
		}else{
			throw invalid_argument("Option out of range");
			return false;
		}
	}catch(exception const& e){
		// Invalid string value
		return false;
	}
}

llint idStringToLLINT(string str){
	return stoll(getStringWithout(str, "-."));
}

void menuPause(){
	cout << " (Press ENTER) >>> ";
	cin.get();
}

void showSearchInfo(const string& str, uint cont){
	GTable table(1);
	string matchesInfo = "Number of Matches: " + to_string(cont);
	table.addRow(vector<string>{str, matchesInfo});
	table.show();
	cout << endl;
}
