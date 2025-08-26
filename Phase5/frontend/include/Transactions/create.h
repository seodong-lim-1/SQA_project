#ifndef CREATE_H
#define CREATE_H

#include "transaction.h"

class Frontend;

class Create : public Transaction {
public:
    Create(Frontend& frontend);
    void processTransaction() override;
    
    User* getNewUser() const;
    void setNewUser(User* user);

    friend std::ostream& operator<<(std::ostream& os, const Create& obj);
protected:
    User* m_newUser;
};

#endif