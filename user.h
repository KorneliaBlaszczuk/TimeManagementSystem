#pragma once
#include <string>

class User
{
    std::string userName;

public:
    User(std::string const &name) : userName(name)
    {
        if (name == "")
        {
            throw std::invalid_argument("User name cannot be empty. It needs to have at least one character.");
        }
    };
    std::string getName() const
    {
        return userName;
    };

    void setName(std::string const &newName)
    {
        if (newName != "")
        {
            userName = newName;
        }
    };
};