#include "Dates.hpp"
#include <string>


    Date::Date(): data("01.01.2020"){}

    Date::Date(const std::string data)
    {
        setData(data);
    }
    
    const std::string &Date::getData() const
    {
        return this->data;
    }

    void Date::setData(const std::string& other)
    {
        this->data = other;
    }

    bool Date::CharIsNum(const char& a)
    {
        return (a>= '0' && a<='9');
    }

    bool Date::DateIsNumber(const std::string& date)
    {
        for(int i = 0; i<10; i++)
        {
            if(i == 2 || i == 5)
            {
                if(date[2] != '.' || date[5] != '.')
                return false;
                else
                continue;
            }
            if(!CharIsNum(date[i]))
            return false;
        }

        return true;
    }

    bool Date::DateIsValid(const std::string& date)
    {
        int day, month, year;
        day = ConvertFromCharToNum(date[0])*10 + ConvertFromCharToNum(date[1]);
        month = ConvertFromCharToNum(date[3])*10 + ConvertFromCharToNum(date[4]);
        year = ConvertFromCharToNum(date[6])*1000 + ConvertFromCharToNum(date[7])*100 + ConvertFromCharToNum(date[8])*10 + ConvertFromCharToNum(date[9]);

        if (year < 0) 
        {return false;} 
        else if (month < 1 || month > 12) 
        {return false;} 
        else if (day < 1 || day > 31)
        {return false;} 
        else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) 
        {return false;} 
        else if (month == 2) 
        {
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) 
            {
                if (day > 29) 
                    {return false;}
            } 
            else if (day > 28) 
            {return false;}
        }

        return true;
    }

    int Date::ConvertFromCharToNum(const char& a) const
    {
        return a - '0';
    }

    bool Date::operator > (const Date& other) const
    {
        int day1, month1, year1;
        day1 = ConvertFromCharToNum(getData()[0])*10 + ConvertFromCharToNum(getData()[1]);
        month1 = ConvertFromCharToNum(getData()[3])*10 + ConvertFromCharToNum(getData()[4]);
        year1 = ConvertFromCharToNum(getData()[6])*1000 + ConvertFromCharToNum(getData()[7])*100 + ConvertFromCharToNum(getData()[8])*10 + ConvertFromCharToNum(getData()[9]);

        int day2, month2, year2;
        day2 = ConvertFromCharToNum(other.getData()[0])*10 + ConvertFromCharToNum(other.getData()[1]);
        month2 = ConvertFromCharToNum(other.getData()[3])*10 + ConvertFromCharToNum(other.getData()[4]);
        year2 = ConvertFromCharToNum(other.getData()[6])*1000 + ConvertFromCharToNum(other.getData()[7])*100 + ConvertFromCharToNum(other.getData()[8])*10 
        + ConvertFromCharToNum(other.getData()[9]);

        return ((year1 > year2) || (year1 == year2 && month1 > month2) || (year1 == year2 && month1 == month2 && day1 > day2));
    }

    bool Date::CheckData(const std::string& other)
    {
        if(other.length()!=10)
        return false;
        if(!DateIsNumber(other))
        return false;
        if(!DateIsValid(other))
        return false;

        return true;
    }

    void Date::PrintData() const
    {
        std::cout << this->data << std::endl;
    }

    std::ostream& operator << (std::ostream& out, const Date& date)
    {
        out << date.data;
        return out;
    }

    std::istream& operator >> (std::istream& in, Date& data)
    {
        in >> data.data;
        return in;
    }

    void Date::setCurrDate()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);

        std::tm* timeinfo = std::localtime(&time);

        std::stringstream ss;
        ss  << std::setfill('0') << std::setw(2) << timeinfo->tm_mday << "."
            << std::setfill('0') << std::setw(2) << timeinfo->tm_mon + 1 << "."
            << timeinfo->tm_year + 1900;
        std::string date_str = ss.str();

        this->setData(date_str);
    }

    int operator -(const Date& lhs, const Date& rhs) 
    {
        std::string lhs_data = lhs.getData();
        std::string rhs_data = rhs.getData();

        int lhs_day = std::stoi(lhs_data.substr(0, 2));
        int lhs_month = std::stoi(lhs_data.substr(3, 2));
        int lhs_year = std::stoi(lhs_data.substr(6, 4));

        int rhs_day = std::stoi(rhs_data.substr(0, 2));
        int rhs_month = std::stoi(rhs_data.substr(3, 2));
        int rhs_year = std::stoi(rhs_data.substr(6, 4));

        int DAYS_IN_MONTH[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        int difference = 0;
        while (lhs_day != rhs_day || lhs_month != rhs_month || lhs_year != rhs_year) 
        {
            lhs_day--;
            if (lhs_day == 0) 
            {
                lhs_month--;
                if (lhs_month == 0) 
                {
                    lhs_month = 12;
                    lhs_year--;
                    if (lhs_year % 4 == 0 && (lhs_year % 100 != 0 || lhs_year % 400 == 0)) 
                    {
                        DAYS_IN_MONTH[1] = 29;
                    } 
                    else 
                    {
                        DAYS_IN_MONTH[1] = 28;
                    }
                }
                lhs_day = DAYS_IN_MONTH[lhs_month - 1];
            }
            difference++;
        }

        return difference;
    }

    bool Date::operator == (const Date& other) const
    {
        return this->data == other.data;
    }

    bool Date::operator !=(const Date& other) const
    {
        return this->data != other.data;
    }

    bool Date::operator>=(const Date& other) const
    {
        return !(other > *this);
    }  
