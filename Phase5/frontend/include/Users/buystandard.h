#ifndef BUYSTANDARD_H
#define BUYSTANDARD_H

#include "user.h"

class BuyStandard : public User {
public:
    BuyStandard(const std::string& username, const std::string& password, const float& credit);
};

#endif