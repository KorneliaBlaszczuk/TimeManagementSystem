#pragma once
#include "calendar.h"
#include "pomodoro.h"

// Interface class
class Interface
{
public:
    int openFile(Calendar &calendar, std::string eventF, std::string tasksF, std::string completedT, std::string reminderF);

    void displayCalendar(const Calendar &calendar);

    void displayEventsInRange(const Calendar &calendar, const std::tm &start, const std::tm &end);

    void displayTasksInRange(const Calendar &calendar, const std::tm &start, const std::tm &end);

    void displayTasksCompleted(const Calendar &calendar);

    // TODO displaying reminders
    void displayTodayReminders(const Calendar &calendar);

    void displayTomorrowReminders(const Calendar &calendar);

    void selectMonthAndDisplayEvents(Calendar &calendar);

    void editEvent(Calendar &calendar, std::string file);

    void editTask(Calendar &calendar, std::string fileTasks, std::string fileCompleted);

    void editReminder(Calendar &Calendar, std::string reminderFile);

    void addReminder(Calendar &Calendar, std::string reminderFile);

    void addEvent(Calendar &calendar, std::string file);

    void addTask(Calendar &calendar, std::string fileTasks, std::string fileCompleted);

    void deleteTask(Calendar &calendar, std::string taskFile);

    void deleteEvent(Calendar &calendar, std::string outFile);

    void deleteReminder(Calendar &calendar, std::string reminderFile);

    // function use to run predefined pomodoro mode in project
    void PomodoroRun();
};