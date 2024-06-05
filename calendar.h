#pragma once
#include <vector>
#include <string>
#include "event.h"
#include "task.h"
#include "reminder.h"
#include "plan.h"

// Helper function o create std::tm from year, month, day, hour, and minute
std::tm make_tm(int year, int month, int day, int hour = 0, int minute = 0);

// Helper function to convert std::tm to std::time_t
std::time_t tm_to_time_t(const std::tm &t);

// Function to get current date
std::tm getCurrentDate();

// Calendar class
class Calendar
{
public:
    std::vector<Event> events;
    std::vector<Task> tasks;
    // std::vector<ReminderTODO> reminders;

    void addEvent(const Event &event);

    void addTask(const Task &task);

    std::vector<Event> filterEvents(const std::tm &start, const std::tm &end) const;

    std::vector<Task> filterTasks(const std::tm &start, const std::tm &end) const;
};

// Function to get start and end date of the current week
void getCurrentWeekRange(std::tm &weekStart, std::tm &weekEnd);

// Function to get start and end date of the current month
void getCurrentMonthRange(std::tm &monthStart, std::tm &monthEnd);