#ifndef DELETE_H
#define DELETE_H

#include "transaction.h"

class Frontend;

class Delete : public Transaction {
public:
    Delete(Frontend& frontend);
    void processTransaction() override;

    User* getOldUser() const;
    void setOldUser(User* user);

    friend std::ostream& operator<<(std::ostream& os, const Delete& obj);
protected:
    User* m_oldUser;
};

#endif