#include "modes.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <ctime>
#include <fstream>

// function that makes an interface to work in settings mode (first run, adding users etc.)
int InitMode()
{
    std::cout << "Welcome to TimeSystem.\n";
    int choice;
    while (true)
    {
        std::cout << "Select an operation:\n"
                  << "1 - Creat a new user\n"
                  << "2 - Check all users\n"
                  << "3 - Delete an user \n"
                  << "4 - Go to User Mode\n"
                  << "5 - Exit\n"
                  << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (std::cin.fail())
        {
            std::cin.clear();                                                   // clear error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore remaining input
            std::cout << "Invalid input. Please enter a number between 1 and 5.\n";
            continue;
        }
        try
        {
            switch (choice)
            {
            case 1:
                std::cout << "\nCreating new user\n";
                break;
            case 2:
                std::cout << "\nTimeSystem Users:\n";
                break;
            case 3:
                std::cout << "\nDeleting an user\n";
                break;
            case 4:
                std::cout << "\nGoing into user mode\n";
                // first getting correct user name;
                // then going into UserMode(User &user);
                // after getting out of user mode, we need to finish program
                return 0;
            case 5:
                std::cout << "Goodbye!";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "Error: " << e.what() << "\n";
            // Clear cin state if an exception occurs
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
};

// function that makes an interface to work for already existing user
int UserMode(User &user)
{
    Calendar calendar;
    Interface interface;

    std::string UserName = user.getName();

    // creating name of files that will be used by that user
    std::string eventFile, taskFile, compTaskFile, reminderFile;

    eventFile = UserName + "_events.txt";
    taskFile = UserName + "_tasks.txt";
    compTaskFile = UserName + "_task_comp.txt";
    reminderFile = UserName + "_reminders.txt";

    interface.openFile(calendar, eventFile, taskFile, compTaskFile);
    // @TODO tutaj będzie do openFile trzeba dopisać pewnie reminders

    std::cout << "Welcome back "
              << UserName;
    int result = UserMenu(interface, calendar);
    return result;
}

// function that takes care of navigating through menu and call proper functionalities of program
int UserMenu(Interface &interface, Calendar &calendar)
{
    int choice;
    while (true)
    {
        std::cout << "\nSelect an operation:\n";
        std::cout << "1 - Display today's events\n";
        std::cout << "2 - Display events of the current week\n";
        std::cout << "3 - Display events of the current month\n";
        std::cout << "4 - Select month for the display of events\n";
        std::cout << "5 - Add an event\n";
        std::cout << "6 - Edit an event\n";
        std::cout << "7 - Display today's tasks\n";
        std::cout << "8 - Display tasks of the current week\n";
        std::cout << "9 - Display tasks of the current month\n";
        std::cout << "10 - Display completed tasks from within the month\n";
        std::cout << "11 - Add a task\n";
        std::cout << "12 - Edit a task\n";
        std::cout << "13 - Display today's reminders\n";
        std::cout << "14 - Display tomorrow's reminders\n";
        std::cout << "15 - Add a reminder\n";
        std::cout << "16 - Edit a reminder\n";
        std::cout << "17 - Start Pomodoro Mode\n";
        std::cout << "18 - Delete an event\n";
        std::cout << "19 - Delete a task\n";
        std::cout << "20 - Delete a reminder\n";
        std::cout << "21 - Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (std::cin.fail())
        {
            std::cin.clear();                                                   // clear error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore remaining input
            std::cout << "Invalid input. Please enter a number between 1 and 21.\n";
            continue;
        }

        std::tm today = getCurrentDate();
        std::tm endOfDay = today;
        endOfDay.tm_hour = 23;
        endOfDay.tm_min = 59;
        endOfDay.tm_sec = 59;

        std::tm weekStart, weekEnd;
        std::tm monthStart, monthEnd;

        try
        {
            switch (choice)
            {
            case 1:
                std::cout << "\nEvents for today:\n";
                interface.displayEventsInRange(calendar, today, endOfDay);
                break;
            case 2:
                getCurrentWeekRange(weekStart, weekEnd);
                std::cout << "\nEvents for the current week:\n";
                interface.displayEventsInRange(calendar, weekStart, weekEnd);
                break;
            case 3:
                getCurrentMonthRange(monthStart, monthEnd);
                std::cout << "\nEvents for the current month:\n";
                interface.displayEventsInRange(calendar, monthStart, monthEnd);
                break;
            case 4:
                interface.selectMonthAndDisplayEvents(calendar);
                break;
            case 5:
                interface.addEvent(calendar, "events.txt");
                break;
            case 6:
                interface.editEvent(calendar, "events.txt");
                break;
            case 7:
                std::cout << "\nTasks for today:\n";
                interface.displayTasksInRange(calendar, today, endOfDay);
                break;
            case 8:
                getCurrentWeekRange(weekStart, weekEnd);
                std::cout << "\nTasks for the current week:\n";
                interface.displayTasksInRange(calendar, weekStart, weekEnd);
                break;
            case 9:
                getCurrentMonthRange(monthStart, monthEnd);
                std::cout << "\nTasks for the current month:\n";
                interface.displayTasksInRange(calendar, monthStart, monthEnd);
                break;
            case 10:
                std::cout << "\nCompleted tasks within a month: \n";
                interface.displayTasksCompleted(calendar);
                break;
            case 11:
                interface.addTask(calendar, "tasks.txt", "tasks_completed.txt");
                break;
            case 12:
                interface.editTask(calendar, "tasks.txt", "tasks_completed.txt");
                break;
            case 13:
                std::cout << "\nToday's reminders:\n";
                interface.displayTodayReminders(calendar);
                break;
            case 14:
                std::cout << "\nTomorrow's reminders:\n";
                interface.displayTomorrowReminders(calendar);
                break;
            case 15:
                interface.addReminder(calendar, "reminders.txt");
                break;
            case 16:
                interface.editReminder(calendar, "reminders.txt");
                break;
            case 17:
                interface.PomodoroRun();
                break;
            case 18:
                interface.deleteEvent(calendar, "events.txt");
                break;
            case 19:
                interface.deleteTask(calendar, "tasks.txt");
                break;
            case 20:
                interface.deleteReminder(calendar, "reminders.txt");
                break;
            case 21:
                std::cout << "Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "Error: " << e.what() << "\n";
            // Clear cin state if an exception occurs
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}