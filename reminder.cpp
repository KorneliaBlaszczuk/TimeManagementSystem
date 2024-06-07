#include "reminder.h"
#include <chrono>
#include <iostream>
#include <ctime>
#include <fstream>

Reminder::Reminder(std::string const &name_ar, std::tm const &date, std::string details, Repetition repeat) : Plan(name_ar, date), description(details), repetition(repeat)
{
    if (name == "")
    {
        throw std::invalid_argument("Name of reminder cannot be empty.");
    }
};

void Reminder::print() const
{
    char dateBuffer[20];
    strftime(dateBuffer, 20, "%Y-%m-%d", &date);

    std::cout << std::left << std::setw(20) << dateBuffer
              << std::setw(20) << name
              << std::setw(40) << description
              << std::setw(20) << getRepetitions()
              << std::endl;
    return;
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
    if (repetition != NO)
    {
        while (tm_to_time_t(time_now) > tm_to_time_t(date))
        {
            switch (repetition)
            {
            case EVERYDAY:
                date.tm_mday += 1;
                continue;
                ;
            case EVERY_WEEK:
                date.tm_mday += 7;
                continue;
            case EVERY_MONTH:
                date.tm_mon += 1;
            default:
                continue;
            }
        }
        // normalizing date so it is correct
        std::time_t temp = std::mktime(&date);
        date = *std::localtime(&temp);
    }
};

void Reminder::saveToFile(std::ofstream &outFile) const
{
    outFile << "Reminder Name: " << name << "\n";
    outFile << "Date: " << std::put_time(&date, "%Y-%m-%d") << "\n";
    outFile << "Details: " << description << "\n";
    outFile << "Repetition: " << repetition << "\n";
}

bool Reminder::loadFromFile(std::ifstream &inFile, Reminder &reminder)
{
    std::tm time_now = getCurrentDate();
    std::string line;
    if (!std::getline(inFile, line) || !startsWith(line, "Reminder Name:"))
    {
        return false;
    }

    std::string name = line.substr(15); // Length of "Reminder Name: "

    std::getline(inFile, line);
    std::string dateStr = line.substr(6); // Length of "Date: "

    std::getline(inFile, line);
    std::string description = line.substr(9); // Length of "Details: "

    std::getline(inFile, line);
    std::string repetitionStr = line.substr(12); // Length of "Repetition: "
    int rep = std::stoi(repetitionStr);

    // Parse the date
    int year, month, day;
    if (std::sscanf(dateStr.c_str(), "%d-%d-%d", &year, &month, &day) != 3)
    {
        return false;
    }
    std::tm date = make_tm(year, month, day, 0, 0); // Assuming no time information is provided

    // Parse the repetition
    Repetition repetition;
    if (rep == 0)
    {
        repetition = NO;
    }
    else if (rep == 1)
    {
        repetition = EVERYDAY;
    }
    else if (rep == 2)
    {
        repetition = EVERY_WEEK;
    }
    else if (rep == 3)
    {
        repetition = EVERY_MONTH;
    }
    else
    {
        return false; // Unknown repetition value
    }

    reminder = Reminder(name, date, description, repetition);
    // Update of reminder date
    reminder.changeDate(time_now);
    return true;
}