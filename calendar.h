#pragma once
#include <vector>
#include <string>
#include "event.h"
#include "task.h"
#include "reminder.h"
#include "plan.h"
#include "functions.h"

// Calendar class
class Calendar
{
public:
    std::vector<Event> events;
    std::vector<Task> tasks;
    std::vector<Reminder> reminders;

    void addEvent(const Event &event);

    void addTask(const Task &task);

    std::vector<Event> filterEvents(const std::tm &start, const std::tm &end) const;

    std::vector<Task> filterTasks(const std::tm &start, const std::tm &end) const;
};

// Function to get start and end date of the current week
void getCurrentWeekRange(std::tm &weekStart, std::tm &weekEnd);

// Function to get start and end date of the current month
void getCurrentMonthRange(std::tm &monthStart, std::tm &monthEnd);