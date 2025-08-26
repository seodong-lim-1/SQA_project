#include "../include/Transactions/login.h"
#include "../include/frontend.h"

// Constructs Login with no transaction code
Login::Login(Frontend& frontend) : Transaction(frontend, "") {}

void Login::processTransaction() {
    std::cout << "Processing Login Transaction..." << std::endl;

    getFrontend().setIsActive(true);
    getFrontend().setAvailableUsers();

    // Gets username from user
    std::string temp_username;
    std::cout << "Enter username: " << std::endl;
    std::cin >> temp_username >> std::ws;
    setUsername(temp_username);
    
    // Gets password from user
    std::string temp_password;
    std::cout << "Enter password: " << std::endl;
    std::cin >> temp_password >> std::ws;
    std::string hashedPassword = getFrontend().hashString(temp_password);
    setPassword(hashedPassword);

    // Gets user from available users
    bool userFound = false;
    for (User* user : getFrontend().getAvailableUsers()) {
        if (user->getUsername() == getUsername() && user->getPassword() == getPassword()) {
            setUser(user);
            userFound = true;   
            break;
        }
    }

    if (!userFound) {
        std::cout << "Error: Invalid Transaction. User does not exist." << std::endl;
        std::cout << "Login cancelled." << std::endl;
        return;
    }

    // Processes accepted user
    getFrontend().setAllowLogin(false);
    getFrontend().setAllowLogout(true);
    getFrontend().setCurrentUser(getUser());
    getFrontend().setAvailableItems();

    std::cout << "Login successful!" << std::endl;

    std::cout << "Welcome " << getUser()->getUsername() << "!" << std::endl;
}

User* Login::getUser() const {
    return m_user;
}

std::string Login::getUsername() const {
    return m_username;
}

std::string Login::getPassword() const {
    return m_password;
}

void Login::setUser(User* user) {
    m_user = user;
}

void Login::setUsername(std::string username) {
    m_username = username;
}

void Login::setPassword(std::string password) {
    m_password = password;
}
