#include "Engine.hpp"

Engine::Engine(): storage(), stopProgram(false), fileIisOpen(false), currentFileName("") {}

Engine& Engine::getInstance()
{
    static Engine object;
    return object;
}

void Engine::printHelp()
{
    std::cout << "The following file commands are supported: " << std::endl;

    std::cout << "open <filename>                              Opens a file with the given name. If no file exists, opens a new, empty file." << std::endl;
    std::cout << "close                                        Closes the currently open file." << std::endl;
    std::cout << "save                                         Saves the changes in the currently open file." << std::endl;
    std::cout << "saveas <filename>                            Saves the changes in a file appointed by the user." << std::endl;
    std::cout << "exit                                         Exits the program.\n" << std::endl;

    std::cout << "The following commands for work with the storage are supported: " << std::endl;

    std::cout << "print                                        Prints the current items in storage." << std::endl;
    std::cout << "printall                                     BONUS OPTION for a thorough review of all the items." << std::endl;
    std::cout << "add                                          Adds an item in the storage in a special dialogue mode." << std::endl;
    std::cout << "remove <name> <quantity>                     Removes an input amount of products that match this name." << std::endl;
    std::cout << "log <from date> <to date>                    Shows a log of all the actions by the user in a given time period." << std::endl;
    std::cout << "clean                                        Clear the storage from all expired or soon to expire products." << std::endl;
    std::cout << "losses <name> <price> <from date> <to date>  A BONUS OPTION Shows the losses from expired products in a given time period.\n" << std::endl;

    std::cout << "*NOTE: THE ADD COMMAND AUTOFILLS PRODUCTS THAT HAVE THE SAME EXPIRATION DATE AND NAME!" << std::endl;
    std::cout << "*NOTE: THE CLEAN COMMAND CLEARS THE STORE FROM PRODUCTS THAT WILL EXPIRE IN 3 DAYS!" << std::endl;
    std::cout << "*NOTE: THE SUPPORTED FORMAT FOR DATES IS AS FOLLOWS: DD.MM.YYYY" << std::endl;
    std::cout << "*NOTE: THE SUPPORTED FORMAT FOR METRIC TYPE IS AS FOLLOWS: \"kilograms\" or \"litres\"." << std::endl;
    std::cout << "*NOTE: THE SUPPORTED FORMAT FOR POSITION IS AS FOLLOWS: SECTION SHELF NUMBER -> WHOLE POSITIVE NUMBERS." << std::endl;
    std::cout << "*NOTE: AS THIS SIMULATES A REAL STORAGE, THERE IS AN ARTIFICIAL LIMIT: 10 SECTIONS, EACH WITH 10 SHELVES," << std::endl;
    std::cout << " EACH WITH 10 PLACES NUMERATED FROM 1 TO 10 INCLUDED, EACH PLACE HOLDING UP TO 100 KG/L OF PRODUCT (CAN BE EASILY CHANGED)" << std::endl;
    std::cout << "*NOTE: THE FORMAT OF THE FILENAMES IS \"NAME.TXT\"" << std::endl;
}

std::string Engine::stringToLower(std::string string)
{
    std::string result = "";

    for (int i = 0; i < string.length(); ++i)
    {
        result.push_back(tolower(string[i]));
    }

    return result;
}

void Engine::removeSpaces(std::string& string)
{
    std::size_t currentIndex = 0;
    std::size_t length = string.length();

    std::string result = "";

    while (string[currentIndex] == ' ')
    {
        ++currentIndex;
    }

    bool spaceFound = false;

    while (currentIndex < length)
    {
        if (string[currentIndex] != ' ')
        {
            result.push_back(string[currentIndex++]);
            spaceFound = false;
        }
        else
        {
            if (!spaceFound)
            {
                result.push_back(string[currentIndex++]);
                spaceFound = true;
            }
            else
            {
                ++currentIndex;
            }
        }
    }

    if (result.back() == ' ')
    {
        result.pop_back();
    }

    string = result;
}

