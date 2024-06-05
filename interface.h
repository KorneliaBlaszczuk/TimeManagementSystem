#pragma once
#include "calendar.h"
#include "event.h"
#include "task.h"
#include "reminder.h"
#include "pomodoro.h"
#include "plan.h"

// Interface class
class Interface
{
public:
    void displayCalendar(const Calendar &calendar);

    void displayEventsInRange(const Calendar &calendar, const std::tm &start, const std::tm &end);

    void displayTasksInRange(const Calendar &calendar, const std::tm &start, const std::tm &end);

    void selectMonthAndDisplayEvents(Calendar &calendar);

    void editEvent(Calendar &calendar);

    void editTask(Calendar &calendar);

    void addEvent(Calendar &calendar);

    void addTask(Calendar &calendar);
};