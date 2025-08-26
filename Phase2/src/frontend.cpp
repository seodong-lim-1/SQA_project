#include "../include/frontend.h"

// reads or creates the Current_User_Accounts.txt file
std::fstream* Frontend::readCurrentUsers()
{
    std::fstream* file = new std::fstream;
    file->open("Current_User_Accounts.txt", std::ios::in | std::ios::out | std::ios::app);
    return file;
}

// reads or creates the Available_Items.txt file
std::fstream* Frontend::readAvailableItems()
{
    std::fstream* file = new std::fstream;
    file->open("Available_Items.txt", std::ios::in | std::ios::out | std::ios::app);
    return file;
}

// writes to or creates the Daily_Transaction.txt file
std::fstream* Frontend::writeDailyTransaction()
{
    std::fstream* file = new std::fstream;
    file->open("Daily_Transaction.txt", std::ios::in | std::ios::out | std::ios::app);
    return file;
}