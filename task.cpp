#include "task.h"
#include <iomanip>
#include <ctime>
#include <iostream>

void Task::print() const
{
    char dateBuffer[20];
    strftime(dateBuffer, 20, "%Y-%m-%d", &date);

    std::cout << std::left << std::setw(20) << dateBuffer
              << std::setw(20) << name
              << std::setw(20) << (important ? "Important" : "Not Important")
              << std::setw(20) << (progressStatus == COMPLETED ? "Completed" : "Pending")
              << progressNote << std::endl;

    if (!subtasks.empty())
    {
        std::cout << "  Subtasks:\n";
        for (const auto &subtask : subtasks)
        {
            std::cout << "    - " << subtask.getName() << " (" << (subtask.progressStatus == COMPLETED ? "Completed" : "Pending") << ")\n";
        }
    }
}

bool Task::getImportant() const
{
    return important;
}

void Task::setImportant(const bool &newImp)
{
    important = newImp;
}

std::string Task::getProgressNote() const
{
    return progressNote;
}

void Task::setProgressNote(const std::string &newProg)
{
    progressNote = newProg;
}

std::vector<Task> Task::getSubtasks() const
{
    return subtasks;
}

void Task::addToSubtask(const Task &newSub)
{
    subtasks.push_back(newSub);
}

Task::Status Task::getProgressStatus() const
{
    return progressStatus;
}

void Task::setStatus(const Status &newStatus)
{
    progressStatus = newStatus;
}