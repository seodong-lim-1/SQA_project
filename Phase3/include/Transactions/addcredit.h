#ifndef ADDCREDIT_H
#define ADDCREDIT_H

#include "transaction.h"
#include "Users/user.h"

class Frontend;

class AddCredit : public Transaction {
public:
    AddCredit(Frontend& frontend);
    void processTransaction() override;

    friend std::ostream& operator<<(std::ostream& os, const AddCredit& obj);
    
    User* getNewCredit() const;
    void setNewCredit(User* user);
protected:
    User* m_newCredit;
};

#endif
