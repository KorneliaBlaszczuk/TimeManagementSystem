#pragma once
#include "calendar.h"
#include "event.h"
#include "task.h"
#include "reminder.h"
#include "pomodoro.h"
#include "plan.h"
#include "functions.h"

// Interface class
class Interface
{
public:
    int openFile(Calendar &calendar);

    void displayCalendar(const Calendar &calendar);

    void displayEventsInRange(const Calendar &calendar, const std::tm &start, const std::tm &end);

    void displayTasksInRange(const Calendar &calendar, const std::tm &start, const std::tm &end);

    void displayTasksCompleted(const Calendar &calendar);

    // TODO displaying reminders
    void displayTodayReminders(const Calendar &calendar);

    void displayTommorowReminders(const Calendar &calendar);

    void selectMonthAndDisplayEvents(Calendar &calendar);

    void editEvent(Calendar &calendar);

    void editTask(Calendar &calendar);

    void editReminder(Calendar &Calendar);

    void addReminder(Calendar &Calendar);

    void addEvent(Calendar &calendar);

    void addTask(Calendar &calendar);

    // TODO - all delete functions

    void deleteTask(Calendar &calendar);

    void deleteEvent(Calendar &calendar);

    void deleteReminder(Calendar &calendar);

    // function use to run predefined pomodoro mode in project
    void PomodoroRun();
};