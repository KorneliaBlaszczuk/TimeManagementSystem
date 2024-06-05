#include "reminder.h"
#include <chrono>
#include <iostream>

Reminder::Reminder(std::string const &name_ar, std::tm const &date, std::string details, Repetition repeat) : Plan(name_ar, date), description(details), repetition(repeat)
{
    if (name == "")
    {
        throw std::invalid_argument("Name of reminder cannot be empty.");
    }
};

void Reminder::print()
{
    char dateBuffer[20];
    strftime(dateBuffer, 20, "%Y-%m-%d %H:%M", &date);

    std::cout << std::left << std::setw(20) << name
              << std::setw(20) << dateBuffer
              << std::endl
              << description << std::endl;
};

void Reminder::setDescription(std::string const &new_description)
{
    if (new_description != "")
        description = new_description;
}

void Reminder::setRepetition(Repetition new_repetition)
{
    repetition = new_repetition;
}

std::string Reminder::getDetails() const
{
    return description;
}

std::string Reminder::getRepetitions() const
{
    switch (repetition)
    {
    case 1:
    {
        return "Everyday.";
    }
    case 2:
    {
        return "Every week.";
    }
    case 3:
    {
        return "Every month.";
    }
    default:
    {
        return "No repetition.";
    }
    };
}

void Reminder::changeDate(std::tm &time_now)
{
    if (tm_to_time_t(time_now) > tm_to_time_t(date))
    {
        switch (repetition)
        {
        case EVERYDAY:
            date.tm_mday += 1;
            break;
        case EVERY_WEEK:
            date.tm_mday += 7;
            break;
        case EVERY_MONTH:
            date.tm_mon += 1;
            break;
        }
        // normalizing date so it is correct
        std::mktime(&date);
    }
};
