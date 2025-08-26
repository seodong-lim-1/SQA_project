#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    std::string username = "";
    std::string privilege = "";
    float credit = 0.0;
};

#endif