#include "../include/Users/fullstandard.h"

// Constructs FullStandard User with "FS" privileges
FullStandard::FullStandard(const std::string& username, const std::string& password, const float& credit) 
    : User(username, "FS", password, credit) {}