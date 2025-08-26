#ifndef DELETE_H
#define DELETE_H

#include "transaction.h"

class Frontend;

class Delete : public Transaction {
public:
    Delete(Frontend& frontend);
    void processTransaction() override;

    friend std::ostream& operator<<(std::ostream& os, const Delete& obj);

    // TODO get deleted user
    // TODO set deleted user
protected:
    // TODO initialize deleted user with pattern m_<variableName>
};

#endif