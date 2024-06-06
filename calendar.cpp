#include "calendar.h"
#include <algorithm>

void Calendar::addEvent(const Event &event)
{
    events.push_back(event);
}

void Calendar::addTask(const Task &task)
{
    tasks.push_back(task);
}

void Calendar::addReminder(const Reminder &reminder)
{
    reminders.push_back(reminder);
}

std::vector<Event> Calendar::filterEvents(const std::tm &start, const std::tm &end) const
{
    std::vector<Event> result;
    std::time_t start_time = tm_to_time_t(start);
    std::time_t end_time = tm_to_time_t(end);
    for (const auto &event : events)
    {
        std::time_t event_start_time = tm_to_time_t(event.getStart());
        std::time_t event_end_time = tm_to_time_t(event.getEnd());
        if (difftime(event_start_time, end_time) <= 0 && difftime(event_end_time, start_time) >= 0)
        {
            result.push_back(event);
        }
    }
    return result;
}

std::vector<Task> Calendar::filterTasks(const std::tm &start, const std::tm &end) const
{
    std::vector<Task> result;
    std::time_t start_time = tm_to_time_t(start);
    std::time_t end_time = tm_to_time_t(end);
    for (const auto &task : tasks)
    {
        std::time_t task_time = tm_to_time_t(task.getDate());
        if ((task.getProgressStatus() == Task::Status::PENDING && (difftime(task_time, start_time) <= 0)) ||
            (difftime(task_time, start_time) >= 0 && difftime(task_time, end_time) <= 0))
        {
            result.push_back(task);
        }
    }
    return result;
}

std::vector<Reminder> Calendar::filterReminders(const std::tm &start, const std::tm &end) const
{
    std::vector<Reminder> result;
    std::time_t start_time = tm_to_time_t(start);
    std::time_t end_time = tm_to_time_t(end);
    for (const auto &reminder : reminders)
    {
        std::time_t reminder_time = tm_to_time_t(reminder.getDate());
        if ((difftime(reminder_time, start_time) >= 0 && difftime(reminder_time, end_time) <= 0))
        {
            result.push_back(reminder);
        }
    }
    return result;
}

bool Calendar::removeEvent(const std::string &name, const std::tm &date)
{
    auto it = std::remove_if(events.begin(), events.end(), [&](const Event &event)
                             { return event.getName() == name && compareTm(event.getStart(), date); });

    if (it != events.end())
    {
        events.erase(it, events.end());
        return true;
    }

    return false;
}

bool Calendar::removeTask(const std::string &name, const std::tm &date)
{
    auto it = std::remove_if(tasks.begin(), tasks.end(), [&](const Task &task)
                             { return task.getName() == name && compareTm(task.getDate(), date); });

    if (it != tasks.end())
    {
        tasks.erase(it, tasks.end());
        return true;
    }

    return false;
}

bool Calendar::removeReminder(const std::string &name, const std::tm &date)
{
    auto it = std::remove_if(reminders.begin(), reminders.end(), [&](const Reminder &reminder)
                             { return reminder.getName() == name && compareTm(reminder.getDate(), date); });

    if (it != reminders.end())
    {
        reminders.erase(it, reminders.end());
        return true;
    }

    return false;
}
