#ifndef LOGIN_H
#define LOGIN_H

#include "transaction.h"

class Frontend;

class Login : public Transaction {
public:
    Login(Frontend& frontend);
    void processTransaction() override;

    User* getUser() const;
    std::string getUsername() const;
    std::string getPassword() const;

    void setUser(User* user);
    void setUsername(std::string username);
    void setPassword(std::string password);

protected:
    User* m_user;
    std::string m_username;
    std::string m_password;
};

#endif