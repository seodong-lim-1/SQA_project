#ifndef USER_H
#define USER_H

#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

class User {
public:
    User(const std::string& username, const std::string& privilege, const std::string& password, const float& credit);
    virtual ~User();

    const std::string& getUsername() const;
    const std::string& getPrivilege() const;
    const std::string& getPassword() const;
    const float& getCredit() const;

    friend std::ostream& operator<<(std::ostream& os, const User& obj);

protected:
    std::string m_username;
    std::string m_privilege;
    std::string m_password;
    float m_credit;
};

#endif