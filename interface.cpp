#include "interface.h"
#include <limits>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>

int Interface::openFile(Calendar &calendar, std::string eventF, std::string tasksF, std::string completedT)
{
    std::ifstream eventsFile(eventF);
    if (!eventsFile)
    {
        std::cerr << "No events loaded.\n";
    }
    else
    {
        Event event("", {}, {}, "", {});
        while (Event::loadFromFile(eventsFile, event))
        {
            calendar.events.push_back(event);
            std::cout << std::endl; // Add a newline between events
        }
        eventsFile.close();
    }

    // Load Tasks Pending
    std::ifstream taskFile(tasksF);
    if (!taskFile)
    {
        std::cerr << "No pending tasks loaded.\n";
    }
    else
    {
        Task task("", {}, false, "", Task::PENDING);
        while (Task::loadFromFile(taskFile, task))
        {
            calendar.addTask(task);
        }

        taskFile.close();
    }

    // Load Tasks Completed
    std::ifstream completedFile(completedT);
    if (!completedFile)
    {
        std::cerr << "No completed tasks loaded.\n";
    }
    else
    {
        std::vector<Task> recentCompleted;
        Task ctask("", {}, false, "", Task::COMPLETED);
        while (Task::loadFromFile(completedFile, ctask))
        {
            if (!isOlderThanAMonth(ctask.getDate()))
            {
                recentCompleted.push_back(ctask);
                calendar.addTask(ctask);
            }
        }

        completedFile.close();

        Task::removeCompleted(recentCompleted);
    }

    return 0;
}

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

void Interface::displayTasksCompleted(const Calendar &calendar)
{
    std::cout << std::left << std::setw(20) << "Date"
              << std::setw(20) << "Name"
              << std::setw(20) << "Importance"
              << std::setw(20) << "Status"
              << "Progress Note" << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    for (const auto &task : calendar.tasks)
    {
        if (task.getProgressStatus() == Task::COMPLETED)
        {
            task.print();
        }
    }
}

void Interface::displayTodayReminders(const Calendar &calendar)
{
    return;
};

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

void Interface::editEvent(Calendar &calendar, std::string file)
{
    std::string name;
    std::cout << "Enter the name of the event to edit: ";
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

            std::ofstream eventFile(file); // Open the file for writing

            if (!eventFile)
            {
                std::cerr << "Couldn't edit events.txt.\n";
            }

            for (const auto &event : calendar.events)
            {
                event.saveToFile(eventFile);
            }

            eventFile.close();

            std::cout << "Event updated successfully.\n";
            return;
        }
    }

    std::cout << "Event not found.\n";
}

void Interface::editTask(Calendar &calendar, std::string taskFile, std::string completedTaskFile)
{
    std::string name;
    std::cout << "Enter the name of the task to edit: ";
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

            std::ofstream fileTask(taskFile); // Open the file for writing

            if (!fileTask)
            {
                std::cerr << "Couldn't edit tasks.txt.\n";
            }

            // Save each event to the file
            for (const auto &task : calendar.tasks)
            {
                if (task.getProgressStatus() == Task::PENDING)
                {
                    task.saveToFile(fileTask);
                }
            }

            // Close the file
            fileTask.close();

            std::ofstream completedFile(completedTaskFile);
            if (!completedFile)
            {
                std::cerr << "Couldn't edit tasks_completed.txt.\n";
                return;
            }

            std::vector<Task> completed;
            for (const auto &task : calendar.tasks)
            {
                if (task.getProgressStatus() == Task::COMPLETED && !isOlderThanAMonth(task.getDate()))
                {
                    task.saveToFile(completedFile);
                }
                else if (task.getProgressStatus() == Task::COMPLETED && isOlderThanAMonth(task.getDate()))
                {
                    completed.push_back(task);
                }
            }

            completedFile.close();

            Task::removeCompleted(completed);

            std::cout << "Task updated successfully.\n";
            return;
        }
    }

    std::cout << "Task not found.\n";
}

void Interface::editReminder(Calendar &calendar)
{
    return;
}

void Interface::addEvent(Calendar &calendar, std::string outFile)
{
    int year, month, day, startHour, startMinute, endHour, endMinute;
    std::string name, location;
    std::vector<std::string> attendees;
    std::string attendee;

    std::cout << "Enter event name: ";
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

    std::ofstream eventsFile(outFile); // Open the file for writing

    if (!eventsFile)
    {
        std::cerr << "Error opening file for writing\n";
    }

    // Save each event to the file
    for (const auto &event : calendar.events)
    {
        event.saveToFile(eventsFile);
    }

    // Close the file
    eventsFile.close();

    std::cout << "Events saved to file\n";
}

