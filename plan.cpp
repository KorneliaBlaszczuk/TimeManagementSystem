#include "plan.h"
#include <ctime>
#include <string>

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

void Plan::setDate(const std::tm &newDate)
{
    date = newDate;
}

bool Plan::startsWith(const std::string& line, const std::string& prefix) {
    return line.compare(0, prefix.size(), prefix) == 0;
}