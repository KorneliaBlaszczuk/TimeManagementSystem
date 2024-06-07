#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

// Plan class
class Plan
/*
Base class for all classes consisting of planning in projects. It has name and data as an attributes.
*/
{
protected:
    std::string name;
    std::tm date;

public:
    // constructor of plan object
    Plan(std::string const &name, std::tm const &date)
        : name(name), date(date) {
        this->date.tm_isdst = -1;
    };

    // Getting name of the plan object.
    std::string getName() const;

    // Getting date in tm format of the plan object.
    std::tm getDate() const;

    // Setting new name to plan object.
    void setName(const std::string &newName);

    // Setting new date (in tm format) to object plan.
    void setDate(const std::tm &newDate);

    // Checks if the line has the same prefix as given.
    //@TOCHECK - czy to ma byc w tej klasie? Moze pomocnicze funkcje?
    static bool startsWith(const std::string &line, const std::string &prefix);
};