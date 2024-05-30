#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

// Helper function to create std::tm from year, month, day, hour, and minute
std::tm make_tm(int year, int month, int day, int hour = 0, int minute = 0) {
    std::tm t = {};
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = minute;
    t.tm_sec = 0;
    return t;
}

// Helper function to convert std::tm to std::time_t
std::time_t tm_to_time_t(const std::tm& t) {
    std::tm temp = t;
    return mktime(&temp);
}

// Function to get current date
std::tm getCurrentDate() {
    std::time_t t = std::time(nullptr);
    std::tm currentTime = *std::localtime(&t);
    currentTime.tm_hour = 0;
    currentTime.tm_min = 0;
    currentTime.tm_sec = 0;
    return currentTime;
}

// Plan class
class Plan {
protected:
    std::string name;
    std::tm date;

public:
    Plan(std::string name, std::tm date)
        : name(name), date(date) {}

    std::string getName() const {
        return name;
    }

    std::tm getDate() const {
        return date;
    }

    void setName(const std::string& newName) {
        name = newName;
    }

    void setDate(const std::tm& newDate) {
        date = newDate;
    }
};

// Event class
class Event : public Plan {
public:
    std::tm start;
    std::tm end;
    std::string location;
    std::vector<std::string> attendees;

    Event(std::string name, std::tm start, std::tm end, std::string location, std::vector<std::string> attendees)
        : Plan(name, start), start(start), end(end), location(location), attendees(attendees) {}

    void print() const {
        char startBuffer[20];
        char endBuffer[20];
        strftime(startBuffer, 20, "%Y-%m-%d %H:%M", &start);
        strftime(endBuffer, 20, "%Y-%m-%d %H:%M", &end);

        std::cout << std::left << std::setw(20) << name<<std::setw(20)<<startBuffer
                  << std::setw(20) << endBuffer
                  << std::setw(20) << location
                  << "Attendees: ";
        for (const auto& attendee : attendees) {
            std::cout << attendee << " ";
        }
        std::cout << std::endl;
    }
};

// Task class
class Task : public Plan {
public:
    enum Status { PENDING, COMPLETED };
    bool important;
    std::string progressNote;
    Status progressStatus;
    std::vector<Task> subtasks;

    Task(std::string name, std::tm date, bool important, std::string progressNote, Status progressStatus)
        : Plan(name, date), important(important), progressNote(progressNote), progressStatus(progressStatus) {}

    void print() const {
        char dateBuffer[20];
        strftime(dateBuffer, 20, "%Y-%m-%d", &date);

        std::cout << std::left << std::setw(20) << dateBuffer
                  << std::setw(20) << name
                  << std::setw(20) << (important ? "Important" : "Not Important")
                  << std::setw(20) << (progressStatus == COMPLETED ? "Completed" : "Pending")
                  << progressNote << std::endl;

        if (!subtasks.empty()) {
            std::cout << "  Subtasks:\n";
            for (const auto& subtask : subtasks) {
                std::cout << "    - " << subtask.getName() << " (" << (subtask.progressStatus == COMPLETED ? "Completed" : "Pending") << ")\n";
            }
        }
    }
};


// Calendar class
class Calendar {
public:
    std::vector<Event> events;
    std::vector<Task> tasks;

    void addEvent(const Event& event) {
        events.push_back(event);
    }

    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    std::vector<Event> filterEvents(const std::tm& start, const std::tm& end) const {
        std::vector<Event> result;
        std::time_t start_time = tm_to_time_t(start);
        std::time_t end_time = tm_to_time_t(end);
        for (const auto& event : events) {
            std::time_t event_start_time = tm_to_time_t(event.start);
            std::time_t event_end_time = tm_to_time_t(event.end);
            if (difftime(event_start_time, end_time) <= 0 && difftime(event_end_time, start_time) >= 0) {
                result.push_back(event);
            }
        }
        return result;
    }

    std::vector<Task> filterTasks(const std::tm& start, const std::tm& end) const {
        std::vector<Task> result;
        std::time_t start_time = tm_to_time_t(start);
        std::time_t end_time = tm_to_time_t(end);
        for (const auto& task : tasks) {
            std::time_t task_time = tm_to_time_t(task.getDate());
            if ((task.progressStatus == Task::PENDING && (difftime(task_time, start_time) <= 0)) ||
                (difftime(task_time, start_time) >= 0 && difftime(task_time, end_time) <= 0)) {
                result.push_back(task);
            }
        }
        return result;
    }
};


// Interface class
class Interface {
public:
    void displayCalendar(const Calendar& calendar) {
        std::cout << std::left << std::setw(20) << "Start Date"
                  << std::setw(20) << "End Date"
                  << std::setw(20) << "Location"
                  << "Attendees" << std::endl;
        std::cout << std::string(80, '-') << std::endl;

        for (const auto& event : calendar.events) {
            event.print();

        }
    }

    void displayEventsInRange(const Calendar& calendar, const std::tm& start, const std::tm& end) {
        auto events = calendar.filterEvents(start, end);
        std::cout << std::left << std::setw(20) <<"Name"<< std::setw(20)<< "Start Date"
                  << std::setw(20) << "End Date"
                  << std::setw(20) << "Location"
                  << "Attendees" << std::endl;
        std::cout << std::string(100, '-') << std::endl;

        for (const auto& event : events) {
            event.print();
        }
    }

