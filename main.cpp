#include <iostream>
#include <stdexcept>
#include <ctime>
#include <fstream>
#include "modes.h"
#include "user.h"

int main(int argc, char *argv[])
{
    // going to initialization mode if there was no user name given at starting
    if (argc < 2)
    {
        InitMode();
    }
    else
    {
        std::string name = argv[1];
        if (name, "build/usersData/users.txt")
        {
            User user(name);
            UserMode(user);
        }
        else
        {
            std::cerr << "User of the given name is not existing in TimeSystem. Going into Init Mode.";
            InitMode();
        }
    }
    return 0;
};