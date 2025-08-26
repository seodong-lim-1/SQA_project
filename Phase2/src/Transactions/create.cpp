#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class User
{
private:
    std::string username;
    std::string userType;
    float credit;

public:
    // Constructor
    User(std::string uname, std::string uType, float cred)
    {
        username = uname;
        userType = uType;
        credit = cred;
    }

    // Getter functions
    std::string getUsername() const
    {
        return username;
    }

    std::string getUserType() const
    {
        return userType;
    }

    float getCredit() const
    {
        return credit;
    }

    // Setter functions
    void setUsername(std::string uname)
    {
        username = uname;
    }

    void setUserType(std::string uType)
    {
        userType = uType;
    }

    void setCredit(float cred)
    {
        credit = cred;
    }
};

class create
{
private:
    std::vector<User> users;

public:
    // Function to create a new user
    void createUser(std::string adminUser)
    {
        // Check if logged in as admin user
        if (adminUser != "admin")
        {
            std::cout << "Error: Only admin user can create new users with privileges.\n";
            return;
        }

        // Get the new username
        std::string newUsername;
        std::cout << "Enter the new username: ";
        std::cin >> newUsername;

        //Check if the new username is too long if (newUsername.length() > 15)
        {
            std::cout << "Error: New username is too long (maximum length is 15 characters).\n";
            return;
        }

        // Check if the new username already exists
        for (int i = 0; i < static_cast<int>(users.size()); i++)
        {
            if (users[i].getUsername() == newUsername)
            {
                std::cout << "Error: New username already exists.\n";
                return;
            }
        }

        // Get the user type
        std::string userType;
        std::cout << "Enter the user type (admin, full-standard, buy-standard, sell-standard): ";
        std::cin >> userType;

        // Check if the user type is valid
        if (userType != "admin" && userType != "full-standard" && userType != "buy-standard" && userType != "sell-standard")
        {
            std::cout << "Error: Invalid user type.\n";
            return;
        }

        // Get the credit
        float credit;
        std::cout << "Enter the credit: ";
        std::cin >> credit;

        // Check if the credit is within the limit
        if (credit > 999999.0)
        {
            std::cout << "Error: Credit is too high (maximum credit is 999,999).\n";
            return;
        }

        // Create the new user and add it to the list of users
        User newUser(newUsername, userType, credit);
        users.push_back(newUser);

        // Save the new user information to the daily transaction file
        std::ofstream dailyTransactionFile;
        dailyTransactionFile.open("daily_transaction.txt", std::ios::app);
        if (dailyTransactionFile.is_open())
        {
            dailyTransactionFile << "CREATE " << newUsername << " " << userType << " " << credit << std::endl;
            dailyTransactionFile.close();
        }
        else
        {
            std::cout << "Error: Could not save new user information to the daily transaction file.\n";
        }

        std::cout << " New user created" << std::endl;
    }
};