#include "plan.h"

std::string Plan::getName() const
{
    return name;
}

std::tm Plan::getDate() const
{
    return date;
}

void Plan::setName(const std::string &newName)
{
    if (newName != "")
        name = newName;
}
