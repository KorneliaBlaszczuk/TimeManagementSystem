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
    // here needs to be checked if user exists in file with users
    // getting user name from program arguments
    std::string name = argv[1];
    // if user is correct ... needs to be done
    User user(name); // in final version it will be from file
    UserMode(user);
    // if name is incorrect then
    std::cerr << "User of the given name is not existing in TimeSystem. Going into Init Mode.";
    // and InitMode();
    return 0;
}