void Engine::add()
{
    std::string ProductName;
    std::string ManufacturerName;
    Metric Type;
    std::string volume;
    Position position;
    std::string comment;

    std::cout << "Please, input the name of the product:" << std::endl;
    std::getline(std::cin, ProductName);
    removeSpaces(ProductName);

    std::cout << "Please, input the product's manufacturer name:" << std::endl;
    std::getline(std::cin, ManufacturerName);
    removeSpaces(ManufacturerName);

    std::cout << "Please, add a comment" << std::endl;
    std::getline(std::cin, comment);
    removeSpaces(comment);

    std::cout << "Please, input the expiration date of the product:" << std::endl;
    std::string ExpDateStr;
    std::cin >> ExpDateStr;
    std::cin.ignore();
    while(!CheckData(ExpDateStr))
    {
        std::cout << "This date is invalid. Please, try again!" << std::endl;
        std::cin >> ExpDateStr;
        std::cin.ignore();
    }   
    Date ExpDate(ExpDateStr);

    std::cout << "Please, input the arrival date of the product:" << std::endl;
    std::string ArrDateStr;
    std::cin >> ArrDateStr;
    std::cin.ignore();
    while(!CheckData(ArrDateStr))
    {
        std::cout << "This date is invalid. Please, try again!" << std::endl;
        std::cin >> ArrDateStr;
        std::cin.ignore();
    }  
    Date ArrDate(ArrDateStr);

    std::cout << "Please, input the metric type of the product: " << std::endl;
    std::string metric;
    std::cin >> metric;
    std::cin.ignore();
    metric = stringToLower(metric);
    while(metric.compare("kilograms") != 0 && metric.compare("litres") != 0)
    {
        std::cout << "The metric type is incorrect. Please, try again:" << std::endl;
        std::cin >> metric;
        std::cin.ignore();
        metric = stringToLower(metric);
    }
    if(metric == "kilograms")
    Type = kilograms;
    if (metric == "litres")
    Type == litres;

    std::cout << "Please, input the volume of the product:" << std::endl;
    double realvol = 0;
    while(true)
    {
        std::cin >> volume;
        std::cin.ignore();
        if(!isNumber(volume))
        {
        std::cout << "Invalid volume. Please, try again:" << std::endl;
        continue;
        }
        realvol = std::stod(volume);
        if(realvol <= 0)
        {
            std::cout << "Invalid volume. Please, try again:" << std::endl;
            continue;
        }
        break; 
    }

    short int section;
    short int shelf;
    short int number;
    std::cout << "Now you have to input the position you want to place the item at. " << std::endl;
    std::cout << "Please, input the number of the section: ";
    std::cin >> section;
    std::cin.ignore();
    while(section <= 0 && section >10)
    {
        std::cout << "Invalid section, please try again: " << std::endl;
        std::cin >> section;
        std::cin.ignore();
    }
    std::cout << "Please, input the number of the shelf: ";
    std::cin >> shelf;
    std::cin.ignore();
    while(shelf <= 0 && shelf >10)
    {
        std::cout << "Invalid shelf, please try again: " << std::endl;
        std::cin >> shelf;
        std::cin.ignore();
    }
    std::cout << "Please, input the number on the shelf: ";
    std::cin >> number;
    std::cin.ignore();
    while(number <= 0 && number >10)
    {
        std::cout << "Invalid number, please try again: " << std::endl;
        std::cin >> number;
        std::cin.ignore();
    }
    position = Position(section, shelf, number);

    Product product(ProductName, ExpDate, ArrDate, ManufacturerName, Type, realvol, comment, position);
    this->storage.addProductByData(product);
}

bool Engine::isValidFilename(const std::string& filename) 
{
    if (filename.length() < 4)
        return false;

    std::string extension = filename.substr(filename.length() - 4);
    if (extension != ".txt")
        return false;

    return true;
}

bool Engine::CharIsNum(char ch)
{
    return ch >= '0' && ch <= '9';
}

bool Engine::isNumber(std::string str) 
{
    try 
    {
        size_t pos = 0;
        std::stod(str, &pos);
        return pos == str.length();
    } 
    catch (...) 
    {
        return false;
    }
}

bool Engine::DateIsNumber(const std::string& date)
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

int Engine::ConvertFromCharToNum(const char& a)
{
    return a - '0';
}

bool Engine::DateIsValid(const std::string& date)
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

bool Engine::CheckData(const std::string& other)
{
    if(other.length()!=10)
    return false;
    if(!DateIsNumber(other))
    return false;
    if(!DateIsValid(other))
    return false;

    return true;
}