    void displayTasksInRange(const Calendar& calendar, const std::tm& start, const std::tm& end) {
        auto tasks = calendar.filterTasks(start, end);
        std::cout << std::left << std::setw(20) << "Date"
                  << std::setw(20) << "Name"
                  << std::setw(20) << "Importance"
                  << std::setw(20) << "Status"
                  << "Progress Note" << std::endl;
        std::cout << std::string(80, '-') << std::endl;

        for (const auto& task : tasks) {
            task.print();
        }
    }
};


// Function to add a new event
void addEvent(Calendar& calendar) {
    int year, month, day, startHour, startMinute, endHour, endMinute;
    std::string name, location;
    std::vector<std::string> attendees;
    std::string attendee;

    std::cout << "Enter event name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter event start year: ";
    std::cin >> year;
    if(year< 2000 || year > 2100)
    {
        std::cout<<"Invalid year: you can add event from 2000 to 2100\n";
        return;
    }
    std::cout << "Enter event start month: ";
    std::cin >> month;
    if(month< 1 || month > 12)
    {
        std::cout<<"Invalid month\n";
        return;
    }
    std::cout << "Enter event start day: ";
    std::cin >> day;
    if(day< 1 || day>31)
    {
        std::cout<<"Invalid day\n";
        return;
    }
    std::cout << "Enter event start hour: ";
    std::cin >> startHour;
    if(startHour< 0 || startHour > 24)
    {
        std::cout<<"Invalid start hour\n";
        return;
    }
    std::cout << "Enter event start minute: ";
    std::cin >> startMinute;
    if(startMinute < 0 || startMinute >59)
    {
        std::cout<<"Invalid start minute\n";
        return;
    }
    std::tm start = make_tm(year, month, day, startHour, startMinute);

    std::cout << "Enter event end hour: ";
    std::cin >> endHour;
    if(endHour< 0 || endHour > 24)
    {
        std::cout<<"Invalid end hour\n";
        return;
    }
    std::cout << "Enter event end minute: ";
    std::cin >> endMinute;
    if(endMinute < 0 || endMinute >59)
    {
        std::cout<<"Invalid end minute\n";
        return;
    }
    std::tm end = make_tm(year, month, day, endHour, endMinute);

    std::cin.ignore();
    std::cout << "Enter event location: ";
    std::getline(std::cin, location);

    std::cout << "Enter event attendees (enter 'done' to finish): ";
    while (std::cin >> attendee && attendee != "done") {
        attendees.push_back(attendee);
    }

    Event event(name, start, end, location, attendees);
    calendar.addEvent(event);
    std::cout << "Event added successfully.\n";
}

// Function to add a new task
void addTask(Calendar& calendar) {
    int year, month, day;
    std::string name, progressNote;
    bool important;
    int status;

    std::cout << "Enter task name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter task date year: ";
    std::cin >> year;
    if(year< 2000 || year > 2100)
    {
        std::cout<<"Invalid year: you can add event from 2000 to 2100\n";
        return;
    }
    std::cout << "Enter task date month: ";
    std::cin >> month;
    if(month< 1 || month > 12)
    {
        std::cout<<"Invalid month\n";
        return;
    }
    std::cout << "Enter task date day: ";
    std::cin >> day;
    if(day< 1 || day>31)
    {
        std::cout<<"Invalid day\n";
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
    while (std::cin.ignore(), std::getline(std::cin, subtaskName) && subtaskName != "done") {
        std::cout << "Enter subtask status (0 for pending, 1 for completed): ";
        std::cin >> status;
        Task::Status subtaskStatus = (status == 1) ? Task::COMPLETED : Task::PENDING;
        Task subtask(subtaskName, date, important, "", subtaskStatus);
        task.subtasks.push_back(subtask);
        std::cout << "Enter next subtask (or 'done' to finish): ";
    }

    calendar.addTask(task);
    std::cout << "Task added successfully.\n";
}

// Function to get start and end date of the current week
void getCurrentWeekRange(std::tm& weekStart, std::tm& weekEnd) {
    std::tm today = getCurrentDate();
    int wday = today.tm_wday; // 0 = Sunday, 1 = Monday, ..., 6 = Saturday
    if (wday == 0) wday = 7; // Adjust Sunday to be the 7th day of the week

    weekStart = today;
    weekStart.tm_mday -= (wday - 1);
    mktime(&weekStart);

    weekEnd = weekStart;
    weekEnd.tm_mday += 6;
    mktime(&weekEnd);
}

// Function to get start and end date of the current month
void getCurrentMonthRange(std::tm& monthStart, std::tm& monthEnd) {
    std::tm today = getCurrentDate();

    monthStart = today;
    monthStart.tm_mday = 1;
    mktime(&monthStart);

    monthEnd = today;
    monthEnd.tm_mon += 1;
    monthEnd.tm_mday = 0;
    mktime(&monthEnd);
}
