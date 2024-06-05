#pragma once
#include "calendar.h"

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