/** @file Log.hpp
 *  @brief A class for the log objects for each product
 *  
 *  @author Georgi Paleykov, 0MI0800195, Computer Science, Group 4
 */


#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "LogAction.hpp"
#include "Dates.hpp"

/**
 * @class Log
 */
class Log
{
    private:
    Action type; //!< The action that was performed on the product
    std::string ProductName; //!< String with the name of the product
    Date DateOfLog; //!< A date object for the date of the action
    double quantity; //!< Double for the volume of the product

    public:
    //! A default constructor
    Log(); 

    //! A constructor for a log object with all of its components
    Log(const Action& type, const std::string& ProductName, const Date& date, const double& quantity); 

    //! Getter that returns the name of the product 
    const std::string& getProductName() const; 

    //! Getter that returns the type of action that was performed on the product
    const Action& getType() const; 

    //! Getter that returns the volume of the product
    const double& getQuantity() const;

    //! Getter that returns the date of the action 
    const Date& getDateOfLog() const;

    //! Setter for the product's name
    void setProductName(const std::string& ProductName);

    //! Setter for the product's volume
    void setQuantity(const double& quantity);

    //! Setter for the action performed on the product
    void setType(const Action& type);

    //! Setter for date of the action performed on the product
    void setDateOfLog(const Date& date); 

    //! Operator << that manages the info in the format picked by me
    friend std::ostream& operator << (std::ostream& out, const Log& other); 
};