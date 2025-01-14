#pragma once
#include <string>
#include "plan.h"
#include "functions.h"

class Reminder : public Plan
{

    std::string description;
    int repetition;

    friend class Calendar;
public:
    enum Repetition
    {
        NO,
        EVERYDAY,
        EVERY_WEEK,
        EVERY_MONTH
    };
    Reminder(std::string const &name_ar, std::tm const &date, std::string details, Repetition repeat);
    // method to print object info in cout
    void print() const;
    // method to change additional information for reminder
    void setDescription(std::string const &new_description);
    // method to change how often reminder is repeated
    void setRepetition(Repetition new_repetition);
    // method to get additional information from reminder
    std::string getDetails() const;
    // method to get how reminder is repeated
    std::string getRepetitions() const;

    void changeDate(std::tm &time_now);

    void saveToFile(std::ofstream &outFile) const;
    static bool loadFromFile(std::ifstream& inFile, Reminder& reminder);
};
