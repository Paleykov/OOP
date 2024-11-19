#include "LogArray.hpp"

void LogArray::deallocate()
{
    for(int i = 0; i<this->size; i++)
    delete this->logs[i];
    delete[] this->logs;
}

void LogArray::copyFrom(const LogArray& other)
{
    this->logs = new Log*[other.capacity];
    if(!this->logs)
    {
        throw std::bad_alloc();
    }

    for(int i = 0; i< other.size; i++)
    {
        this->logs[i] = new Log(*other.logs[i]);
    }

    this->capacity = other.capacity;
    this->size = other.size;
}

void LogArray::resize(const int& newCapacity)
{
    this->capacity = newCapacity;

    Log** LogsBuffer = new Log*[newCapacity];
    if(!LogsBuffer)
    {
        throw std::bad_alloc();
    }

    for(int i = 0; i < this->size; i++)
    {
        LogsBuffer[i] = this->logs[i];
    }

    delete[] this->logs;
    this->logs = LogsBuffer;
}

LogArray::LogArray(): size(0), capacity(4)
{
    this->logs = new Log*[this->capacity];
    if(!this->logs)
    {
        throw std::bad_alloc();
    }
}
    
LogArray::LogArray(const LogArray& other)
{
    copyFrom(other);
}

LogArray::~LogArray()
{
    this->deallocate();
}

LogArray & LogArray::operator=(const LogArray& other)
{
    if(this!=&other)
    {
        this->deallocate();
        copyFrom(other);
    }

    return *this;
}

const int& LogArray::getSize() const
{
    return this->size;
}

const int& LogArray::getCapacity() const
{
    return this->capacity;
}

Log** LogArray::getLogs() const
{
    return this->logs;
}

void LogArray::addLog(Log* newLog)
{
    if(this->size == this->capacity)
    resize(this->capacity*2);

    this->logs[this->size++] = newLog;
}

void LogArray::print()
{
    if (this->size == 0) 
    {
        std::cout << "The are no logs." << std::endl;
        return;
    }

    for(int i = 0; i < this->size; i++)
    {
        std::string currentName = this->logs[i]->getProductName();
        double volume = this->logs[i]->getQuantity();
        Date currentDate = this->logs[i]->getDateOfLog();
        std::string action;

        if(this->logs[i]->getType() == 1)
        action = "ADDED";
        if(this->logs[i]->getType() == 2)
        action = "REMOVED";
        if(this->logs[i]->getType() == 3)
        action = "CLEARED";

        std::cout << "The product is: " << currentName << " with a volume of " << volume << std::endl;
        std::cout << "It was: " << action << std::endl;
        std::cout << "The date of the action is: " << currentDate << std::endl;
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
    }
}

void LogArray::printWithDates(const Date& from, const Date& to)
{
    this->sortByDates();
    if(this->size == 0)
    {
        std::cout << "Log is empty" << std::endl;
        return;
    }

    bool thereIs = false;
    for(int i = 0; i < this->size; i++)
    {
        Date currentDate = this->logs[i]->getDateOfLog();
        if(currentDate >= from && to >= currentDate)
        {
        thereIs = true;
        std::string currentName = this->logs[i]->getProductName();
        double volume = this->logs[i]->getQuantity();
        std::string action;

        if(this->logs[i]->getType() == 1)
        action = "ADDED";
        if(this->logs[i]->getType() == 2)
        action = "REMOVED";
        if(this->logs[i]->getType() == 3)
        action = "CLEARED";

        std::cout << "The product is: " << currentName << " with a volume of " << volume << std::endl;
        std::cout << "It was: " << action << std::endl;
        std::cout << "The date of the action is: " << currentDate << std::endl;
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
        }
    }
    if(thereIs == false)
    std::cout << "No logs in this period of time" << std::endl;
}

std::ostream& operator << (std::ostream& out, const LogArray& other)
{
    for(int i = 0; i<other.getSize(); i++)
    {
        out << *other.logs[i];
    }
    return out;
}

void LogArray::sortByDates() {
    for (int i = 0; i < this->size - 1; i++) 
    {
        for (int j = 0; j < this->size - i - 1; j++) 
        {
            if (this->logs[j]->getDateOfLog() > this->logs[j + 1]->getDateOfLog()) 
            {
                Log* temp = this->logs[j];
                this->logs[j] = this->logs[j + 1];
                this->logs[j + 1] = temp;
            }
        }
    }
}

std::istream& operator >>(std::istream& file, LogArray& other)
{
    // FORMAT:
    // ADDED/CLEARED/REMOVED
    // NAME
    // QUANTITY
    // DATE OF LOG

    std::string action;
    std::string name;
    double quantity;
    std::string date;

    file.seekg(0, std::ios::beg);
    while (std::getline(file, action)) 
    {
        std::getline(file, name);

        if (!(file >> quantity)) {
            break;
        }
        file.ignore();

        std::getline(file, date);

        Action type;
        if (action == "ADDED")
        type = Action::ADDED;
        else 
        if (action == "REMOVED")
        type = Action::REMOVED;
        else 
        if (action == "CLEARED")
        type = Action::CLEARED;

        Date logDate(date);
        other.addLog(new Log(type, name, logDate, quantity));
    }

    return file;
}