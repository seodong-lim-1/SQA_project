#ifndef BID_H
#define BID_H

#include "transaction.h"
#include "../item.h"

class Frontend;

class Bid : public Transaction {
public:
    Bid(Frontend& frontend);
    void processTransaction() override;

    friend std::ostream& operator<<(std::ostream& os, const Bid& obj);

    Item* getItem() const;
    void setItem(Item* item);
protected:
    Item* m_editedItem;  
};

#endif