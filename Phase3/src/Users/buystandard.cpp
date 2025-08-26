#include "../include/Users/buystandard.h"

// Constructs BuyStandard User with "BS" privileges
BuyStandard::BuyStandard(const std::string& username, const std::string& password, const float& credit) 
    : User(username, "BS", password, credit) {}