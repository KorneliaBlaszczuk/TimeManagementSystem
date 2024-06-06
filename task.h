#pragma once
#include "plan.h"
#include <vector>
#include <string>
#include <ctime>

// Task class
class Task : public Plan
{
public:
    enum Status
    {
        PENDING,
        COMPLETED
    };
    Task(std::string const &name, std::tm const &date, bool const &important, std::string const &progressNote, Status progressStatus)
        : Plan(name, date), important(important), progressNote(progressNote), progressStatus(progressStatus) {}

    void print() const;
    void saveToFile(std::ofstream &outFile) const;
    static bool loadFromFile(std::ifstream &inFile, Task &task);

    bool getImportant() const;
    void setImportant(const bool &newImp);
    std::string getProgressNote() const;
    void setProgressNote(const std::string &newProg);
    virtual std::vector<Task> getSubtasks() const;
    virtual void addToSubtask(const Task &newSub);
    Status getProgressStatus() const;
    void setStatus(const Status &newStatus);

    static void removeCompleted(std::vector<Task> &recentCompleted);

private:
    bool important;
    std::string progressNote;
    Status progressStatus;
    std::vector<Task> subtasks;
};

class SubTask : public Task
{
public:
    SubTask(std::string const &name, std::tm const &date, bool const &important, std::string const &progressNote, Status progressStatus) : Task(name, date, important, progressNote, progressStatus){};
    void addToSubtask(const Task &newSub) override;
    std::vector<Task> getSubtasks() const override;
};