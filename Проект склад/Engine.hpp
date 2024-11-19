/** @file Engine.hpp
 *  @brief A singleton class that combines all other classes
 *  
 *  @author Georgi Paleykov, 0MI0800195, Computer Science, Group 4
 */

#include "CommandReader.hpp"
#include "Commands.hpp"
#include "Dates.hpp"
#include "Position.hpp"
#include "Product.hpp"

/**
 * @class Engine
 */

class Engine
{
    private:
    Commands storage; //!< A commands object that combines a LogArray and Storage object and handles their commands
    std::string currentFileName; //!< A string that contains the current file name
    bool stopProgram; //!< Bool that checks if the program stops
    bool fileIisOpen; //!< Bool that checks if a file is open

    //! A default constructor for the engine singleton class
    Engine();

    //! A function that removes all blank spaces
    void removeSpaces(std::string& string);

    //! A function that turns the letters in a string to lower
    std::string stringToLower(std::string string);

    //! A function with validations that adds a product by data in a dialogue mode with the user
    void add();

    //! A function that prints all the available commands for the user
    void printHelp(); 

    //! A function that opens a file and extracts its contents into the memory before closing it
    void Open(std::string name);

    //! A function that stops the program
    void Exit(); 

    //! A function that saves the file in a given directory (main file if the user selects only "save")
    void SaveFile(const std::string filename); 

    //! A function that checks if the input command is valid
    bool isCommandValid(CommandReader command); 

    //! A function that checks if the input file name and format are valid
    bool isValidFilename(const std::string& filename); 

    //! A function that checks if a character is a number
    bool CharIsNum(char ch); 

    //! A function that checks if a string is a number
    bool isNumber(std::string string);

    //! A function that checks if a string that is suppossed to be a date is in the correct DD.MM.YYYY format
    bool DateIsNumber(const std::string& date);

    //! A function that checks if a string that is contains a date in the format DD.MM.YYYY is a real, correct date 
    bool DateIsValid(const std::string& date);

    //! A function that converts a character to a number
    int ConvertFromCharToNum(const char& a);

    //! A function that combines all the other date check function and outputs whether a string that is suppossed to contain a date is correct
    bool CheckData(const std::string& other); 

    //! A helper function that makes the name for the log file that corresponds to a storage file
    std::string NameOfLog(const std::string& name);

    //! A function that closes the currently open file
    void Close(); 

    //! A function that checks if a file with a given name exists in the directory
    bool fileExists(std::string filename); 

    //! A function that checks if a file is new
    bool isNewFile(const std::string& filename);
    
    public: 
    //! Deleted copy constructor since the engine class is a singleton
    Engine(const Engine& other) = delete;

    //! Deleted operator = since the engine class is a singleton
    Engine& operator = (const Engine& other) = delete; 

    //! A function that creates an instance of the singleton class "Engine"
    static Engine& getInstance(); 

    //! A function that executes a command based on the user input
    void DoCommand(CommandReader command);

    //! The function that runs the program until the user exits the program
    void Exe(); 
};