#ifndef SELLSTANDARD_H
#define SELLSTANDARD_H

#include "user.h"

class SellStandard : public User {
public:
    SellStandard(const std::string& username, const std::string& password, const float& credit);
};

#endif