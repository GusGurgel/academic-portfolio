/**
 * @file person.cpp
 * @brief Person Class (Implementation file)
 *
 * Project 1 - Advanced Data Structures UFC
 *
 * @date Created: May 11, 2023
 * @date Updated: May 26, 2023
 *
 * @author Created by: Gustavo Gurgel Medeiros
 */
#include "person.hpp"

#include <iostream> // Input and output operations

//------------------------------------
//   { Constructors and Destructors }
//------------------------------------

Person::Person(string str){
    this->setPerson(str);
}

//----------------------------
//   { Public Methods }
//----------------------------

void Person::setPerson(string str){
    std::smatch regexMatch;

    std::regex_search(str, regexMatch, Person::regexPerson);

    if(regexMatch.empty()){
        throw std::invalid_argument("Invalid person string \"" + str + "\"");
    }else{
        this->nationalID = regexMatch.str(1);
        this->givenName  = regexMatch.str(2);
        this->surname    = regexMatch.str(3);
        this->city       = regexMatch.str(5);
        this->birthday.setDate(regexMatch.str(4));
    }
}

void Person::show() const{
    makeLine();
    std::cout << "NationalID: " << nationalID << std::endl;
    std::cout << "Full name: "  << (givenName + " " + surname) << std::endl;
    std::cout << "Birthday: "   << birthday << std::endl;
    std::cout << "City: "       << city << std::endl;
    makeLine();
}

ostream &operator<<(ostream &os, const Person &person) {
	os << "NationalID: " << person.getNationalID() << "; Name: " << person.getFullName() << " ; Birthday: " << person.getBirthDay() << " ; City: " << person.getCity() << ";";
	return os;
}

//----------------------------
//   { Private Attributes }
//----------------------------

const std::regex Person::regexPerson("(\\d{3}\\.\\d{3}.\\d{3}-\\d{2}),(.*),(.*),(\\d{1,2}\\/\\d{1,2}\\/\\d{4}),(.*)");


//----------------------------
//      { Getters }
//----------------------------

string Person::getNationalID() const{
    return this->nationalID;
}

llint Person::getNumNationalID() const{
	// The '-' and '.' are removed from the string,
	// and then it is converted to a long long int
    // using the stoll function.
    return stoll(getStringWithout(this->getNationalID(), "-."));
}

string Person::getGivenName() const{
    return this->givenName;
}

string Person::getSurname() const{
    return this->surname;
}

GDate Person::getBirthDay() const{
    return this->birthday;
}

string Person::getCity() const{
    return this->city;
}

string Person::getFullName() const{
    return (getGivenName() + " " + getSurname());
}

string Person::getBirthDayString() const{
    return birthday.toString();
}

//----------------------------
//   { Helper Functions }
//----------------------------

void makeLine(uint length){
    for(uint i = 0; i < length; i++){
        std::cout << "-";
    }
    std::cout << std::endl;
}

string getStringWithout(const string& str, const string& toRemove){
	bool canAdd; // Indicates if the character can be added to the return string
	string ret = "";
	for(const char& c : str){
		canAdd = true; // Assume it can be added
		for(const char& r : toRemove){
			// The character matches one in toRemove, so it cannot be added
			if(c == r){
				canAdd = false;
				break;
			}
		}
		if(canAdd)
			ret += c;
	}
	return ret;
}
