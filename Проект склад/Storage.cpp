#include "Storage.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <stdexcept>

void Storage::deallocate()
{
    for(int i = 0; i<this->size; i++)
    delete this->products[i];
    delete[] this->products;
}

void Storage::copyFrom(const Storage& other)
{
    this->products = new Product*[other.capacity];
    if(!this->products)
    {
        std::cout << "Problem allocating memory" << std::endl;
        return;
    }

    for(int i = 0; i< other.size; i++)
    {
        this->products[i] = new Product(*other.products[i]);
    }

    this->capacity = other.capacity;
    this->size = other.size;
}

void Storage::resize(const int& newCapacity)
{
    this->capacity = newCapacity;
    Product** ProductBuffer = new Product*[newCapacity];
    
    if(!ProductBuffer)
    {
        throw std::bad_alloc();
    }
    
    for(int i = 0; i < this->size; i++)
    {
        ProductBuffer[i] = this->products[i];
    }

    delete[] this->products;
    this->products = ProductBuffer;
}

Storage::Storage(): size(0), capacity(4)
{
    this->products = new Product*[this->capacity];
    if(!this->products)
    {
        throw std::bad_alloc();
    }
}

Storage::Storage(const Storage& other)
{
    copyFrom(other);
}

Storage::~Storage()
{
    deallocate();
}

Storage &Storage::operator=(const Storage& other)
{
    if(this!=&other)
    {
        this->deallocate();
        copyFrom(other);
    }

    return *this;
}

const int& Storage::getSize() const
{
    return this->size;
}

const int& Storage::getCapacity() const
{
    return this->capacity;
}

Product** Storage::getProducts() const
{
    return this->products;
}

void Storage::addProduct(Product* NewProduct)
{
    if(this->size == this->capacity)
    resize(this->capacity*2);

    this->products[this->size++] = NewProduct;
}

double Storage::volumeAtPosition(const Position& position)
{
    double volumeAtPos = 0;
    for(int i = 0; i< this->size; i++)
    {
        if(this->products[i]->getPosition() == position)
        volumeAtPos += this->products[i]->getVolume();
    }
    return volumeAtPos;
}

bool Storage::HasMatchingPosition(const Position& position)
{
    if(this->size == 0)
    return false;

    for(int i  = 0; i<this->size; i++)
    {
        if(this->products[i]->getPosition() == position)
        {
            return true;
            break;
        }
    }
    return false;
}

void Storage::removeProduct(const int& index)
{
    if(this->size == 0)
    {
        std::cout << "No more products, cannot remove" << std::endl;
        return;
    }

    if(this->size == this->capacity/4)
    resize(this->capacity/2);

    std::cout << "You removed the whole product " << this->products[index]->getProductName() << " with volume of " << this->products[index]->getVolume() << " from: ";
    this->products[index]->getPosition().print();

    this->size--;
    delete this->products[index];
    for(int i = index; i<this->size;i++)
    {
        this->products[i] = this->products[i+1];
    }
}

void Storage::bubbleSort() 
{
    if(this->size == 0 || this->size == 1)
    return;

    for (int i = 0; i < this->size - 1; i++) 
    {
        for (int j = 0; j < this->size - i - 1; j++) 
        {
            if (this->products[j]->getExpDate() > this->products[j+1]->getExpDate()) 
            {
                Product* temp = products[j];
                products[j] = products[j+1];
                products[j+1] = temp;
            }
        }
    }
}

