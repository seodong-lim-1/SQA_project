#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
class Admin : public User {
    std::string privilege = "AA"; //admin privilage
};

#endif