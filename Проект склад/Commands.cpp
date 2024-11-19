#include "Commands.hpp"

Commands::Commands(const Storage& otherStorage, const LogArray& otherLog)
{
    this->storage = otherStorage;
    this->log = otherLog;
}

Commands::Commands(): storage(), log(){}

void Commands::clearProducts()
{
    Date today;
    today.setCurrDate();
    if(this->storage.getSize() == 0)
    {
        std::cout << "No products, cannot clear anything" << std::endl;
        return;
    }

    bool SomethingToBeCleared = false;

    for(int i = 0; i < this->storage.getSize(); ++i)
    {
        if(today == this->storage.getProducts()[i]->getExpDate() || today > this->storage.getProducts()[i]->getExpDate())
        {
            std::cout << "You cleared a product because it has expired: " << this->storage.getProducts()[i]->getExpDate() << std::endl;
            SomethingToBeCleared = true;

            Date date;
            date.setCurrDate();
            Log newLog(CLEARED, this->storage.getProducts()[i]->getProductName(), date, this->storage.getProducts()[i]->getVolume());
            this->log.addLog(new Log(newLog));
            this->storage.removeProduct(i);
            i--;
        }
        else
        {   
            int difference = this->storage.getProducts()[i]->getExpDate() - today;
            if(difference <= 3)
            {
                std::cout << "You cleared a product that expires soon: " << this->storage.getProducts()[i]->getExpDate() << std::endl;
                SomethingToBeCleared = true;

                Date date;
                date.setCurrDate();
                Log newLog(CLEARED, this->storage.getProducts()[i]->getProductName(), date, this->storage.getProducts()[i]->getVolume());
                this->log.addLog(new Log(newLog));
                this->storage.removeProduct(i);
                i--;
            }
        }
    }

    if(SomethingToBeCleared == false)
    {
        std::cout << "No products are expiring soon/are expired. Nothing was cleared" << std::endl;
    }
}

void Commands::DeleteAllWithName(const std::string& name)
{
    for (int i = 0; i < this->storage.getSize(); i++)
            {
                if(this->storage.getProducts()[i]->getProductName().compare(name) == 0)
                {
                    Date date;
                    date.setCurrDate();
                    Log newLog(REMOVED, this->storage.getProducts()[i]->getProductName(), date, this->storage.getProducts()[i]->getVolume());
                    this->log.addLog(new Log(newLog));
                    this->storage.removeProduct(i);
                    i--;
                }
            }   
}

void Commands::RemoveProductsIfVolIsLessThanTotalVol(const double& volume, const std::string& name)
{
        double currVol = volume;
        this->storage.bubbleSort();
        for (int i = 0; i < this->storage.getSize(); i++)
        {
            if(this->storage.getProducts()[i]->getProductName().compare(name) == 0)
            {
                if(this->storage.getProducts()[i]->getVolume()> currVol)
                {
                    Date date;
                    date.setCurrDate();
                    Log newLog(REMOVED, this->storage.getProducts()[i]->getProductName(), date, currVol);
                    this->log.addLog(new Log(newLog));

                    this->storage.getProducts()[i]->setVolume(this->storage.getProducts()[i]->getVolume()-currVol);
                    std::cout << "You removed " << currVol << " from the product "<< this->storage.getProducts()[i]->getProductName() << " at ";
                    this->storage.getProducts()[i]->getPosition().print();
                    break;
                }
                else if(this->storage.getProducts()[i]->getVolume() == currVol)
                {
                    Date date;
                    date.setCurrDate();
                    Log newLog(REMOVED, this->storage.getProducts()[i]->getProductName(), date, this->storage.getProducts()[i]->getVolume());
                    this->log.addLog(new Log(newLog));
                    this->storage.removeProduct(i);
                    break;
                }
                else 
                {
                    currVol -= this->storage.getProducts()[i]->getVolume();
                    Date date;
                    date.setCurrDate();
                    Log newLog(REMOVED, this->storage.getProducts()[i]->getProductName(), date, this->storage.getProducts()[i]->getVolume());
                    this->log.addLog(new Log(newLog));
                    this->storage.removeProduct(i);
                    i--;
                }
            }
        } 
}

void Commands::removeProductByNameAndVol(const std::string& name, const double& volume)
{
    if(this->storage.getSize() == 0)
    {
        std::cout << "There are no products in the storage" << std::endl;
        return;
    }

    double total_volume = 0;
    bool hasThisProduct = false;
    for (int i = 0; i < this->storage.getSize(); i++)
    {
        if(this->storage.getProducts()[i]->getProductName().compare(name) == 0)
        {
            total_volume += this->storage.getProducts()[i]->getVolume();
            hasThisProduct = true;
        }
    }

    if(hasThisProduct == false)
    {
        std::cout << "No products match this name" << std::endl;
        return;
    }

    if(total_volume < volume)
    {
        std::cout << "You want to remove more than you currently have. Here is what you have in storage:" << std::endl;
        this->storage.ShowWhatIsAvailableByName(name);

        std::cout << "Are you sure you want to remove the rest of your " << name << " products? y/n" << std::endl;
        
        std::string input;
        while (true) 
        {
            std::cin >> input;
            std::cin.ignore();

            if (input == "y" || input == "n" || input == "Y" || input == "N") 
            {
                break;
            } 
            else 
            {
            std::cout << "Invalid input. Please try again.\n";
            }
        }
        
        if(input == "y")
        {
            this->DeleteAllWithName(name);
        }
        else
        {std::cout << "No changes have been made to your products." << std::endl;}
    }
    else
    {
        this->RemoveProductsIfVolIsLessThanTotalVol(volume, name);
    }
}

