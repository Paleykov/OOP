#include "Log.hpp"

Log::Log(): type(ADDED), ProductName(""), quantity(0), DateOfLog(){}

Log::Log(const Action& type, const std::string& ProductName, const Date& date, const double& quantity):
type(type), ProductName(ProductName), DateOfLog(date), quantity(quantity){}

const std::string& Log::getProductName() const
{
    return this->ProductName;
}

const Action& Log::getType() const
{
    return this->type;
}
    
const double& Log::getQuantity() const
{
    return this->quantity;
}

const Date& Log::getDateOfLog() const
{
    return this->DateOfLog;
}

void Log::setProductName(const std::string& ProductName)
{
    this->ProductName = ProductName;
}

void Log::setQuantity(const double& quantity)
{
    this->quantity = quantity;
}

void Log::setType(const Action& type)
{
    this->type = type;
}

void Log::setDateOfLog(const Date& date)
{
    this->DateOfLog = date;
}

std::ostream& operator << (std::ostream& out, const Log& other)
{
    std::string action;
    if(other.getType() == 1)
    action = "ADDED";
    if(other.getType() == 2)
    action = "REMOVED";
    if(other.getType() == 3)
    action = "CLEARED";

    out << action << std::endl;
    out << other.getProductName() << std::endl;
    out << other.getQuantity() << std::endl;
    out << other.getDateOfLog() << std::endl;
    return out;
}
