#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include <vector>
#include "functions.h"
#include "task.h"

TEST(TaskTest, TaskPrintsCorrectly)
{
    std::tm taskDate = make_tm(2024, 6, 5);
    Task task("Finish Report", taskDate, true, "Work in progress", Task::PENDING);

    std::ostringstream output;
    task.print();
    std::string expectedOutput = "2024-06-05          Finish Report       Important           Pending             Work in progress\n";
    testing::internal::CaptureStdout();
    task.print();
    std::string outputStr = testing::internal::GetCapturedStdout();
    ASSERT_EQ(outputStr, expectedOutput);
}

TEST(TaskTest, ConstructorAndAccessors)
{
    std::tm date = {};
    date.tm_year = 2023 - 1900;
    date.tm_mon = 5 - 1;
    date.tm_mday = 10;

    Task task("Test Task", date, true, "In Progress", Task::PENDING);

    EXPECT_EQ(task.getName(), "Test Task");
    EXPECT_EQ(task.getDate().tm_year, 2023 - 1900);
    EXPECT_EQ(task.getDate().tm_mon, 5 - 1);
    EXPECT_EQ(task.getDate().tm_mday, 10);
    EXPECT_TRUE(task.getImportant());
    EXPECT_EQ(task.getProgressNote(), "In Progress");
    EXPECT_EQ(task.getProgressStatus(), Task::PENDING);
}

TEST(TaskTest, SetAndGetImportant)
{
    std::tm date = {};
    Task task("Test Task", date, false, "In Progress", Task::PENDING);

    task.setImportant(true);
    EXPECT_TRUE(task.getImportant());

    task.setImportant(false);
    EXPECT_FALSE(task.getImportant());
}

TEST(TaskTest, SetAndGetProgressNote)
{
    std::tm date = {};
    Task task("Test Task", date, false, "Initial Note", Task::PENDING);

    task.setProgressNote("Updated Note");
    EXPECT_EQ(task.getProgressNote(), "Updated Note");
}

TEST(TaskTest, AddAndGetSubtasks)
{
    std::tm date = {};
    Task task("Main Task", date, false, "In Progress", Task::PENDING);
    Task subtask1("Subtask 1", date, false, "In Progress", Task::PENDING);
    Task subtask2("Subtask 2", date, false, "Completed", Task::COMPLETED);

    task.addToSubtask(subtask1);
    task.addToSubtask(subtask2);

    std::vector<Task> subtasks = task.getSubtasks();
    ASSERT_EQ(subtasks.size(), 2);
    EXPECT_EQ(subtasks[0].getName(), "Subtask 1");
    EXPECT_EQ(subtasks[1].getName(), "Subtask 2");
}

TEST(TaskTest, SetAndGetStatus)
{
    std::tm date = {};
    Task task("Test Task", date, false, "In Progress", Task::PENDING);

    task.setStatus(Task::COMPLETED);
    EXPECT_EQ(task.getProgressStatus(), Task::COMPLETED);

    task.setStatus(Task::PENDING);
    EXPECT_EQ(task.getProgressStatus(), Task::PENDING);
}

TEST(SubTaskTest, ctor)
{
    std::tm taskDate = make_tm(2024, 6, 5);
    SubTask task("Finish Report", taskDate, true, "in progress", Task::PENDING);
    EXPECT_EQ(task.getName(), "Finish Report");
    EXPECT_EQ(task.getDate().tm_year, 2024 - 1900);
    EXPECT_EQ(task.getDate().tm_mon, 6 - 1);
    EXPECT_EQ(task.getDate().tm_mday, 5);
    EXPECT_TRUE(task.getImportant());
    EXPECT_EQ(task.getProgressNote(), "in progress");
    EXPECT_EQ(task.getProgressStatus(), Task::PENDING);
}

TEST(SubTaskTest, add_not_allowed)
{
    std::tm taskDate = make_tm(2024, 6, 5);
    SubTask task("Finish Report", taskDate, true, "Work in progress", Task::PENDING);
    std::ostringstream outputStream;
    std::streambuf *oldCoutBuffer = std::cerr.rdbuf();
    std::cerr.rdbuf(outputStream.rdbuf()); // Redirect cout to our stringstream buffer
    task.addToSubtask(SubTask("a", taskDate, true, "abc", Task::COMPLETED));
    std::cerr.rdbuf(oldCoutBuffer); // Reset cout to standard output
    ASSERT_EQ(outputStream.str(), "Adding subtask to subtask is not allowed.");
}

TEST(SubTaskTest, getSub)
{
    std::vector<Task> res;
    std::tm taskDate = make_tm(2024, 6, 5);
    SubTask task("Finish Report", taskDate, true, "Work in progress", Task::PENDING);
    std::ostringstream outputStream;
    std::streambuf *oldCoutBuffer = std::cerr.rdbuf();
    std::cerr.rdbuf(outputStream.rdbuf()); // Redirect cout to our stringstream buffer
    task.getSubtasks();
    std::cerr.rdbuf(oldCoutBuffer); // Reset cout to standard output
    ASSERT_EQ(outputStream.str(), "Subtask cannot have subtasks.");
}