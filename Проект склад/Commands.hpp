/** @file Commands.hpp
 *  @brief A class that combines the storage array of products and the array of logs for each product in one
 *  
 *  @author Georgi Paleykov, 0MI0800195, Computer Science, Group 4
 */

#pragma once

#include "Storage.hpp"
#include "LogArray.hpp"

/**
 * @class Commands
 */
class Commands
{
    private:
    Storage storage; //!< A Storage object that contains an array of pointers of product objects
    LogArray log; //!< A LogArray object that contains an array of pointers of log objects

    public:

    //! A default constructor
    Commands();

     //! A constructor with other Storage object and other LogArray object
    Commands(const Storage& otherStorage, const LogArray& otherLog);
    
    //! A function that removes all products in the storage array that match the given name and logs the actions of removal
    void DeleteAllWithName(const std::string& name);

    //! A function that removes from the products in the storage array with matching name if the user volume input is less or equal to the total of the products with that name
    void RemoveProductsIfVolIsLessThanTotalVol(const double& volume, const std::string& name);

    //! A function that removes a given volume or the whole amount of products from the storage array if the product has a matching name 
    void removeProductByNameAndVol(const std::string& name, const double& volume); 

    //! Clears products that will expire soon (IN 3 DAYS) or have already expired
    void clearProducts(); 

    //! Fills the available space of products when adding a product with a matching name and expiration date to one that is already in the storage array
    bool FillAvailableSpaces(Product& newProduct);

    //! Adds a product by data and manages the positions if volume is more than what can be stored in one place 
    void addProductByData(Product& newProduct); 

    //! A getter that returns the storage object
    Storage getStorage();

    //! A getter that returns the LogArray object
    LogArray getLogArray(); 

    //! A print function that shows the log for a given period of time
    void ShowLog(const Date& from, const Date& to); 

    //! A function that shows the losses from expired cleared products based on the price of the product per kg/litre
    void ShowLosses(const std::string& name, const double& price, const Date& from, const Date& to); 

    //! A function that prints the storage contents by name and volume
    void print();

    //! A function that prints the whole information about the storage contents 
    void printWholeThing(); 
};