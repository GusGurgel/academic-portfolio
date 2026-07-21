/**
 * @file gtable.hpp
 * @brief GTable (Header file)
 *
 * Project 1 - Advanced Data Structures UFC
 *
 * @date Created: May 21, 2023
 * @date Updated: May 26, 2023
 *
 * @author Created by: Gustavo Gurgel Medeiros
 */

#ifndef _GTABLE_H_
#define _GTABLE_H_

#include <iostream>  // Input and output
#include <vector>    // Vectors

#include "gdate.hpp" // For typedef uint

using std::string;
using std::cout;
using std::endl;
using std::vector;

/**
 * @brief Prints a string repeatedly to the terminal.
 *
 * @param str The string to be repeated.
 * @param times The number of times to repeat the string.
 */
void showRepeat(string str, int times);

/**
 * @brief Returns a new string created by repeating another string.
 *
 * @param str The string to be repeated.
 * @param times The number of times to repeat the string.
 * @return string The resulting repeated string.
 */
string strRepeat(string str, int times);

/**
 * @brief Returns a centered string padded with spaces to match a specific length.
 *
 * Empty spaces are added to the left and right of the original string
 * to center it within the given length.
 *
 * @note Example:
 * Parameters: str = "gustavo", length = 10
 * Return: " gustavo  "
 *
 * @param str The string to be padded.
 * @param length The expected total length of the string.
 * @return string The padded and centered string.
 */
string fillString(string str, uint length);

/**
 * @brief Calculates the actual length of a UTF-8 string.
 *
 * This function resolves issues with string lengths containing special
 * characters and accents. For example, using the standard string `size()`
 * method on "Mário" returns 6 because the character 'á' is counted as two
 * separate characters. This function handles UTF-8 properly and returns 5.
 *
 * @param str The string to calculate the length of.
 * @return uint The actual character count of the string.
 */
uint strLenght(string str);

/**
 * @brief Struct representing the visual style of a table.
 *
 * This structure allows for aesthetic modifications in how
 * tables are rendered and displayed in the terminal.
 */
struct tableStyle{
    string horizontalLine;
    string verticalLine;

    string leftUpEdge;
    string leftDownEdge;

    string rightUpEdge;
    string rightDownEdge;

    string leftUpDownEdge;
    string rightUpDownEdge;

    string leftRightDownEdge;
    string leftRightUpEdge;

    string fullEdge;
};

/**
 * @brief Class for drawing formatted tables in the terminal.
 */
class GTable {
public:
    /**
     * @brief Constructs a new GTable object.
     *
     * @param padding The internal spacing (padding) for the table cells.
     */
    GTable(uint padding);


    /**
     * @brief Adds a row to the table.
     *
     * Each row in the table is represented by a vector of strings
     * of varying sizes.
     *
     * @param row A vector of strings representing the columns of the row.
     */
    void addRow(vector<string> row);

    /**
     * @brief Displays the table in the terminal.
     */
    void show();

    /**
     * @brief Retrieves the number of rows currently in the table.
     *
     * @return uint The row count.
     */
    uint getRowSize();

private:
    tableStyle sty;               ///< Visual style of the table
    uint tableMaxLength;          ///< Maximum length among all rows
    int padding;                  ///< Cell padding

    vector<vector<string>> table; ///< Table data (matrix of strings)
    vector<uint> lengths;         ///< Array storing the max width of each column

    /**
     * @brief Draws the top border line of the table.
     */
    void showTopLine();

    /**
     * @brief Draws the connection line between rows.
     */
    void showConnectLine();

    /**
     * @brief Draws the middle section (data cells) of the table.
     */
    void showMiddle();

    /**
     * @brief Draws the bottom border line of the table.
     */
    void showDownLine();
};

#endif
