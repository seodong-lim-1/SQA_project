#include "../include/Users/admin.h"

// Constructs Admin User with "AA" privileges
Admin::Admin(const std::string& username, const std::string& password, const float& credit) 
    : User(username, "AA", password, credit) {}