bool Commands::FillAvailableSpaces(Product& newProduct)
{  
    for(int i = 0; i < this->storage.getSize(); i++)
    {
        double volumeAtPos = 0;
        if((this->storage.getProducts()[i]->getProductName().compare(newProduct.getProductName()) == 0) && (this->storage.getProducts()[i]->getExpDate() == newProduct.getExpDate()))
        {
            volumeAtPos = this->storage.volumeAtPosition(this->storage.getProducts()[i]->getPosition());
            if(volumeAtPos < 100)
            {
                if(volumeAtPos + newProduct.getVolume() <= 100)
                {
                    newProduct.setPosition(Position(this->storage.getProducts()[i]->getPosition()));
                    this->storage.addProduct(new Product(newProduct));
                    return true;
                }
                else
                {
                    double currVolume = 100 - volumeAtPos;
                    std::string name = newProduct.getProductName();
                    Date expDate = newProduct.getExpDate();
                    Date arrDate = newProduct.getArrDate();
                    std::string ManuName = newProduct.getManufacturerName();
                    Metric newType = newProduct.getType(); 
                    Position newPos = this->storage.getProducts()[i]->getPosition();
                    std::string newComment = newProduct.getComment();
                    this->storage.addProduct(new Product(name, expDate, arrDate, ManuName, newType, currVolume, newComment, newPos));

                    newProduct.setVolume(newProduct.getVolume()-currVolume);
                }
            }
        }
    }
    return false;
}

void Commands::addProductByData(Product& newProduct)
{
    Date date(newProduct.getArrDate());
    Log newLog(ADDED, newProduct.getProductName(), date, newProduct.getVolume());
    this->log.addLog(new Log(newLog));
    if(this->storage.getSize() != 0)
    {
        if(this->FillAvailableSpaces(newProduct))
        return;
    }

    if(newProduct.getVolume()>100)
    {
        std::cout << "Your product is in a high quantity so you need to break it into smaller portions." << std::endl;
        std::cout << "You have to input some new positions to store it in" << std::endl;
        while(newProduct.getVolume()>100)
        {
            std::cout << "Please, input position. Format is: section, shelf, number:" << std::endl;
            int a,b,c;
            std::cin >> a >> b >> c;
            std::cin.ignore();
            Position position(a,b,c);
            if(this->storage.getSize() != 0)
            {
            while(this->storage.HasMatchingPosition(position) == true || position.positionIsValid() == false)
            {
                std::cout << "This position is already taken/invalid, please input a new position for your product: " << std::endl;
                std::cin >> a >> b >> c;
                std::cin.ignore();
                position.setSection(a);
                position.setShelf(b);
                position.setNumber(c);
            }
            }
            double currVolume = 100;
            std::string name = newProduct.getProductName();
            Date expDate = newProduct.getExpDate();
            Date arrDate = newProduct.getArrDate();
            std::string ManuName = newProduct.getManufacturerName();
            Metric newType = newProduct.getType(); 
            std::string newComment = newProduct.getComment();
            this->storage.addProduct(new Product(name, expDate, arrDate, ManuName, newType, currVolume, newComment, position));
            newProduct.setVolume(newProduct.getVolume()-100);
        }
    }

    if(this->storage.HasMatchingPosition(newProduct.getPosition()) == false)
        {
            std::cout << "You have only one batch of the product to store. It was stored in the original input position" << std::endl;
            this->storage.addProduct(new Product(newProduct));
        }
    else
    {
        std::cout << "This is your last batch of this product left to store." << std::endl;
        std::cout << "The original input position is already taken, please input a new position for your last batch of this product: " << std::endl;
        bool check = false;
        while(this->storage.HasMatchingPosition(newProduct.getPosition()) == true || newProduct.getPosition().positionIsValid() == false)
        {
            if(check == true)
            std::cout << "This position is already taken/invalid. Please try again." << std::endl;
            check = true;
            int a,b,c;
            std::cin >> a >> b >> c;
            std::cin.ignore();
            newProduct.setPosition(Position(a,b,c));
        }
        this->storage.addProduct(new Product(newProduct));
    }
}

void Commands::print()
{
    this->storage.print();
}

void Commands::printWholeThing()
{
    this->storage.PrintWholeThing();
}

void Commands::ShowLog(const Date& from, const Date& to)
{
    if(from > to)
    {
        std::cout << "Invalid dates" << std::endl;
        return;
    }
    this->log.printWithDates(from,to);
}

void Commands::ShowLosses(const std::string& name, const double& price, const Date& from, const Date& to)
{
    if(this->log.getSize() == 0)
    {
        std::cout << "The log is empty" << std::endl;
        return;
    }

    if(from>to)
    {
        std::cout << "Invalid time period" << std::endl;
        return;
    }
    
    double losses = 0;
    for(int i = 0; i < this->log.getSize(); i++)
    {
        if(this->log.getLogs()[i]->getProductName() == name && 
            this->log.getLogs()[i]->getType() == CLEARED &&
            this->log.getLogs()[i]->getDateOfLog()>=from && 
            to >= this->log.getLogs()[i]->getDateOfLog())
        losses += this->log.getLogs()[i]->getQuantity();
    }

    if(losses == 0)
    std::cout << "You have no losses from this product for this time period" << std::endl;
    else
    std::cout << "You have lost " << losses*price << " leva from this product for this time period" << std::endl;
}

Storage Commands::getStorage()
{
    return this->storage;
}

LogArray Commands::getLogArray()
{
    return this->log;
}