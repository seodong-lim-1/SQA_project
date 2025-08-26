#ifndef BID_H
#define BID_H

#include "transaction.h"
#include "../item.h"

class Frontend;

class Bid : public Transaction {
public:
    Bid(Frontend& frontend);
    void processTransaction() override;

    Item* getEditedItem() const;
    void setEditedItem(Item* item);

    friend std::ostream& operator<<(std::ostream& os, const Bid& obj);
protected:
    Item* m_editedItem;  
};

#endif