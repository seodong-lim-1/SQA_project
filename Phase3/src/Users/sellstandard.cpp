#include "../include/Users/sellstandard.h"

// Constructs SellStandard User with "SS" privileges
SellStandard::SellStandard(const std::string& username, const std::string& password, const float& credit) 
    : User(username, "SS", password, credit) {}