void Storage::bubbleSortByProductName() 
{
    if(this->size == 0 || this->size == 1)
    return;
    
    bool swapped;

    for (int i = 0; i < this->size - 1; ++i) 
    {
        swapped = false;
        for (int j = 0; j < this->size - i - 1; ++j)
        {
            if (this->products[j]->getProductName() > this->products[j + 1]->getProductName())
            {
                std::swap(products[j], products[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) 
        break;
    }
}

void Storage::printVolAndNameOnly()
{
    this->bubbleSortByProductName();
    std::string currentName = this->products[0]->getProductName();
    double totalVolume = this->products[0]->getVolume();
    std::string currentType;

    if(this->products[0]->getType() == kilograms)
    currentType = "kilograms.";
    else
    currentType = "litres.";

    for (int i = 1; i < this->size; ++i) 
    {
        if (this->products[i]->getProductName() == currentName) 
        {
            totalVolume += this->products[i]->getVolume();
        } 
        else 
        {
            std::cout << "The name of the product is: " << currentName << ", with a total volume of: " << totalVolume << " " << currentType << std::endl;

            currentName = this->products[i]->getProductName();
            totalVolume = this->products[i]->getVolume();
            if(this->products[i]->getType() == kilograms)
            currentType = "kilograms.";
            else
            currentType = "litres.";
        }
    }
  
    std::cout << "The name of the product is: " << currentName << ", with a total volume of: " << totalVolume << " " << currentType << std::endl;
}

void Storage::PrintWholeThing()
{
    if (this->size == 0) 
    {
        std::cout << "The are no products in the storage." << std::endl;
        return;
    }
    
    for(int i = 0; i<this->size; i ++)
        {
            std::cout << "Name and manufacturer name: " << this->products[i]->getProductName() << " ; " << this->products[i]->getManufacturerName() << std::endl;
            std::cout << "Expiry date and date of arrival: " << this->products[i]->getExpDate() << " ; " << this->products[i]->getArrDate() << std::endl;

            std::string currentType;

            if(this->products[i]->getType() == kilograms)
            currentType = "kilograms.";
            if(this->products[i]->getType() == litres)
            currentType = "litres.";

            std::cout << "Metric type of the product: " << currentType << std::endl;
            std::cout << "Position: ";
            this->products[i]->getPosition().print();
            std::cout << "Volume: " << this->products[i]->getVolume() << std::endl;
            std::cout << "Comment: " <<std::endl;
            std::cout << this->products[i]->getComment() << std::endl;
            std::cout << "------------------------------------------------------------------------------------------" << std::endl;
        }
}

void Storage::print() 
{
    if (this->size == 0) 
    {
        std::cout << "There are no products in the storage." << std::endl;
        return;
    }

    this->printVolAndNameOnly();
}

void Storage::ShowWhatIsAvailableByName(const std::string& name)
{
    for (int i = 0; i < this->size; i++)
        {
            if(this->products[i]->getProductName().compare(name) == 0)
            {
                std::cout << this->products[i]->getProductName() << " with a volume of "  << this->products[i]->getVolume() << " with an expiration date: ";
                this->products[i]->getExpDate().PrintData();
            }
        } 
}

std::ostream& operator << (std::ostream& out, const Storage& other)
{
    for(int i = 0; i<other.getSize(); i++)
    {
        out << *other.products[i];
    }
    return out;
}

std::istream& operator >> (std::istream& file, Storage& other)
{
    file.seekg(0, std::ios::beg);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);

        std::string name;
        std::getline(iss, name, ';');

        std::string expDateString;
        std::getline(iss, expDateString, ';');
        Date expDate(expDateString);

        std::string arrDateString;
        std::getline(iss, arrDateString, ';');
        Date arrDate(arrDateString);

        std::string manufacturer;
        std::getline(iss, manufacturer, ';');

        std::string metricType;
        std::getline(iss, metricType, ';');

        Metric type;
        if(metricType == "kilograms")
        type = kilograms;
        else
        type = litres;
        
        std::string volumestr;
        std::getline(iss, volumestr, ';');
        double volume = std::stod(volumestr);

        std::string posonestr;
        std::getline(iss, posonestr, ';');
        int pos1 = std::stoi(posonestr);

        std::string postwostr;
        std::getline(iss, postwostr, ';');
        int pos2 = std::stoi(postwostr);

        std::string posthreestr;
        std::getline(iss, posthreestr);
        int pos3 = std::stoi(posthreestr);

        Position position(pos1,pos2,pos3);

        std::string comment = "";
        std::getline(file, line);
        comment += line;

        other.addProduct(new Product{name, expDate, arrDate, manufacturer, type, volume, comment, position});
    }
}
