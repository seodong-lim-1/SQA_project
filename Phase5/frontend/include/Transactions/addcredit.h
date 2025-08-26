#ifndef ADDCREDIT_H
#define ADDCREDIT_H

#include "transaction.h"
#include "Users/user.h"

class Frontend;

class AddCredit : public Transaction {
public:
    AddCredit(Frontend& frontend);
    void processTransaction() override;
    
    User* getEditedUser() const;
    void setEditedUser(User* user);

    friend std::ostream& operator<<(std::ostream& os, const AddCredit& obj);
protected:
    User* m_editedUser;
};

#endif
