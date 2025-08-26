#ifndef FRONTEND_H
#define FRONTEND_H

#include <string>
#include <fstream>

class Frontend  {
public:
    std::string currentUser; // TODO replace string object with User object
    bool start = false;
    std::fstream* readCurrentUsers();
    std::fstream* readAvailableItems();
    std::fstream* writeDailyTransaction();
};


#endif