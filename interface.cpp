#include "interface.h"
#include <iomanip>
#include <iostream>
#include <ctime>
#include <vector>
#include <string>

void Interface::displayCalendar(const Calendar &calendar)
{
    std::cout << std::left << std::setw(20) << "Start Date"
              << std::setw(20) << "End Date"
              << std::setw(20) << "Location"
              << "Attendees" << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    for (const auto &event : calendar.events)
    {
        event.print();
    }
}

void Interface::displayEventsInRange(const Calendar &calendar, const std::tm &start, const std::tm &end)
{
    auto events = calendar.filterEvents(start, end);
    std::cout << std::left << std::setw(20) << "Name" << std::setw(20) << "Start Date"
              << std::setw(20) << "End Date"
              << std::setw(20) << "Location"
              << "Attendees" << std::endl;
    std::cout << std::string(100, '-') << std::endl;

    for (const auto &event : events)
    {
        event.print();
    }
}

void Interface::displayTasksInRange(const Calendar &calendar, const std::tm &start, const std::tm &end)
{
    auto tasks = calendar.filterTasks(start, end);
    std::cout << std::left << std::setw(20) << "Date"
              << std::setw(20) << "Name"
              << std::setw(20) << "Importance"
              << std::setw(20) << "Status"
              << "Progress Note" << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    for (const auto &task : tasks)
    {
        task.print();
    }
}

void Interface::selectMonthAndDisplayEvents(Calendar &calendar)
{
    int startYear, startMonth, endYear, endMonth;
    std::string input;

    // Get current date
    std::tm currentDate = getCurrentDate();
    int currentYear = currentDate.tm_year + 1900;
    int currentMonth = currentDate.tm_mon + 1;

    // Prompt for start month
    std::cout << "Enter the start month (1-12) or press Enter for the current month: ";
    std::getline(std::cin, input);
    if (input.empty())
    {
        startMonth = currentMonth;
    }
    else
    {
        startMonth = std::stoi(input);
        if (startMonth < 1 || startMonth > 12)
        {
            std::cout << "Invalid start month. Please enter a number between 1 and 12.\n";
            return;
        }
    }

    // Prompt for start year
    std::cout << "Enter the start year or press Enter for the current year: ";
    std::getline(std::cin, input);
    if (input.empty())
    {
        startYear = currentYear;
    }
    else
    {
        startYear = std::stoi(input);
        if (startYear < 2000 || startYear > 2100)
        {
            std::cout << "Invalid start year. Please enter a year between 2000 and 2100.\n";
            return;
        }
    }

    // Prompt for end month
    std::cout << "Enter the end month (1-12) or press Enter for the current month: ";
    std::getline(std::cin, input);
    if (input.empty())
    {
        endMonth = currentMonth;
    }
    else
    {
        endMonth = std::stoi(input);
        if (endMonth < 1 || endMonth > 12)
        {
            std::cout << "Invalid end month. Please enter a number between 1 and 12.\n";
            return;
        }
    }

    // Prompt for end year
    std::cout << "Enter the end year or press Enter for the current year: ";
    std::getline(std::cin, input);
    if (input.empty())
    {
        endYear = currentYear;
    }
    else
    {
        endYear = std::stoi(input);
        if (endYear < 2000 || endYear > 2100)
        {
            std::cout << "Invalid end year. Please enter a year between 2000 and 2100.\n";
            return;
        }
    }

    // Create tm structures for the start and end dates
    std::tm monthStart = make_tm(startYear, startMonth, 1);
    std::tm monthEnd = make_tm(endYear, endMonth, 1);

    // Adjust monthEnd to the last day of the end month
    monthEnd.tm_mon += 1; // Move to the next month
    monthEnd.tm_mday = 0; // Set to the last day of the previous month
    mktime(&monthEnd);

    std::cout << "\nEvents from " << startMonth << "/" << startYear << " to " << endMonth << "/" << endYear << ":\n";
    displayEventsInRange(calendar, monthStart, monthEnd);
}

