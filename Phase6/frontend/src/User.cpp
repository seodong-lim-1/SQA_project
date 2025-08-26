#include "User.h"
#include "UserAccountsFile.h"
#include "TransactionFile.h"
/* The constructor method for a user object.
*/
User::User()
{
    this->loggedIn = false;
    this->availableCredit = 0.0;
    this->userType = UserType::NONE;
}

/*The destructor method for a user object.
*/
User::~User()
{
}

/*
* Description: Based on the passed in username, this method sets the user type for each 
* user to log them in and to print the appropriate MENU.
* 
* @param - username - username inputted by the user at login
* @return - returns true if login is successful
*/
bool User::login(const char* username, const char* password)
{
    UserAccountsFile accounts;
    for (auto &i : accounts.readUserFile())
    {
        if (i.username == std::string(username) && i.password == std::string(password))
        {
            this->username = username;
            this->userType = i.userType;
            this->availableCredit = i.availableCredit;
            this->loggedIn = true;
            return true;
        }
    }
    return false;
}

/*
* Description: This method sets the usertype to NONE, and the boolean value of "loggedin"
* to “false” when a user decides to log out.
* 
* @return - returns true if user is able to successfully log out
*/
bool User::logout()
{
    TransactionFile transactionFile;


    TransactionInfo transactionInfo = {
        this->username.c_str(),
        nullptr,
        nullptr,
        TransactionCode::END_OF_SESSION,
        this->userType,
        this->availableCredit,
        0.0,
        nullptr,
        0,
        0.0,
        0.0
    };

    transactionFile.appendToFile(transactionInfo);
    this->userType = UserType::NONE;
    this->loggedIn = false;
    
    return true;
}

/*
* Description: This method returns the full user type name, based on the passed in 
* user type for the current user.
*
* @param - usertype - User type of the user currently logged in 
* @return - returns a string with the appropriate user type full name 
*/
std::string User::getTypeName(UserType userType)
{
    switch (userType)
    {
    case UserType::AA:
        return "Admin";
        break;
    case UserType::FS:
        return "Full-Standard";
        break;
    case UserType::BS:
        return "Buy-Standard";
        break;
    case UserType::SS:
        return "Sell-Standard";
        break;
    case UserType::NONE:
        return "None";
        break;
    }
    return "";
}

std::string User::getTypeCode(UserType userType)
{
    switch (userType)
    {
    case UserType::AA:
        return "AA";
        break;
    case UserType::FS:
        return "FS";
        break;
    case UserType::BS:
        return "BS";
        break;
    case UserType::SS:
        return "SS";
        break;
    case UserType::NONE:
        return "None";
        break;
    }
    return "";
}

UserType User::getUserType(const char *typeCode)
{
    if (strcmp(typeCode, "AA") == 0)
    {
        return UserType::AA;
    }
    else if (strcmp(typeCode, "FS") == 0)
    {
        return UserType::FS;
    }
    else if (strcmp(typeCode, "BS") == 0)
    {
        return UserType::BS;
    }
    else if (strcmp(typeCode, "SS") == 0)
    {
        return UserType::SS;
    }
    return UserType::NONE;
}
