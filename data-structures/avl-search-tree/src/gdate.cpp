/**
 * @file gdate.cpp
 * @brief GDate (Implementation file)
 *
 * Project 1 - Advanced Data Structures UFC
 *
 * @date Created: May 09, 2023
 * @date Updated: May 26, 2023
 *
 * @author Created by: Gustavo Gurgel Medeiros
 */

#include "gdate.hpp"
#include <iomanip>

//------------------------------------
//   { Destructors and Constructors }
//------------------------------------

GDate::GDate(std::string str){
	setDate(str);
}

//----------------------------
//   { Public Methods }
//----------------------------
void GDate::setDate(std::string str){
	std::smatch regexMatch; // Receives the search results

	// Searches for the regular expression within the string
	std::regex_search(str, regexMatch, GDate::regexDate);

	// Handles invalid date format cases
	if(regexMatch.empty()){
		throw std::invalid_argument("Invalid date string \"" + str + "\"");
	}else{
		this->month = stoi(regexMatch.str(1)); // Group 1 is the month
		this->day   = stoi(regexMatch.str(2)); // Group 2 is the day
		this->year  = stoi(regexMatch.str(3)); // Group 3 is the year
	}
}

int GDate::compareDate(const GDate& date1, const GDate& date2){
	if (date1.year != date2.year) {
    	return (date1.year < date2.year) ? -1 : 1;
	} else if (date1.month != date2.month) {
		return (date1.month < date2.month) ? -1 : 1;
	} else if (date1.day != date2.day) {
		return (date1.day < date2.day) ? -1 : 1;
	} else {
		// If none of the conditions are met, the dates are identical
		return 0;
	}
}

std::string GDate::toString() const{
	std::stringstream ss;

	ss << *(this);

	return ss.str();
}

//-----------------------------------
//   { Operator Overloads }
//-----------------------------------

ostream &operator<<(ostream &os, const GDate &date) {
	os << std::setfill('0') << std::setw(2) << date.month << "/";
	os << std::setw(2) << date.day << "/";
	os << std::setw(4) << date.year;
	return os;
}

bool GDate::operator==(const GDate& dateCopared) const{
	// Uses the 'this' pointer to pass the reference
	return (GDate::compareDate(*(this), dateCopared) == 0);
}

bool GDate::operator!=(const GDate& dateCopared) const{
	// Uses the 'this' pointer to pass the reference
	return (GDate::compareDate(*(this), dateCopared) != 0);
}

bool GDate::operator<(const GDate& dateCopared) const{
	return (GDate::compareDate(*(this), dateCopared) == -1);
}

bool GDate::operator>(const GDate& dateCopared) const{
	return (GDate::compareDate(*(this), dateCopared) == 1);
}

bool GDate::operator<=(const GDate& dateCopared) const{
	return (GDate::compareDate(*(this), dateCopared) == 0) || (GDate::compareDate(*(this), dateCopared) == -1);
}

bool GDate::operator>=(const GDate& dateCopared) const{
	return (GDate::compareDate(*(this), dateCopared) == 0) || (GDate::compareDate(*(this), dateCopared) == 1);
}

//----------------------------
//   { Private Methods }
//----------------------------
// const std::regex GDate::regexDate ("(\\d{1,2})\\/(\\d{1,2})\\/(\\d{4})");
const std::regex GDate::regexDate ("([0][1-9]|[1][0-2]|[1-9])\\/([3][0-1]|[0-2]\\d|\\d)\\/(\\d{4})");