bool Engine::isCommandValid(CommandReader command)
{
    std::string mainCommand = command[0];
    int size = command.getNumberOfArgs();

    if(mainCommand != "open" && mainCommand != "close" && mainCommand != "save" && mainCommand != "saveas" && mainCommand != "exit" 
    && mainCommand !="print" && mainCommand != "add" && mainCommand !="remove" && mainCommand !="log" && mainCommand != "log"
    && mainCommand !="clean" && mainCommand !="losses" && mainCommand != "help" && mainCommand != "printall" && mainCommand != "buffer")
    {
        std::cout << "Invalid main command" << std::endl;
        return false;
    }

    if(mainCommand == "open" || mainCommand == "saveas")
    {
        if(size != 2)
        {
            std::cout << "Invalid number of arguments in command" << std::endl;
            return false;
        }
        if(!isValidFilename(command[1]))
        {
            std::cout << "Invalid file name" << std::endl;
            return false;
        }
    }

    if(mainCommand == "close" || mainCommand == "save" || mainCommand == "exit" || mainCommand == "print"  || mainCommand == "clean" || mainCommand == "help"
    || mainCommand == "printall")
    {
        if(size != 1)
        {
            std::cout << "Invalid number of arguments in command" << std::endl;
            return false;
        }
    }

    if(mainCommand == "add")
    {
        if(size != 1)
         {
            std::cout << "Invalid number of arguments in command" << std::endl;
            return false;
        }
    }
    
    if(mainCommand == "remove")
    {
        if(size !=3)
        {
            std::cout << "Invalid number of arguments in command" << std::endl;
            return false;
        }
        if(!isNumber(command[2]))
         {
            std::cout << "Invalid quantity of the product" << std::endl;
            return false;
        }
        double number = std::stod(command[2]);
        if(number<=0)
        {
            std::cout << "Invalid quantity of the product" << std::endl;
            return false;
        }
    }

    if(mainCommand == "log")
    {
        if(size !=3)
        {
            std::cout << "Invalid number of arguments in command" << std::endl;
            return false;
        }
        if(!CheckData(command[2]) || !CheckData(command[1]))
        {
            std::cout << "Invalid dates" << std::endl;
            return false;
        }
    }

    if(mainCommand == "losses")
    {
        if(size !=5)
        {
            std::cout << "Invalid number of arguments in command" << std::endl;
            return false;
        }
        if(!CheckData(command[3]) || !CheckData(command[4]))
        {
            std::cout << "Invalid dates" << std::endl;
            return false;
        }
        if(!isNumber(command[2]))
         {
            std::cout << "Invalid quantity of the product" << std::endl;
            return false;
        }
        double number = std::stod(command[2]);
        if(number<=0)
        {
            std::cout << "Invalid quantity of the product" << std::endl;
            return false;
        }
    }

    return true;
}

bool Engine::fileExists(std::string filename)
{
    std::ifstream file(filename);
    bool result = file.good();
    file.close();

    return result;
}

bool Engine::isNewFile(const std::string& filename) 
{
    std::ifstream file(filename);
    if (!file) 
    {
        std::cout << "Error opening file. " << std::endl;
        return false;
    }

    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.close();

    return (fileSize == 0);
}

std::string Engine::NameOfLog(const std::string& name)
{
    size_t positionOfDot = name.find_last_of(".");
    std::string fileNameWithoutExt = name.substr(0, positionOfDot);
    std::string filenameLog = fileNameWithoutExt + "Log" + name.substr(positionOfDot);
    return filenameLog;
}

void Engine::Open(std::string name)
{
    if(this->fileIisOpen)
    {
        std::cout << "A file is already opened!" << std::endl;
        return;
    }

    bool fileExist = fileExists(name);
    if(!fileExist)
    {
        std::cout << "No file with such name exists. A new one with this name will be created" << std::endl;
        std::ofstream file(name);
        if(!file)
        {
            std::cout << "Error opening file" << std::endl;
            return;
        }

        Commands bufferStorage;
        this->storage = bufferStorage;
        
        std::string filenameLog = NameOfLog(name);
        std::ofstream fileLog(filenameLog);
        if(!fileLog)
        {
            std::cout << "Error opening log file" << std::endl;
            return;
        }

        this->fileIisOpen = true;
        std::cout << "File successfully created!" << std::endl;
        std::cout << "File successfully opened!" << std::endl;
    }
    else
    {
        std::ifstream file(name);
        if(!file)
        {
            std::cout << "Error opening file" << std::endl;
            return;
        }
        std::cout << "File successfully opened!" << std::endl;
        this->fileIisOpen = true;

        Storage storage;
        file >> storage;

        std::string filenameLog = NameOfLog(name);
        std::ifstream fileLog(filenameLog);
        if(!fileLog)
        {
            std::cout << "Error opening log file" << std::endl;
            return;
        }

        LogArray log;
        fileLog >> log;

        this->storage = Commands(storage, log);

        file.close();
        fileLog.close();
    }
}

