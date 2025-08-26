#include "../include/Users/user.h"

User::User(const std::string& username, const std::string& privilege, const std::string& password, const float& credit) {
    m_username = username;
    m_privilege = privilege;
    m_password = password;
    m_credit = credit;
}

User::~User(){}

const std::string& User::getUsername() const {
    return m_username;
}

const std::string& User::getPrivilege() const {
    return m_privilege;
}

const std::string& User::getPassword() const {
    return m_password;
}

const float& User::getCredit() const {
    return m_credit;
}

// Overrides to string method
std::ostream& operator<<(std::ostream& os, const User& obj) {
    // Formats user name to 15 characters
    std::string username = obj.getUsername();
    username.resize(15, ' ');

    std::string privilege = obj.getPrivilege();
    
    // Declares and initializes stringstream
    std::stringstream ss;

    // Formats credit to 9 characters
    int creditVal = (int)obj.getCredit();
    ss << std::setfill('0') << std::setw(6) << creditVal << ".00";
    std::string credit = ss.str();
    ss.str(std::string());  // Clears stringstream

    // Formats user password to 25 characters
    std::string password = obj.getPassword();
    password.resize(25, ' ');

    return (os << username << " " << privilege << " " << credit << " " << password);
}