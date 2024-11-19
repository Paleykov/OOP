/** @file Position.hpp
 *  @brief A class for the position of the products
 *  
 *  @author Georgi Paleykov, 0MI0800195, Computer Science, Group 4
 */

#pragma once
#include <iostream>
#include <string>

/**
 * @class Position
 */
class Position
{
    private:
    int section; //!< An int for the number of the product's secion
    int shelf; //!< An int for the number of the product's shelf
    int number; //!< An int for the number of the product's place on the shelf

    public:

    //! A default constructor
    Position(); 

    //! A constructor for a position object with all of its components
    Position(const int& section, const int& shelf, const int& number); 
    
    //! Getter that returns section number
    const int& getSection() const;

    //! Getter that returns shelf number 
    const int& getShelf() const; 

    //! Getter that returns the number on the shelf
    const int& getNumber() const; 

    //! Setter for the product's section number
    void setSection(const int& section);

    //! Setter for the product's shelf number
    void setShelf(const int& shelf); 

    //! Setter for the product's number on the shelf
    void setNumber(const int& number); 

    //! A function that validates the position of the product
    bool positionIsValid() const; 

    //! Operator == for comparing 2 positions
    bool operator ==(const Position& other) const; 

    //! Operator != for comparing 2 positions
    bool operator !=(const Position& other) const; 

    //! Function that prints the position of the product
    void print() const;

    //! Operator << that manages the info in the format picked by me
    friend std::ostream& operator << (std::ostream& out, const Position& other);   
};