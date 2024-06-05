#include <iostream>
#include <limits>
#include <stdexcept>
#include <ctime>
#include "calendar.h"
#include "interface.h"
#include "task.h"
#include "event.h"
#include "reminder.h"

int main()
{
    Calendar calendar;
    Interface interface;

    std::cout << "Welcome back\n";

    int choice;
    while (true)
    {
        std::cout << "\nSelect an operation:\n";
        std::cout << "1 - Display today's events\n";
        std::cout << "2 - Display events of the current week\n";
        std::cout << "3 - Display events of the current month\n";
        std::cout << "4 - Select month for the display of events\n";
        std::cout << "5 - Add an event\n";
        std::cout << "6 - Display today's tasks\n";
        std::cout << "7 - Display tasks of the current week\n";
        std::cout << "8 - Display tasks of the current month\n";
        std::cout << "9 - Add a task\n";
        std::cout << "10 - Edit an event\n";
        std::cout << "11 - Edit a task\n";
        std::cout << "12 - Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (std::cin.fail())
        {
            std::cin.clear();                                                   // clear error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore remaining input
            std::cout << "Invalid input. Please enter a number between 1 and 12.\n";
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
                interface.addEvent(calendar);
                break;
            case 6:
                std::cout << "\nTasks for today:\n";
                interface.displayTasksInRange(calendar, today, endOfDay);
                break;
            case 7:
                getCurrentWeekRange(weekStart, weekEnd);
                std::cout << "\nTasks for the current week:\n";
                interface.displayTasksInRange(calendar, weekStart, weekEnd);
                break;
            case 8:
                getCurrentMonthRange(monthStart, monthEnd);
                std::cout << "\nTasks for the current month:\n";
                interface.displayTasksInRange(calendar, monthStart, monthEnd);
                break;
            case 9:
                interface.addTask(calendar);
                break;
            case 10:
                interface.editEvent(calendar);
                break;
            case 11:
                interface.editTask(calendar);
                break;
            case 12:
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

    return 0;
}