void Interface::addReminder(Calendar &calendar)
{
    int year, month, day;
    std::string name, details;
    int status;

    std::cout << "Enter reminder's name: ";
    std::getline(std::cin, name);
    while (name == "")
    {
        std::cin.clear();                                                   // clear
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore remaining input
        std::cout << "Name of reminder cannot be empty. Write valid name.\n";
        std::cin >> day;
    };
    std::cout << "Enter reminder's date year: ";
    std::cin >> year;
    while (2000 < 1 or year > 2100)
    {
        std::cin.clear();                                                   // clear
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore remaining input
        std::cout << "Invalid year. Please enter a number between 2000 and 2100.\n";
        std::cin >> day;
    };
    std::cout << "Enter reminder's date month: ";
    std::cin >> month;
    while (month < 1 or month > 12)
    {
        std::cin.clear();                                                   // clear
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore remaining input
        std::cout << "Invalid month. Please enter a number between 1 and 12.\n";
        std::cin >> day;
    };
    std::cout << "Enter reminder's date day: ";
    std::cin >> day;
    while (day < 1 || day > 31)
    {
        std::cin.clear();                                                   // clear
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore remaining input
        std::cout << "Invalid day. Please enter a number between 1 and 31.\n";
        std::cin >> day;
    };
    std::tm date = make_tm(year, month, day);

    std::cin.ignore();
    std::cout << "Enter reminder's details: ";
    std::getline(std::cin, details);

    std::cout << "Enter reminder's repetition (0 for no, 1 for everyday, 2 for every week, 3 for every month): ";
    std::cin >> status;
    Reminder::Repetition reminderRep;
    switch (status)
    {
    case 0:
        reminderRep = Reminder::NO;
        break;
    case 1:
        reminderRep = Reminder::EVERYDAY;
        break;
    case 2:
        reminderRep = Reminder::EVERY_WEEK;
        break;
    case 3:
        reminderRep = Reminder::EVERY_MONTH;
        break;
    default:
        while (status < 0 or status > 3)
        {
            std::cin.clear();                                                   // clear
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore remaining input
            std::cout << "Invalid input. Please enter a number between 0 and 3.\n";
            std::cin >> status;
        };
    }

    Reminder reminder(name, date, details, reminderRep);

    calendar.addReminder(reminder);
    std::cout << "Reminder added successfully.\n";

    std::ofstream reminderFile("reminders.txt"); // Open the file for writing

    if (!reminderFile)
    {
        std::cerr << "Error opening file for writing\n";
    }

    // Save each event to the file
    for (const auto &reminder : calendar.reminders)
    {
        reminder.saveToFile(reminderFile);
    }

    // Close the file
    reminderFile.close();

    std::ofstream completedTaskFile("tasks_completed.txt");
    if (!completedTaskFile)
    {
        std::cerr << "Error opening file tasks_completed.txt for writing\n";
        return;
    }

    std::vector<Task> completed;
    for (const auto &task : calendar.tasks)
    {
        if (task.getProgressStatus() == Task::COMPLETED)
        {
            task.saveToFile(completedTaskFile);
        }
        else if (task.getProgressStatus() == Task::COMPLETED && isOlderThanAMonth(task.getDate()))
        {
            completed.push_back(task);
        }
    }

    Task::removeCompleted(completed);

    std::cout << "Task saved to file\n";
};

void Interface::addTask(Calendar &calendar, std::string taskFile, std::string completedTaskFile)
{
    int year, month, day;
    std::string name, progressNote;
    bool important;
    int status;

    std::cout << "Enter task name: ";
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
        SubTask subtask(subtaskName, date, important, "", subtaskStatus);
        task.addToSubtask(subtask);
        std::cout << "Enter next subtask (or 'done' to finish): ";
    }

    calendar.addTask(task);
    std::cout << "Task added successfully.\n";

    std::ofstream file(taskFile); // Open the file for writing

    if (!file)
    {
        std::cerr << "Error opening file for writing\n";
    }

    // Save each event to the file
    for (const auto &task : calendar.tasks)
    {
        if (task.getProgressStatus() == Task::PENDING)
        {
            task.saveToFile(file);
        }
    }

    // Close the file
    file.close();

    std::ofstream fileCompleted(completedTaskFile);
    if (!fileCompleted)
    {
        std::cerr << "Error opening file tasks_completed.txt for writing\n";
        return;
    }

    std::vector<Task> completed;
    for (const auto &task : calendar.tasks)
    {
        if (task.getProgressStatus() == Task::COMPLETED)
        {
            task.saveToFile(fileCompleted);
        }
        else if (task.getProgressStatus() == Task::COMPLETED && isOlderThanAMonth(task.getDate()))
        {
            completed.push_back(task);
        }
    }

    fileCompleted.close();

    Task::removeCompleted(completed);

    std::cout << "Task saved to file\n";
}

void Interface::PomodoroRun()
{
    int choice;
    std::cout << "You are entering Pomodoro mode.\n"
              << "Possible modes to choose from are: \n"
              << "1 - short: 3 repetitions, 30 minutes blocks, 5 minutes breaks;\n"
              << "2 - medium: 4 repetitions, 30 minutes blocks, 7 minutes breaks;\n"
              << "3 - long: 6 repetitions, 30 minutes blocks, 10 minutes breaks;\n"
              << "4 - intense: 5 repetitions, 45 minutes blocks, 10 minutes breaks;\n"
              << "5 - exam: 4 repetitions, 75 minutes blocks, 15 minutes breaks."
              << "Which one do you choose?\n";
    std::cin >> choice;
    while (choice != 1 and choice != 2 and choice != 3 and choice != 4 and choice != 5)
    {
        std::cin.clear();                                                   // clear
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore remaining input
        std::cout << "Invalid input. Please enter a number between 1 and 5.\n";
        std::cin >> choice;
    };
    switch (choice)
    {
    case 1:
    {
        Pomodoro pm(3, 30, 5);
        pm.go();
        break;
    }
    case 2:
    {
        Pomodoro pm(4, 30, 7);
        pm.go();
        break;
    }
    case 3:
    {
        Pomodoro pm(6, 30, 10);
        pm.go();
        break;
    }
    case 4:
    {
        Pomodoro pm(5, 45, 10);
        pm.go();
        break;
    }
    case 5:
    {
        Pomodoro pm(4, 75, 15);
        pm.go();
        break;
    }
    };
    return;
}