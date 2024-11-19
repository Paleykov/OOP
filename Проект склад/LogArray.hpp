/** @file LogArray.hpp
 *  @brief A class for managing an array of pointers of log objects
 *  
 *  @author Georgi Paleykov, 0MI0800195, Computer Science, Group 4
 */

#pragma once

#include "Log.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include "Dates.hpp"

/**
 * @class LogArray
 */

class LogArray
{
    private:
    Log** logs; //!< An array of pointers of Log objects
    int size; //!< The size of the Log objects array
    int capacity; //!< The capacity of the Log objects array

    //! Function to copy from another object of LogArray type
    void copyFrom(const LogArray& other);

    //! Function to resize the LogArray array of pointers
    void resize(const int& newCapacity); 

    public:
    //! A default constructor
    LogArray(); 

    //! A copy constructor
    LogArray(const LogArray& other);

    //! A destructor
    ~LogArray(); 

    //! A function for memory deallocation
    void deallocate();

    //! Operator =
    LogArray &operator=(const LogArray& other); 

    //! Getter that returns the array size
    const int& getSize() const;

    //! Getter that returns the capacity size
    const int& getCapacity() const;

    //! Getter that returns the array itself 
    Log** getLogs() const;

    //! A function that adds a new Log object in the pointer array
    void addLog(Log* newLog);

    //! A function prints the contents of the log array 
    void print(); 

    //! A function prints the contents of the log array in a given time period
    void printWithDates(const Date& from, const Date& to);

    //! A function that sorts the log array by the log dates of the products 
    void sortByDates();

    //! Operator << that manages the info in the format picked by me
    friend std::ostream& operator << (std::ostream& out, const LogArray& data);

    //! Operator >> that manages the info in the format picked by me 
    friend std::istream& operator >> (std::istream& out, LogArray& other); 
};
