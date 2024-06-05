#include <iostream>
#pragma once
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

// Helper function o create std::tm from year, month, day, hour, and minute
std::tm make_tm(int year, int month, int day, int hour=0, int minute=0) {
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
std::time_t tm_to_time_t(const std::tm& t);

// Function to get current date
std::tm getCurrentDate();


// Plan class
class Plan
{
protected:
    std::string name;
    std::tm date;

public:
    Plan(std::string name, std::tm date)
        : name(name), date(date) {}

    std::string getName() const;

    std::tm getDate() const;

    void setName(const std::string& newName);

    void setDate(const std::tm& newDate);
};

// Event class
class Event : public Plan
{
    std::tm start;
    std::tm end;
    std::string location;
    std::vector<std::string> attendees;
public:
    Event(std::string name, std::tm start, std::tm end, std::string location, std::vector<std::string> attendees)
        : Plan(name, start), start(start), end(end), location(location), attendees(attendees) {}

    void print() const;

    std::tm getStart() const;
    void setStart(const std::tm& newDate);
    std::tm getEnd() const;
    void setEnd(const std::tm& newDate);
    std::string getLocation() const;
    void setLocation(const std::string& newLoc);
    std::vector<std::string> getAttendees() const;
    void setAttendees(const std::vector<std::string>& newAttendees);

};

// Task class
class Task : public Plan
{
public:
    enum Status { PENDING, COMPLETED };
    Task(std::string name, std::tm date, bool important, std::string progressNote, Status progressStatus)
        : Plan(name, date), important(important), progressNote(progressNote), progressStatus(progressStatus) {}

    void print() const;

    bool getImportant() const;
    void setImportant(const bool& newImp);
    std::string getProgressNote() const;
    void setProgressNote(const std::string& newProg);
    std::vector<Task> getSubtasks() const;
    void addToSubtask(const Task& newSub);
    Status getProgressStatus() const;
    void setStatus(const Status& newStatus);
private:
    bool important;
    std::string progressNote;
    Status progressStatus;
    std::vector<Task> subtasks;
};


// Calendar class
class Calendar
{
public:
    std::vector<Event> events;
    std::vector<Task> tasks;

    void addEvent(const Event& event);

    void addTask(const Task& task);

    std::vector<Event> filterEvents(const std::tm& start, const std::tm& end) const;

    std::vector<Task> filterTasks(const std::tm& start, const std::tm& end) const;
};


// Interface class
class Interface
{
public:
    void displayCalendar(const Calendar& calendar);

    void displayEventsInRange(const Calendar& calendar, const std::tm& start, const std::tm& end);

    void displayTasksInRange(const Calendar& calendar, const std::tm& start, const std::tm& end);

    void selectMonthAndDisplayEvents(Calendar& calendar);

    void editEvent(Calendar& calendar);

    void editTask(Calendar& calendar);

    void addEvent(Calendar& calendar);

    void addTask(Calendar& calendar);
};

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
