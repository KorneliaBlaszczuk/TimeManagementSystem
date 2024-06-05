#include "calendar.h"

std::time_t tm_to_time_t(const std::tm &t)
{
    std::tm temp = t;
    return mktime(&temp);
}

std::tm getCurrentDate()
{
    std::time_t t = std::time(nullptr);
    std::tm currentTime = *std::localtime(&t);
    currentTime.tm_hour = 0;
    currentTime.tm_min = 0;
    currentTime.tm_sec = 0;
    return currentTime;
}

void Calendar::addEvent(const Event &event)
{
    events.push_back(event);
}

void Calendar::addTask(const Task &task)
{
    tasks.push_back(task);
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

// Function to get start and end date of the current week
void getCurrentWeekRange(std::tm &weekStart, std::tm &weekEnd)
{
    std::tm today = getCurrentDate();
    int wday = today.tm_wday; // 0 = Sunday, 1 = Monday, ..., 6 = Saturday
    if (wday == 0)
        wday = 7; // Adjust Sunday to be the 7th day of the week

    weekStart = today;
    weekStart.tm_mday -= (wday - 1);
    mktime(&weekStart);

    weekEnd = weekStart;
    weekEnd.tm_mday += 6;
    mktime(&weekEnd);
}

// Function to get start and end date of the current month
void getCurrentMonthRange(std::tm &monthStart, std::tm &monthEnd)
{
    std::tm today = getCurrentDate();

    monthStart = today;
    monthStart.tm_mday = 1;
    mktime(&monthStart);

    monthEnd = today;
    monthEnd.tm_mon += 1;
    monthEnd.tm_mday = 0;
    mktime(&monthEnd);
}

std::tm make_tm(int year, int month, int day, int hour, int minute)
{
    std::tm t = {};
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = minute;
    t.tm_sec = 0;
    return t;
};