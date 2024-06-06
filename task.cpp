#include "task.h"
#include "plan.h"
#include "calendar.h"
#include <iomanip>
#include <ctime>
#include <iostream>
#include <fstream>

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

void Task::saveToFile(std::ofstream &outFile) const
{
    outFile << "Task Name: " << name << "\n";
    outFile << "Date: " << std::put_time(&date, "%Y-%m-%d") << "\n";
    outFile << "Important: " << (important ? "Yes" : "No") << "\n";
    outFile << "Progress Note: " << progressNote << "\n";
    outFile << "Status: " << (progressStatus == COMPLETED ? "Completed" : "Pending") << "\n";
    outFile << "Subtasks: " << subtasks.size() << "\n";
    for (const auto &subtask : subtasks)
    {
        subtask.saveToFile(outFile);
    }
}

bool Task::loadFromFile(std::ifstream &inFile, Task &task)
{
    std::string line;
    if (!std::getline(inFile, line) || !Plan::startsWith(line, "Task Name:"))
    {
        return false;
    }

    std::string name, dateStr, importantStr, progressNote, statusStr;

    name = line.substr(11);
    std::getline(inFile, line);
    dateStr = line.substr(6);
    std::getline(inFile, line);
    importantStr = line.substr(11);
    std::getline(inFile, line);
    progressNote = line.substr(14);
    std::getline(inFile, line);
    statusStr = line.substr(8);

    int year, month, day;
    std::sscanf(dateStr.c_str(), "%d-%d-%d", &year, &month, &day);
    std::tm date = make_tm(year, month, day);

    bool important = (importantStr == "Yes");
    Task::Status status = (statusStr == "Completed") ? Task::COMPLETED : Task::PENDING;

    task = Task(name, date, important, progressNote, status);

    std::getline(inFile, line);
    if (startsWith(line, "Subtasks:"))
    {
        size_t subtaskCount = std::stoi(line.substr(10));
        for (size_t i = 0; i < subtaskCount; ++i)
        {
            Task subtask("", {}, false, "", PENDING);
            if (loadFromFile(inFile, subtask))
            {
                task.addToSubtask(subtask);
            }
        }
    }

    return true;
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

void Task::removeCompleted(std::vector<Task> &recentCompleted)
{
    std::ofstream completedChecked("tasks_completed.txt");
    for (const auto &task : recentCompleted)
    {
        task.saveToFile(completedChecked);
    }

    completedChecked.close();
}

void SubTask::addToSubtask(const Task &newSub)
{
    std::cerr << "Adding subtask to subtask is not allowed.";
}

std::vector<Task> SubTask::getSubtasks() const
{
    std::vector<Task> vector;
    std::cerr << "Subtask cannot have subtasks.";
    return vector;
}