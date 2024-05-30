#include "calendar_v_3.h"

int main() {
    Calendar calendar;
    Interface interface;


    std::cout << "Welcome back\n";

    int choice;
    while (true) {
        std::cout << "\nSelect an operation:\n";
        std::cout << "1 - Display today's events\n";
        std::cout << "2 - Display events of the current week\n";
        std::cout << "3 - Display events of the current month\n";
        std::cout << "4 - Add an event\n";
        std::cout << "5 - Display today's tasks\n";
        std::cout << "6 - Display tasks of the current week\n";
        std::cout << "7 - Display tasks of the current month\n";
        std::cout << "8 - Add a task\n";
        std::cout << "9 - Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        std::tm today = getCurrentDate();
        std::tm endOfDay = today;
        endOfDay.tm_hour = 23;
        endOfDay.tm_min = 59;
        endOfDay.tm_sec = 59;

        std::tm weekStart, weekEnd;
        std::tm monthStart, monthEnd;

        switch (choice) {
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
                addEvent(calendar);
                break;
            case 5:
                std::cout << "\nTasks for today:\n";
                interface.displayTasksInRange(calendar, today, endOfDay);
                break;
            case 6:
                getCurrentWeekRange(weekStart, weekEnd);
                std::cout << "\nTasks for the current week:\n";
                interface.displayTasksInRange(calendar, weekStart, weekEnd);
                break;
            case 7:
                getCurrentMonthRange(monthStart, monthEnd);
                std::cout << "\nTasks for the current month:\n";
                interface.displayTasksInRange(calendar, monthStart, monthEnd);
                break;
            case 8:
                addTask(calendar);
                break;
            case 9:
                std::cout << "Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}