#include "modes.h"
#include "functions.h"
#include <algorithm>
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
    std::string userName;
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
                try {
                    User newUser = createUser();
                    std::cout << "User created successfully.\n";
                    return UserMode(newUser);
                } catch(const std::exception& e) {
                    std::cerr << "Error creating user: " << e.what() << '\n';
                }
                break;
            case 2:
                std::cout << "\nTimeSystem Users:\n";
                displayUsers();
                std::cout << "\n";
                break;
            case 3:
                std::cout << "\nDeleting an user\n";
                deleteUser();
                std::cout << "\n";
                break;
            case 4:
                std::cout << "\nGoing into user mode\n";
                try {
                    User user = getUser();
                    return UserMode(user);
                } catch(const std::exception& e) {
                    std::cerr << "Error: " << e.what() << '\n';
                    continue; // Go back to main menu
                }
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

    interface.openFile(calendar, user.getEventsFile(), user.getTaskFile(), user.getCompTaskFile(), user.getReminderFile());
    // @TODO tutaj będzie do openFile trzeba dopisać pewnie reminders

    std::cout << "Welcome back "
              << UserName;
    int result = UserMenu(interface, calendar, user);
    return result;
}

// function that takes care of navigating through menu and call proper functionalities of program
int UserMenu(Interface &interface, Calendar &calendar, User &user)
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
                interface.addEvent(calendar, user.getEventsFile());
                break;
            case 6:
                interface.editEvent(calendar, user.getEventsFile());
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
                interface.addTask(calendar, user.getTaskFile(), user.getCompTaskFile());
                break;
            case 12:
                interface.editTask(calendar, user.getTaskFile(), user.getCompTaskFile());
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
                interface.addReminder(calendar, user.getReminderFile());
                break;
            case 16:
                interface.editReminder(calendar, user.getReminderFile());
                break;
            case 17:
                interface.PomodoroRun();
                break;
            case 18:
                interface.deleteEvent(calendar, user.getEventsFile());
                break;
            case 19:
                interface.deleteTask(calendar, user.getTaskFile());
                break;
            case 20:
                interface.deleteReminder(calendar, user.getReminderFile());
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

User getUser()
{
    std::string userName;
    std::cout << "\nEnter your user name: ";
    std::getline(std::cin, userName);
    if (userName.empty())
    {
        std::cerr << "Invalid user name. It can't be empty.";
        throw std::invalid_argument("Invalid user name");
    }

    User user(userName);
    if (inUserList(userName))
        return user;
    else
    {
        std::cerr << "Incorrect user name.\n";
        throw std::invalid_argument("Incorrect user name");
    }
}

User createUser()
{
    std::string newUserName;
    std::cout << "\nEnter the new user's name: ";
    std::getline(std::cin, newUserName);

    if (newUserName.empty())
    {
        throw std::invalid_argument("User name cannot be empty");
    }

    // Check if the user already exists
    if (inUserList(newUserName))
    {
        throw std::invalid_argument("User already exists");
    }

    User newUser(newUserName);
    // tutaj dodawanie do pliku

    // First we load an existing ones into some vector
    std::vector<User> allUsers = loadUsers();
    allUsers.push_back(newUser);

    saveUsers(allUsers);

    return newUser; // Assuming User constructor takes a user name
}

void displayUsers()
{
    std::vector<User> users = loadUsers();
    for (auto& user : users)
    {
        user.print();
    }
}

void deleteUser() {
    std::string name;
    std::cout << "\nEnter the user's name to delete: ";
    std::getline(std::cin, name);

    if (name.empty()) {
        throw std::invalid_argument("User names are not empty.\n");
    }

    if (!inUserList(name)) {
        throw std::invalid_argument("This member doesn't exist.\n");
    }

    std::vector<User> allUsers = loadUsers();
    User userToRemove(name);

    // Użycie std::remove_if zamiast std::remove
    auto newEnd = std::remove_if(allUsers.begin(), allUsers.end(), [&](const User& user) {
        return user == userToRemove;
    });

    // Usuń elementy od nowego końca do faktycznego końca wektora
    allUsers.erase(newEnd, allUsers.end());

    // Zapisz zaktualizowaną listę użytkowników
    saveUsers(allUsers);

    std::cout << "User was deleted.\n";
}

bool inUserList(std::string& checkName)
{
    if (checkName.empty())
    {
        std::cerr << "Empty username.\n";
        return false;
    }

    std::ifstream usersFile("build/usersData/users.txt");
    if (!usersFile)
    {
        std::cerr << "No users available.\n";
        return false;
    }

    User uTemp(" ");
    while (loadFromFile(usersFile, uTemp))
    {
        if (uTemp.getName() == checkName)
        {
            return true;
        }
    }

    return false;
}

std::vector<User> loadUsers()
{
    std::vector<User> users;
    std::ifstream usersFile("build/usersData/users.txt");
    if (!usersFile)
    {
        return users;
    }

    User user(" ");
    while (loadFromFile(usersFile, user))
    {
        users.push_back(user);
    }

    usersFile.close();

    return users;
}

void saveUsers(std::vector<User> users)
{
    std::ofstream file("build/usersData/users.txt"); // Open the file for writing
    for (auto &user : users)
    {
        saveToFile(file, user);
    }
    file.close();

}