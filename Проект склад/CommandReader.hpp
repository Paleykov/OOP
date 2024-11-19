/** @file CommandReader.hpp
 *  @brief A class that manages the command input by the user and breaks it down into smaller parts that are easier to work with
 *  @note This command reader was shown during OOP practicum by Peter Kolev - assistent for group 4
 * 
 *  @author Georgi Paleykov, 0MI0800195, Computer Science, Group 4
 */

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

/**
 * @class CommandReader
 */
class CommandReader
{
    private:
    std::vector<std::string> command; //!< An array of string (using vector) that contains the arguments of the command

    //! A function that counts the number of closing symbols -> "
    int NumberOfClosingSymbols(std::string string);

    //! A function that converts all characters of a string to lower
    std::string stringToLower(std::string string);

    //! A function that removes blank spaces from arguments
    void removeSpaces(std::string& string); // POMOSHT OT ASISTENT, CREDIT: PETER KOLEV

    //! A function that removes empty arguments
    void removeEmptyArgs(std::vector<std::string>& arguments);

    public:

    //! A constructor for the command that takes a string
    CommandReader(std::string command);
    
    //! A function that returns the number of arguments
    int getNumberOfArgs() const;

    //! A function that combines all the other functions to manage the command
    void CommandReaderFunction(std::string command); // POMOSHT OT ASISTENT, CREDIT: PETER KOLEV
    
    //! A function that returns an argument at a given index
    std::string& operator [] (std::size_t index);

    //! A function that returns an argument at a given index
    const std::string& operator [] (std::size_t index) const; 

};