void Interface::editEvent(Calendar &calendar)
{
    std::string name;
    std::cout << "Enter the name of the event to edit: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    for (auto &event : calendar.events)
    {
        if (event.getName() == name)
        {
            std::string newName, location, input;
            int year, month, day, hour, minute;
            std::tm start = event.getStart();
            std::tm end = event.getEnd();
            std::vector<std::string> attendees = event.getAttendees();

            // Edit name
            std::cout << "Enter new name (or press Enter to keep current): ";
            std::getline(std::cin, newName);
            if (!newName.empty())
                event.setName(newName);

            // Edit start date and time
            std::cout << "Enter new start year (or press Enter to keep current): ";
            std::getline(std::cin, input);
            if (!input.empty())
                start.tm_year = std::stoi(input) - 1900;

            std::cout << "Enter new start month: ";
            std::getline(std::cin, input);
            if (!input.empty())
                start.tm_mon = std::stoi(input) - 1;

            std::cout << "Enter new start day: ";
            std::getline(std::cin, input);
            if (!input.empty())
                start.tm_mday = std::stoi(input);

            std::cout << "Enter new start hour: ";
            std::getline(std::cin, input);
            if (!input.empty())
                start.tm_hour = std::stoi(input);

            std::cout << "Enter new start minute: ";
            std::getline(std::cin, input);
            if (!input.empty())
                start.tm_min = std::stoi(input);

            event.setStart(start);

            // Edit end date and time
            std::cout << "Enter new end year (or press Enter to keep current): ";
            std::getline(std::cin, input);
            if (!input.empty())
                end.tm_year = std::stoi(input) - 1900;

            std::cout << "Enter new end month: ";
            std::getline(std::cin, input);
            if (!input.empty())
                end.tm_mon = std::stoi(input) - 1;

            std::cout << "Enter new end day: ";
            std::getline(std::cin, input);
            if (!input.empty())
                end.tm_mday = std::stoi(input);

            std::cout << "Enter new end hour: ";
            std::getline(std::cin, input);
            if (!input.empty())
                end.tm_hour = std::stoi(input);

            std::cout << "Enter new end minute: ";
            std::getline(std::cin, input);
            if (!input.empty())
                end.tm_min = std::stoi(input);

            event.setEnd(end);

            // Edit location
            std::cout << "Enter new location (or press Enter to keep current): ";
            std::getline(std::cin, location);
            if (!location.empty())
                event.setLocation(location);

            // Edit attendees
            std::cout << "Enter new attendees (type 'done' to finish, or press Enter to keep current): ";
            attendees.clear();
            while (std::getline(std::cin, input) && input != "done")
            {
                if (input.empty())
                {
                    attendees = event.getAttendees();
                    break;
                }
                attendees.push_back(input);
            }
            if (!attendees.empty())
            {
                event.setAttendees(attendees);
            }

            std::cout << "Event updated successfully.\n";
            return;
        }
    }

    std::cout << "Event not found.\n";
}

void Interface::editTask(Calendar &calendar)
{
    std::string name;
    std::cout << "Enter the name of the task to edit: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    for (auto &task : calendar.tasks)
    {
        if (task.getName() == name)
        {
            std::string newName, progressNote, input;
            bool important;
            int year, month, day, statusInt;
            Task::Status status;
            std::tm date = task.getDate();

            // Edit name
            std::cout << "Enter new name (or press Enter to keep current): ";
            std::getline(std::cin, newName);
            if (!newName.empty())
                task.setName(newName);

            // Edit date
            std::cout << "Enter new year (or press Enter to keep current): ";
            std::getline(std::cin, input);
            if (!input.empty())
                date.tm_year = std::stoi(input) - 1900;

            std::cout << "Enter new month: ";
            std::getline(std::cin, input);
            if (!input.empty())
                date.tm_mon = std::stoi(input) - 1;

            std::cout << "Enter new day: ";
            std::getline(std::cin, input);
            if (!input.empty())
                date.tm_mday = std::stoi(input);

            task.setDate(date);

            // Edit importance
            std::cout << "Is the task important? (1 for yes, 0 for no, or press Enter to keep current): ";
            std::getline(std::cin, input);
            if (!input.empty())
            {
                important = std::stoi(input);
                task.setImportant(important);
            }

            // Edit progress note
            std::cout << "Enter new progress note (or press Enter to keep current): ";
            std::getline(std::cin, progressNote);
            if (!progressNote.empty())
                task.setProgressNote(progressNote);

            // Edit status
            std::cout << "Enter new status (0 for pending, 1 for completed, or press Enter to keep current): ";
            std::getline(std::cin, input);
            if (!input.empty())
            {
                statusInt = std::stoi(input);
                status = statusInt == 0 ? Task::PENDING : Task::COMPLETED;
                task.setStatus(status);
            }

            std::cout << "Task updated successfully.\n";
            return;
        }
    }

    std::cout << "Task not found.\n";
}

