/**
 * @file gdate.hpp
 * @brief GDate (Header file)
 *
 * Project 1 - Advanced Data Structures UFC
 *
 * @date Created: May 09, 2023
 * @date Updated: May 26, 2023
 *
 * @author Created by: Gustavo Gurgel Medeiros
 */

#ifndef _GDATE_H_
#define _GDATE_H_

#include <iostream> // Input and output operations
#include <regex>    // Regular expressions

using std::ostream;

// -----{ Typedefs }-----
typedef unsigned int uint;
typedef long long int llint;

/**
 * @brief Class representing a Date (MM/DD/YYYY).
 */
class GDate {
public:
	/**
	 * @brief Default constructor.
	 */
	GDate() = default;

	/**
	 * @brief Constructs a date from a string.
	 *
	 * Validates the passed values to ensure they match a real date.
	 *
	 * @param str String in the expected format (MM/DD/YYYY).
	 */
	GDate(std::string str);

	/**
	 * @brief Sets the date attributes from a string.
	 *
	 * Validates the passed values to ensure they match a real date.
	 *
	 * @param str String in the expected format (MM/DD/YYYY).
	 * @throw std::invalid_argument if the string does not match the date format.
	 */
	void setDate(std::string str);

	/**
	 * @brief Compares two dates.
	 *
	 * @param date1 First date to compare.
	 * @param date2 Second date to compare.
	 * @return int 0 if they are equal, 1 if date1 > date2, and -1 if date1 < date2.
	 */
	static int compareDate(const GDate& date1, const GDate& date2);

	/**
	 * @brief Overload of the insertion operator (<<).
	 *
	 * @param os Output stream.
	 * @param date The date to be outputted.
	 * @return ostream& Reference to the output stream.
	 */
	friend ostream &operator<<(ostream &os, const GDate &date);

	/**
	 * @brief Returns the date as a formatted string.
	 *
	 * @return std::string The date string in MM/DD/YYYY format.
	 */
	std::string toString() const;

	/**
	 * @name Comparison Operators
	 * @brief Overloads for date comparison operators.
	 *
	 * These operators rely on the public static function `compareDate`.
	 * @{
	 */
    bool operator==(const GDate&) const;
    bool operator!=(const GDate&) const;
	bool operator<(const GDate&) const;
	bool operator>(const GDate&) const;
	bool operator<=(const GDate&) const;
	bool operator>=(const GDate&) const;
	/** @} */

private :
	// ---{ Private Attributes }---
	uint day{0};   ///< Day
	uint month{0}; ///< Month
	uint year{0};  ///< Year

	/**
	 * @brief Regular expression that represents a date in the following format:
	 *
	 * MM/DD/YYYY
	 */
	const static std::regex regexDate;
};

#endif
