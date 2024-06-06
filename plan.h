#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

// Plan class
class Plan
{
protected:
    std::string name;
    std::tm date;

public:
    Plan(std::string const &name, std::tm const &date)
        : name(name), date(date) {}

    std::string getName() const;

    std::tm getDate() const;

    void setName(const std::string &newName);

    void setDate(const std::tm &newDate);

    static bool startsWith(const std::string& line, const std::string& prefix);
};