void Interface::addEvent(Calendar &calendar)
{
    int year, month, day, startHour, startMinute, endHour, endMinute;
    std::string name, location;
    std::vector<std::string> attendees;
    std::string attendee;

    std::cout << "Enter event name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter event start year: ";
    std::cin >> year;
    if (year < 2000 || year > 2100)
    {
        std::cout << "Invalid year: you can add event from 2000 to 2100\n";
        return;
    }
    std::cout << "Enter event start month: ";
    std::cin >> month;
    if (month < 1 || month > 12)
    {
        std::cout << "Invalid month\n";
        return;
    }
    std::cout << "Enter event start day: ";
    std::cin >> day;
    if (day < 1 || day > 31)
    {
        std::cout << "Invalid day\n";
        return;
    }
    std::cout << "Enter event start hour: ";
    std::cin >> startHour;
    if (startHour < 0 || startHour > 24)
    {
        std::cout << "Invalid start hour\n";
        return;
    }
    std::cout << "Enter event start minute: ";
    std::cin >> startMinute;
    if (startMinute < 0 || startMinute > 59)
    {
        std::cout << "Invalid start minute\n";
        return;
    }
    std::tm start = make_tm(year, month, day, startHour, startMinute);

    std::cout << "Enter event end hour: ";
    std::cin >> endHour;
    if (endHour < 0 || endHour > 24)
    {
        std::cout << "Invalid end hour\n";
        return;
    }
    std::cout << "Enter event end minute: ";
    std::cin >> endMinute;
    if (endMinute < 0 || endMinute > 59)
    {
        std::cout << "Invalid end minute\n";
        return;
    }
    std::tm end = make_tm(year, month, day, endHour, endMinute);

    std::cin.ignore();
    std::cout << "Enter event location: ";
    std::getline(std::cin, location);

    std::cout << "Enter event attendees (enter 'done' to finish): ";
    while (std::cin >> attendee && attendee != "done")
    {
        attendees.push_back(attendee);
    }

    Event event(name, start, end, location, attendees);
    calendar.addEvent(event);
    std::cout << "Event added successfully.\n";
}

void Interface::addTask(Calendar &calendar)
{
    int year, month, day;
    std::string name, progressNote;
    bool important;
    int status;

    std::cout << "Enter task name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter task date year: ";
    std::cin >> year;
    if (year < 2000 || year > 2100)
    {
        std::cout << "Invalid year: you can add event from 2000 to 2100\n";
        return;
    }
    std::cout << "Enter task date month: ";
    std::cin >> month;
    if (month < 1 || month > 12)
    {
        std::cout << "Invalid month\n";
        return;
    }
    std::cout << "Enter task date day: ";
    std::cin >> day;
    if (day < 1 || day > 31)
    {
        std::cout << "Invalid day\n";
        return;
    }
    std::tm date = make_tm(year, month, day);

    std::cout << "Is the task important? (1 for yes, 0 for no): ";
    std::cin >> important;

    std::cin.ignore();
    std::cout << "Enter progress note: ";
    std::getline(std::cin, progressNote);

    std::cout << "Enter task status (0 for pending, 1 for completed): ";
    std::cin >> status;

    Task::Status taskStatus = (status == 1) ? Task::COMPLETED : Task::PENDING;
    Task task(name, date, important, progressNote, taskStatus);

    // Optionally, add subtasks
    std::string subtaskName;
    std::cout << "Enter subtasks (enter 'done' to finish): ";
    while (std::cin.ignore(), std::getline(std::cin, subtaskName) && subtaskName != "done")
    {
        std::cout << "Enter subtask status (0 for pending, 1 for completed): ";
        std::cin >> status;
        Task::Status subtaskStatus = (status == 1) ? Task::COMPLETED : Task::PENDING;
        Task subtask(subtaskName, date, important, "", subtaskStatus);
        task.addToSubtask(subtask);
        std::cout << "Enter next subtask (or 'done' to finish): ";
    }

    calendar.addTask(task);
    std::cout << "Task added successfully.\n";
}