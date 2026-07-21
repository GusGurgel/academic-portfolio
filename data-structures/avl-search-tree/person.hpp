/**
 * @file person.hpp
 * @brief Person Class (Header file)
 *
 * Project 1 - Advanced Data Structures UFC
 *
 * @date Created: May 11, 2023
 * @date Updated: May 26, 2023
 *
 * @author Created by: Gustavo Gurgel Medeiros
 */

#ifndef _PERSON_H_
#define _PERSON_H_

#include "gdate.hpp"// Dates

#include <string>   // Strings
#include <regex>    // Regular expressions

using std::string;

/**
 * @brief Removes specific characters from a string.
 *
 * @param str The original string.
 * @param toRemove A string containing all the characters that should be removed.
 * @return string The resulting string without the specified characters.
 */
string getStringWithout(const string& str, const string& toRemove);

/**
 * @brief Draws a line in the terminal.
 *
 * @param length The length of the line (default is 30).
 */
void makeLine(uint length = 30);

/**
 * @brief Class representing a Person.
 */
class Person{
public:
    /**
     * @brief Default constructor.
     */
    Person() = default;

    /**
     * @brief Constructs a person from a string.
     *
     * Validates the passed values.
     *
     * @param str String in the expected format.
     */
    Person(string str);

    /**
     * @brief Sets the person's attributes from a string.
     *
     * Validates the passed values.
     *
     * @param str String in the expected format.
     * @throw std::invalid_argument if the string format is invalid.
     */
    void setPerson(string str);

    /**
     * @brief Displays a person in a more readable format in the console.
     */
    void show() const;

    /**
     * @brief Overload of the insertion operator (<<).
     *
     * @param os Output stream.
     * @param person The person object to be outputted.
     * @return ostream& Reference to the output stream.
     */
	friend ostream &operator<<(ostream &os, const Person &person);

    /**
     * @name Getters
     * @brief Methods to retrieve Person attributes.
     * @{
     */
    string getNationalID() const;
    string getGivenName() const;
    string getSurname() const;
    string getCity() const;
    string getFullName() const;
    string getBirthDayString() const;
    llint getNumNationalID() const;
    GDate getBirthDay() const;
    /** @} */

private:
    // ---{ Private Attributes }---
    string nationalID;
    string givenName;
    string surname;
    GDate birthday;
    string city;

    /**
     * @brief Regular expression representing a Person in the following format:
     *
     * "NationalID,GivenName,Surname,Birthday,City"
     */
    const static std::regex regexPerson;
};

#endif
