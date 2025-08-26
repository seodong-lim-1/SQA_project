#ifndef FULLSTANDARD_H
#define FULLSTANDARD_H

#include "user.h"

class FullStandard : public User {
public:
    FullStandard(const std::string& username, const std::string& password, const float& credit);
};

#endif