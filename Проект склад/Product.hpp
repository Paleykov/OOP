/** @file Product.hpp
 *  @brief A class for the product objects
 *  
 *  @author Georgi Paleykov, 0MI0800195, Computer Science, Group 4
 */

#pragma once
#include <iostream>
#include <string>
#include "Dates.hpp"
#include "MetricType.hpp"
#include "Position.hpp"

/**
 * @class Product
 */
class Product
{
    private:
    std::string ProductName; //!< String with the name of the product
    Date ExpDate; //!< A date object for the expiration date
    Date ArrDate; //!< A date object for the arrival date
    std::string ManufacturerName; //!< String with the product's manufacturer name
    Metric Type; //!< The metric type of the the product (ENUM class object)
    double volume; //!< A double for the volume of the product
    std::string Comment; //!< String that contains a comment for the product
    Position position; //!< A position object that contains the location for the product

    public:
    //! A default constructor
    Product();

    //! A constructor for a product object with all of its components
    Product(const std::string& ProductName, const Date& ExpDate, const Date& ArrDate, 
    const std::string& ManufacturerName, const Metric& Type, const double& volume, 
    const std::string& Comment, const Position& other); 
    
    //! Operator += for volume of products with matching expiration dates
    Product &operator +=(const Product& other);

    //! Operator -= for volume of products with matching expiration dates
    Product &operator -=(const Product& other); 

    //! Getter that returns the name of the product
    const std::string& getProductName() const;

    //! Getter that returns the expiration date of the product 
    const Date& getExpDate() const;

    //! Getter that returns the arrival date of the product 
    const Date& getArrDate() const;

    //! Getter that returns the product's manufacturer name
    const std::string& getManufacturerName() const;

    //! Getter that returns the metric type of the product
    const Metric& getType() const; 

    //! Getter that returns the volume of the product
    const double& getVolume() const;

    //! Getter that returns the comment of the product
    const std::string& getComment() const;

    //! Getter that returns the position of the product 
    const Position& getPosition() const; 

    //! Setter for the product's position
    void setPosition(const Position& other);

    //! Setter for the product's volume 
    void setVolume(const double& volume); 

    //! Operator << that manages the info in the format picked by me
    friend std::ostream& operator << (std::ostream& out, const Product& other);

    //! Operator + for volume of products with matching expiration dates
    friend Product operator +(const Product& lhs, const Product& rhs); 

    //! Operator - for volume of products with matching expiration dates
    friend Product operator -(const Product& lhs, const Product& rhs); 

    //! Print function for the products
    void Print() const; 
};