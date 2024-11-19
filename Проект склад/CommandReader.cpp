#include "CommandReader.hpp"

CommandReader::CommandReader(std::string commandLine)
{
    if (commandLine.length() == 0 || NumberOfClosingSymbols(commandLine)%2 == 1)
    {
        throw std::invalid_argument("Empty/invalid command line");
    }

    this->CommandReaderFunction(commandLine);
}

int CommandReader::getNumberOfArgs() const
{
    return this->command.size();
}

int CommandReader::NumberOfClosingSymbols(std::string string)
{
    int counter = 0;

    for (int i = 0; i < string.length(); ++i)
    {
        if (string[i] == '\"')
        {
            ++counter;
        }
    }

    return counter;
}

std::string CommandReader::stringToLower(std::string string)
{
    std::string result = "";

    for (int i = 0; i < string.length(); ++i)
    {
        result.push_back(tolower(string[i]));
    }

    return result;
}

void CommandReader::removeSpaces(std::string& string)
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

void CommandReader::removeEmptyArgs(std::vector<std::string>& arguments)
{
    for (std::size_t i = 0; i < arguments.size(); ++i)
    {
        if (arguments[i] == "")
        {
            arguments.erase(arguments.begin() + i);
            --i;
        }
    }
}

void CommandReader::CommandReaderFunction(std::string commandLine)
{
    removeSpaces(commandLine);

    std::size_t length = commandLine.length();
    std::size_t currentIndex = 0;
    std::size_t countWords = 0;

    std::string currentWord = "";

    bool openedQuotes = false;
    while (currentIndex < length)
    {
        if (commandLine[currentIndex] == '\"')
        {
            if (currentIndex == length - 1)
            {
                this->command.push_back(currentWord);
                currentWord = "";
                ++countWords;
            }

            openedQuotes = !openedQuotes;
        }
        else if (currentIndex == length - 1 || (!openedQuotes && commandLine[currentIndex] == ' '))
        {
            if (currentIndex == length - 1)
            {
                currentWord.push_back(commandLine[currentIndex]);
            }
            this->command.push_back(currentWord);
            currentWord = "";
            ++countWords;
        }
        else
        {
            currentWord.push_back(commandLine[currentIndex]);
        }

        ++currentIndex;
    }

    for (std::size_t i = 0; i < countWords; ++i)
    {
        removeSpaces(this->command[i]);
    }

    removeEmptyArgs(this->command);

    this->command[0] = stringToLower(this->command[0]);
}

std::string& CommandReader::operator [](std::size_t index)
{
    return this->command[index];
}

const std::string& CommandReader::operator [](std::size_t index) const
{
    return this->command[index];
}
