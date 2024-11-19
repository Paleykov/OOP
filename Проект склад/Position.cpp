#include "Position.hpp"

    Position::Position(): section(0),shelf(0),number(0){}

    Position::Position(const int& section, const int& shelf, const int& number)
    {
        setSection(section);
        setShelf(shelf);
        setNumber(number);
    }
    
    const int& Position::getSection() const
    {
        return this->section;
    }

    const int& Position::getShelf() const
    {
        return this->shelf;
    }

    const int& Position::getNumber() const
    {
        return this->number;
    }

    void Position::setSection(const int& section)
    {
        this->section = section;
    }

    void Position::setShelf(const int& shelf)
    {
        this->shelf = shelf;
    }

    void Position::setNumber(const int& number)
    {
        this->number = number;
    }

    bool Position::positionIsValid() const
    {
        if(this->getNumber() > 10 || this->getNumber() <= 0)
        return false;
        if(this->getSection() > 10 || this->getSection() <= 0)
        return false;
        if(this->getShelf() > 10 || this->getShelf() <= 0)
        return false;
        return true;
    }

    bool Position::operator ==(const Position& other) const
    {
        return (this->section == other.section && this->shelf == other.shelf && this->number == other.number);
    }

    bool Position::operator !=(const Position& other) const
    {
        return !(*this == other);
    }

    void Position::print() const
    {
        std::cout << "The section is #" << this->getSection() << ", the shelf is #" << this->getShelf() << ", the number on the shelf is #" << this->getNumber() << "." << std::endl;
    }

    std::ostream& operator << (std::ostream& out, const Position& other)
    {
        out << other.section << ";" << other.shelf << ";" << other.number;
        return out;
    }
