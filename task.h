#pragma once
#include "plan.h"
#include "user.h"
#include <vector>
#include <string>
#include <ctime>

// Task class
class Task : public Plan
/*
Task Class
Class created to store and work with created tasks.
Each task can have subtasks.
Attributes::
- Name (in object of Plan Class) - std::string;
- Date (in object of Plan Class) - std::tm;
- Importance - bool;
- Progress Note - std::string;
- Progress Status - Status Enum: PENDING COMPLETED;
- Subtasks - std::vector <Task>.

Status of main task is not based on subtasks. User need to explicit set status of main task to COMPLETED.
*/
{
public:
    enum Status
    {
        PENDING,
        COMPLETED
    };
    // Constructor of Task object.
    Task(std::string const &name, std::tm const &date, bool const &important, std::string const &progressNote, Status progressStatus)
        : Plan(name, date), important(important), progressNote(progressNote), progressStatus(progressStatus) {}

    // Method to print object specifics in cout.
    void print() const;

    // Saving task object with it subtasks into given file.
    void saveToFile(std::ofstream &outFile) const;

    // Loading task objects with subtasks into program.
    // Takes empty task() as argument and returns bool value informing if loading was successful.
    static bool loadFromFile(std::ifstream &inFile, Task &task);

    // Getting bool value if task is important.
    bool getImportant() const;

    // Setting new bool value if task is important.
    void setImportant(const bool &newImp);

    // Getting progress note of task.
    std::string getProgressNote() const;

    // Setting new progress note of task.
    void setProgressNote(const std::string &newProg);

    // Getting vector of subtasks to given main task.
    virtual std::vector<Task> getSubtasks() const;

    // Adding new subtask (as an Task object) into subtasks.
    virtual void addToSubtask(const Task &newSub);

    // Getting progress status in from of enum - PENDING or COMPLETED.
    Status getProgressStatus() const;

    // Setting new progress status in from of enum - PENDING or COMPLETED.
    void setStatus(const Status &newStatus);

    // Updates files according with files according to their status .
    // Takes vector of completed task as an argument.
    static void removeCompleted(std::vector<Task> &recentCompleted, std::string compF);

private:
    bool important;
    std::string progressNote;
    Status progressStatus;
    std::vector<Task> subtasks;
};

class SubTask : public Task
/*
SubTask Class
Class created to store and work with created subtasks.
Subtask cannot have subtasks.
Attributes as in Class Task.
Class overrides functions to addToSubtask and getSubtask so they do nothing since subtask cannot have subtasks.
*/
{
public:
    SubTask(std::string const &name, std::tm const &date, bool const &important, std::string const &progressNote, Status progressStatus) : Task(name, date, important, progressNote, progressStatus){};
    void addToSubtask(const Task &newSub) override;
    std::vector<Task> getSubtasks() const override;
};