void Engine::Exit()
{
    std::cout << "Exiting program..." << std::endl;
    this->stopProgram = true;
}

void Engine::Close()
{
    this->fileIisOpen = false;
    std::cout << "Program successfully closed. The memory is cleared." << std::endl;
}

void Engine::SaveFile(const std::string filename)
{
    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    if(!file)
    {
        std::cout << "Output file could not be opened" << std::endl;
        return;
    }

    std::string logFileName = NameOfLog(filename);
    std::ofstream fileLog(logFileName, std::ios::out | std::ios::trunc);
    if(!fileLog)
    {
        std::cout << "Output file could not be opened" << std::endl;
        return;
    }

    file << this->storage.getStorage();
    fileLog << this->storage.getLogArray();

    std::cout << "File successfully saved!" << std::endl;
    file.close();
    fileLog.close();
}

void Engine::DoCommand(CommandReader command)
{
    if (!isCommandValid(command))
    {
        return;
    }

    std::string mainCommand = command[0];
    std::size_t size = command.getNumberOfArgs();
    
    if (mainCommand == "help") 
    {
        this->printHelp();
    }
    else if (mainCommand == "close")
    {
        if(!this->fileIisOpen)
        {
            std::cout << "No file is open" << std::endl;
        }
        else
        {
            this->currentFileName = "";
            this->Close();
        }
    }
    else if (mainCommand == "exit") 
    {
        this->Exit();
    }
    else if (mainCommand == "open")
    {
        this->currentFileName = command[1];
        this->Open(command[1]);
    }
    else if (mainCommand == "printall")
    {
        if(!this->fileIisOpen)
        {
            std::cout << "No file is open" << std::endl;
        }
        else
        this->storage.printWholeThing();
    }
    else if (mainCommand == "save")
    {
        if(!this->fileIisOpen)
        {
            std::cout << "No file is open" << std::endl;
        }
        else
        this->SaveFile(this->currentFileName);
    }
    else if (mainCommand == "saveas")
    {
        if(!this->fileIisOpen)
        {
            std::cout << "No file is open" << std::endl;
        }
        else
        this->SaveFile(command[1]);
    }
    else if(mainCommand == "print") 
    {
        if(!this->fileIisOpen)
        {
            std::cout << "No file is open" << std::endl;
        }
        else
        this->storage.print();
    }
    else if(mainCommand == "add") 
    {
        if(!this->fileIisOpen)
        {
            std::cout << "No file is open" << std::endl;
        }
        else
        this->add();
    }
    else if(mainCommand == "remove") 
    {
        if(!this->fileIisOpen)
        {
            std::cout << "No file is open" << std::endl;
        }
        else
        {
            double number = std::stod(command[2]);
            this->storage.removeProductByNameAndVol(command[1], number);
        }
    }
    else if(mainCommand == "log")
    {
        if(!this->fileIisOpen)
        {
            std::cout << "No file is open" << std::endl;
        }
        else
        this->storage.ShowLog(command[1],command[2]);
    }
    else if(mainCommand == "clean") 
    {
        if(!this->fileIisOpen)
        {
            std::cout << "No file is open" << std::endl;
        }
        else
        this->storage.clearProducts();
    }
    else if(mainCommand == "losses")
    {
        if(!this->fileIisOpen)
        {
            std::cout << "No file is open" << std::endl;
        }
        else
        {
            double number = std::stod(command[2]);
            this->storage.ShowLosses(command[1], number, command[3],command[4]);
        }
    }
}

void Engine::Exe()
{
    std::cout << "Welcome to the storage program!" << std::endl;
    std::cout << "Please, input a command. You can see the available commands with the command \"help\"" << std::endl;
    while (!this->stopProgram)
    {   
        std::string command;
        std::getline(std::cin, command);

        CommandReader cmd(command);
        this->DoCommand(cmd);
    }
}