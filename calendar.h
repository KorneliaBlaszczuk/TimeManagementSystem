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

    void addReminder(const Reminder &reminder);

    std::vector<Event> filterEvents(const std::tm &start, const std::tm &end) const;

    std::vector<Task> filterTasks(const std::tm &start, const std::tm &end) const;

    bool removeEvent(const std::string &name, const std::tm &date);

    bool removeTask(const std::string &name, const std::tm &date);

    bool removeReminder(const std::string &name, const std::tm &date);
};
