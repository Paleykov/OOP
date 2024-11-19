/** @file Dates.hpp
 *  @brief A class that defines dates in the format DD.MM.YYYY
 *  
 *  @author Georgi Paleykov, 0MI0800195, Computer Science, Group 4
 */

#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

/**
 * @class Date
 */
class Date
{
    private:
    std::string data;//!< A string that contains the date

    public:
    //! A default constructor
    Date();

    //! A constructor for a Date object that takes a string
    Date(const std::string data);
    
    //! Getter that returns the date string
    const std::string& getData() const;

    //! Setter for the date string
    void setData(const std::string& other);

    //! A helper function to get today's date
    void setCurrDate();

    //! A function that checks if a character is a number
    bool CharIsNum(const char& a);

    //! A function that checks if a string that contains a date is in the correct DD.MM.YYYY format
    bool DateIsNumber(const std::string& date);

    //! A function that checks if a string that contains a date is a real, correct date
    bool DateIsValid(const std::string& date); 

    //! A function that converts a char to a number
    int ConvertFromCharToNum(const char& a) const;  

    //! A function that combines all the date checker functions and tells if a string that is suppossed to contain a date is correct
    bool CheckData(const std::string& date); 

    //! Operator > for comparison of dates
    bool operator > (const Date& other) const;

    //! Operator == for comparison of dates
    bool operator ==(const Date& other) const;

    //! Operator != for comparison of dates
    bool operator !=(const Date& other) const; 

    //! Operator >= for comparison of dates
    bool operator >=(const Date& other) const; 

     //! Standart << operator that manages the info in the format picked by me
    friend std::ostream& operator << (std::ostream& out, const Date& data);

    //! Standart >> operator that manages the info in the format picked by me
    friend std::istream& operator >> (std::istream& in,  Date& data);

    //! A friend operator - function to see the difference in days between 2 dates 
    friend int operator -(const Date& lhs, const Date& rhs); 

    //! A function that prints the date
    void PrintData() const;
};