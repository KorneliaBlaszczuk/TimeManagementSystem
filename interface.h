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
    int openFile(Calendar &calendar, std::string eventF, std::string tasksF, std::string completedT);

    void displayCalendar(const Calendar &calendar);

    void displayEventsInRange(const Calendar &calendar, const std::tm &start, const std::tm &end);

    void displayTasksInRange(const Calendar &calendar, const std::tm &start, const std::tm &end);

    void displayTasksCompleted(const Calendar &calendar);

    // TODO displaying reminders
    void displayTodayReminders(const Calendar &calendar);

    void displayTommorowReminders(const Calendar &calendar);

    void selectMonthAndDisplayEvents(Calendar &calendar);

    void editEvent(Calendar &calendar, std::string file);

    void editTask(Calendar &calendar, std::string fileTasks, std::string fileCompleted);

    void editReminder(Calendar &Calendar);

    void addReminder(Calendar &Calendar);

    void addEvent(Calendar &calendar, std::string file);

    void addTask(Calendar &calendar, std::string fileTasks, std::string fileCompleted);

    // TODO - all delete functions

    void deleteTask(Calendar &calendar);

    void deleteEvent(Calendar &calendar);

    void deleteReminder(Calendar &calendar);

    // function use to run predefined pomodoro mode in project
    void PomodoroRun();
};