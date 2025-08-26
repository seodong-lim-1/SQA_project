#ifndef ADVERTISE_H
#define ADVERTISE_H

#include "transaction.h"
#include "../item.h"

class Frontend;

class Advertise : public Transaction {
public:
    Advertise(Frontend& frontend);
    void processTransaction() override;

    Item* getNewItem() const;
    void setNewItem(Item* item);

    friend std::ostream& operator<<(std::ostream& os, const Advertise& obj);
protected:
    Item* m_newItem;
};

#endif