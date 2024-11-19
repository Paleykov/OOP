/** @file Storage.hpp
 *  @brief A class for managing an array of pointers of Product objects
 *  
 *  @author Georgi Paleykov, 0MI0800195, Computer Science, Group 4
 */

#pragma once
#include "Product.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

/**
 * @class Storage
 */
class Storage
{
    private:
    Product** products; //!< An array of pointers of Product objects
    int size; //!< The size of the Product objects array
    int capacity; //!< The capacity of the Product objects array

    //! Function to copy from another object of Storage type
    void copyFrom(const Storage& other); 

    //! Function to resize the Product objects array of pointers
    void resize(const int& newCapacity); 

    public:

    //! A default constructor
    Storage(); 

    //! A copy constructor
    Storage(const Storage& other); 

    //! A destructor
    ~Storage(); 

    //! Operator =
    Storage &operator=(const Storage& other);

    //! A function for memory deallocation 
    void deallocate(); 

    //! Getter that returns the array size
    const int& getSize() const;

    //! Getter that returns the capacity size
    const int& getCapacity() const;

    //! Getter that returns the array itself 
    Product** getProducts() const; 

    //! A function that swaps 2 elements in the array
    void swap(Product* lhs, Product* rhs);

    //! Bubble sort that sorts the objects in the array by expiration date
    void bubbleSort(); 

    //! Bubble sort that sorts the objects in the array by product name
    void bubbleSortByProductName();

    //! A function that returns the total volume of products at a given position in the storage
    double volumeAtPosition(const Position& position); 

    //! A bool function to check if a given position matches another position of a product object from the array
    bool HasMatchingPosition(const Position& position);  

    //! A function that prints in the console the volumes and expiration dates of all products with the given name
    void ShowWhatIsAvailableByName(const std::string& name); 

    //! A function that adds a new product object in the pointer array
    void addProduct(Product* NewProduct); 

    //! A function removes a product object in the pointer array by index
    void removeProduct(const int& index); 

    //! A function that prints the whole information about the objects in the array (additional function for print)
    void PrintWholeThing();

    //! A function that prints only the volume and name of objects in the array (the print as desired in the description of the task)
    void printVolAndNameOnly(); 

    //! A function that calls the printVolAndNameOnly function
    void print(); 

    //! Operator << that manages the info in the format picked by me
    friend std::ostream& operator << (std::ostream& out, const Storage& data);

    //! Operator >> that manages the info in the format picked by me
    friend std::istream& operator >> (std::istream& out, Storage& other); 
};
