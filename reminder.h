#pragma once
#include <string>
#include "plan.h"
#include "functions.h"

class Reminder : public Plan
{

    std::string description;
    int repetition;

    friend class Calendar;

    // method that will be used to update next appearance of reminder by calendar
    void changeDate(std::tm &time_now);

public:
    enum Repetition
    {
        NO,
        EVERYDAY,
        EVERY_WEEK,
        EVERY_MONTH
    };
    Reminder(std::string const &name_ar, std::tm const &date, std::string details, Repetition repeat);
    // method to return information from reminder
    void print();
    // method to change additional information for reminder
    void setDescription(std::string const &new_description);
    // method to change how often reminder is repeated
    void setRepetition(Repetition new_repetition);
    // method to get additional information from reminder
    std::string getDetails() const;
    // method to get how reminder is repeated
    std::string getRepetitions() const;

    // TODO
    void saveToFile(std::ofstream &outFile) const;
};
