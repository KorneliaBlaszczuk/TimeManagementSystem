#pragma once
#include <string>
#include <fstream>

class User
{
    std::string userName;
    std::string eventsFile = "build/usersData/"+ userName + "_events.txt";
    std::string taskFile = "build/usersData/" + userName + "_tasks.txt";
    std::string compTaskFile = "build/usersData/" + userName + "_task_comp.txt";
    std::string reminderFile = "build/usersData/" + userName + "_reminders.txt";

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

    std::string getEventsFile() const
    {
        return eventsFile;
    }

    std::string getTaskFile() const
    {
        return taskFile;
    }

    std::string getCompTaskFile() const
    {
        return compTaskFile;
    }

    std::string getReminderFile() const
    {
        return reminderFile;
    }
};