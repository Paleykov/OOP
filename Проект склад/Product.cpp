#include "Product.hpp"
#include <iostream>
#include <string>
#include <fstream>

    Product::Product(): ProductName("N/A"), ExpDate("01.01.2000"), ArrDate("01.01.2000"), 
    ManufacturerName("N/A"), Type(kilograms), volume(0), 
    Comment("//NO COMMENT"), position(){}

    Product::Product(const std::string& ProductName, const Date& ExpDate, const Date& ArrDate, 
    const std::string& ManufacturerName, const Metric& Type, 
    const double& volume, const std::string& Comment, const Position& position)
    {
        this->ProductName = ProductName;
        this->ExpDate = ExpDate;
        this->ArrDate = ArrDate;
        this->ManufacturerName = ManufacturerName;
        this->Type = Type;
        this->volume = volume;
        this->Comment = Comment;
        this->position = position;
    }

    Product & Product::operator +=(const Product& other)
    {
        if(this->ProductName!=other.ProductName && this->ExpDate != other.ExpDate)
        std::cout << "Error! Cannot add!" << std::endl;

        this->volume += other.volume;
    }

    Product & Product::operator -=(const Product& other)
    {
        if(this->ProductName!=other.ProductName && this->ExpDate != other.ExpDate)
        std::cout << "Error! Cannot subtract!" << std::endl;

        this->volume -= other.volume;
        if(this->volume < 0)
        this->volume = 0;
    }

    const std::string& Product::getProductName() const
    {
        return this->ProductName;
    }

    const Date& Product::getExpDate() const
    {
        return this->ExpDate;
    }

    const Date& Product::getArrDate() const
    {
        return this->ArrDate;
    }

    const std::string& Product::getManufacturerName() const
    {
        return this->ManufacturerName;
    }

    const Metric& Product::getType() const
    {
        return this->Type;
    }

    const double& Product::getVolume() const
    {
        return this->volume;
    }

    const std::string& Product::getComment() const
    {
        return this->Comment;
    }

    const Position& Product::getPosition() const
    {
        return this->position;
    }

    void Product::setPosition(const Position& other)
    {
        this->position = other;
    }

    void Product::setVolume(const double& volume)
    {
        this->volume = volume;
    }

    std::ostream& operator << (std::ostream& out, const Product& other)
    {
        std::string VolType;
        if(other.Type == kilograms)
        VolType = "kilograms";
        else
        VolType = "litres";
        out << other.ProductName << ";" << other.ExpDate << ";" << other.ArrDate << ";" 
            << other.ManufacturerName << ";" << VolType << ";" << other.volume << ";" << other.position << std::endl;
        out << other.Comment << std::endl;

        return out;
    }

    Product operator +(const Product& lhs, const Product& rhs)
    {
        Product result = lhs;
        result += rhs;
        return result;
    }

    Product operator -(const Product& lhs, const Product& rhs)
    {
        Product result = lhs;
        result -= rhs;
        return result;
    }
