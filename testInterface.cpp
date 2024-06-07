#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include "interface.h"

TEST(InterfaceTest, OpenFileLoadsEventsAndTasks)
{
    Calendar calendar;

    // events.txt file tests
    std::ofstream eventsFile("testEvents_.txt");
    eventsFile << "Event Name: Meeting\n";
    eventsFile << "Start Date: 2024-06-01 09:00\n";
    eventsFile << "End Date: 2024-06-01 10:00\n";
    eventsFile << "Location: Office\n";
    eventsFile << "Attendees: Alice,Bob,\n";
    eventsFile.close();

    // tasks.txt file tests
    std::ofstream tasksFile("testTasks_.txt");
    tasksFile << "Task Name: Finish Report\n";
    tasksFile << "Date: 2024-06-01\n";
    tasksFile << "Important: Yes\n";
    tasksFile << "Progress Note: Initial Draft\n";
    tasksFile << "Status: Pending\n";
    tasksFile << "Subtasks: 0\n";
    tasksFile.close();

    // tasks_completed.txt file tests
    std::ofstream tasksCompletedFile("testCompleted_.txt");
    tasksCompletedFile << "Task Name: Submit Report\n";
    tasksCompletedFile << "Date: 2024-05-01\n";
    tasksCompletedFile << "Important: Yes\n";
    tasksCompletedFile << "Progress Note: Final Draft\n";
    tasksCompletedFile << "Status: Completed\n";
    tasksCompletedFile << "Subtasks: 0\n";
    tasksCompletedFile.close();

    Interface interface;
    interface.openFile(calendar, "testEvents_.txt", "testTasks_.txt", "testCompleted_.txt", "testReminders.txt");

    ASSERT_EQ(calendar.events.size(), 1);
    EXPECT_EQ(calendar.events[0].getName(), "Meeting");
    EXPECT_EQ(calendar.events[0].getLocation(), "Office");
    EXPECT_EQ(calendar.events[0].getAttendees().size(), 2);
    EXPECT_EQ(calendar.events[0].getAttendees()[0], "Alice");
    EXPECT_EQ(calendar.events[0].getAttendees()[1], "Bob");

    ASSERT_EQ(calendar.tasks.size(), 1);
    EXPECT_EQ(calendar.tasks[0].getName(), "Finish Report");
    EXPECT_EQ(calendar.tasks[0].getProgressStatus(), Task::PENDING);
}

TEST(InterfaceTest, OpenFileLoadsEventsAndTasks_NoFile)
{
    std::string filename = "non_existent_file.txt";

    // non-existent file
    std::ifstream inFile(filename);

    ASSERT_FALSE(inFile.is_open()) << "File should not exist and thus not open.";

    Event event("", {}, {}, "", {});
    bool eventLoaded = Event::loadFromFile(inFile, event);
    EXPECT_FALSE(eventLoaded);

    inFile.close();
}

TEST(InterfaceTest, DisplayCalendar)
{
    Calendar calendar;
    Interface interface;

    std::tm start1 = make_tm(2023, 6, 6, 10, 0);
    std::tm end1 = make_tm(2023, 6, 6, 12, 0);
    Event event1("Event1", start1, end1, "Location1", {"Attendee1", "Attendee2"});
    calendar.addEvent(event1);

    std::tm start2 = make_tm(2023, 7, 7, 14, 0);
    std::tm end2 = make_tm(2023, 7, 7, 16, 0);
    Event event2("Event2", start2, end2, "Location2", {"Attendee3", "Attendee4"});
    calendar.addEvent(event2);

    // Capture the output of displayCalendar
    testing::internal::CaptureStdout();
    interface.displayCalendar(calendar);
    std::string output = testing::internal::GetCapturedStdout();

    std::string expectedOutput = "Start Date          End Date            Location            Attendees\n";
    expectedOutput += "--------------------------------------------------------------------------------\n";
    expectedOutput += "Event1              2023-06-06 10:00    2023-06-06 12:00    Location1           Attendee1, Attendee2, \n";
    expectedOutput += "Event2              2023-07-07 14:00    2023-07-07 16:00    Location2           Attendee3, Attendee4, \n";

    EXPECT_EQ(output, expectedOutput);
}

TEST(InterfaceTest, DisplayEventsInRange)
{
    Calendar calendar;
    Interface interface;

    // Create some events for testing
    std::tm start = make_tm(2024, 6, 1);
    std::tm end = make_tm(2024, 6, 30);
    calendar.addEvent(Event("Event1", start, end, "Location1", {"Attendee1", "Attendee2"}));
    calendar.addEvent(Event("Event2", start, end, "Location2", {"Attendee3", "Attendee4"}));

    std::ostringstream outputStream;
    std::streambuf *oldCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(outputStream.rdbuf()); // Redirect cout to our stringstream buffer

    interface.displayEventsInRange(calendar, start, end);

    std::cout.rdbuf(oldCoutBuffer); // Reset cout to standard output

    std::string expectedOutput = "Name                Start Date          End Date            Location            Attendees\n";
    expectedOutput += "----------------------------------------------------------------------------------------------------\n";
    expectedOutput += "Event2              2024-06-01 00:00    2024-06-30 00:00    Location2           Attendee3, Attendee4, \n";
    expectedOutput += "Event1              2024-06-01 00:00    2024-06-30 00:00    Location1           Attendee1, Attendee2, \n";

    EXPECT_EQ(outputStream.str(), expectedOutput);
}

TEST(InterfaceTest, DisplayTasksInRange)
{
    Calendar calendar;
    Interface interface;

    // Create some tasks for testing
    std::tm date = make_tm(2024, 6, 1);
    calendar.addTask(Task("Task1", date, true, "Progress1", Task::PENDING));
    calendar.addTask(Task("Task2", date, false, "Progress2", Task::COMPLETED));

    std::ostringstream outputStream;
    std::streambuf *oldCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(outputStream.rdbuf()); // Redirect cout to our stringstream buffer

    interface.displayTasksInRange(calendar, date, date);

    std::cout.rdbuf(oldCoutBuffer); // Reset cout to standard output

    std::string expectedOutput = "Date                Name                Importance          Status              Progress Note\n";
    expectedOutput += "--------------------------------------------------------------------------------\n";
    expectedOutput += "2024-06-01          Task1               Important           Pending             Progress1\n";

    EXPECT_EQ(outputStream.str(), expectedOutput);
}

TEST(InterfaceTest, DisplayTasksCompleted)
{
    Calendar calendar;
    Interface interface;

    // Create some completed tasks for testing
    std::tm date = make_tm(2024, 6, 1);
    calendar.addTask(Task("Task1", date, true, "Progress1", Task::COMPLETED));
    calendar.addTask(Task("Task2", date, false, "Progress2", Task::COMPLETED));

    std::ostringstream outputStream;
    std::streambuf *oldCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(outputStream.rdbuf()); // Redirect cout to our stringstream buffer

    interface.displayTasksCompleted(calendar);

    std::cout.rdbuf(oldCoutBuffer); // Reset cout to standard output

    std::string expectedOutput = "Date                Name                Importance          Status              Progress Note\n";
    expectedOutput += "--------------------------------------------------------------------------------\n";
    expectedOutput += "2024-06-01          Task2               Not Important       Completed           Progress2\n";
    expectedOutput += "2024-06-01          Task1               Important           Completed           Progress1\n";

    EXPECT_EQ(outputStream.str(), expectedOutput);
}

TEST(InterfaceTest, SelectMonthAndDisplayEvents)
{
    Calendar calendar;
    Interface interface;

    std::stringstream mockInput;
    mockInput << "6" << std::endl
              << "2024" << std::endl
              << "6" << std::endl
              << "2024" << std::endl;

    std::streambuf *oldCin = std::cin.rdbuf(mockInput.rdbuf());
    std::stringstream outputStream;
    std::streambuf *oldCout = std::cout.rdbuf(outputStream.rdbuf());

    interface.selectMonthAndDisplayEvents(calendar);

    // Restore cin and cout
    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    // Get the console output after the prompt for the end year
    std::string outputAfterPrompt;
    std::getline(outputStream, outputAfterPrompt); // Skip all lines until after the prompt for end year
    std::getline(outputStream, outputAfterPrompt); // Read the line after the prompt
    std::string expectedOutput = "Events from 6/2024 to 6/2024:";

    ASSERT_EQ(expectedOutput, outputAfterPrompt);
}

TEST(InterfaceTest, EditTask)
{
    Calendar calendar;
    Interface interface;

    Task task("Test Task", make_tm(2023, 6, 6), true, "This is a test task.", Task::PENDING);
    calendar.addTask(task);

    // Redirect std::cin
    std::stringstream input("Test Task\nNew Task\n2023\n6\n7\n1\nUpdated task description.\n1\n");
    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf());

    interface.editTask(calendar, "testTask.txt", "testCompleted.txt");

    ASSERT_EQ(calendar.tasks.size(), 1);
    EXPECT_EQ(calendar.tasks[0].getName(), "New Task");
    EXPECT_EQ(calendar.tasks[0].getDate().tm_year + 1900, 2023);
    EXPECT_EQ(calendar.tasks[0].getDate().tm_mon + 1, 6);
    EXPECT_EQ(calendar.tasks[0].getDate().tm_mday, 7);
    EXPECT_EQ(calendar.tasks[0].getImportant(), true);
    EXPECT_EQ(calendar.tasks[0].getProgressNote(), "Updated task description.");
    EXPECT_EQ(calendar.tasks[0].getProgressStatus(), Task::COMPLETED);

    // Restore original std::cin
    std::cin.rdbuf(oldCin);
}

TEST(InterfaceTest, EditEvent)
{
    Calendar calendar;
    Interface interface;

    Event event("Test Event", make_tm(2023, 6, 6, 10, 30), make_tm(2023, 6, 6, 12, 0), "Location1", {"Attendee1", "Attendee2"});
    calendar.addEvent(event);

    // Redirect std::cin
    std::stringstream input("Test Event\nNew Event\n2023\n6\n7\n13\n30\n2023\n6\n7\n14\n0\nNew Location\nAttendee3\ndone\n");
    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf());

    interface.editEvent(calendar, "testEvents.txt");

    ASSERT_EQ(calendar.events.size(), 1);
    EXPECT_EQ(calendar.events[0].getName(), "New Event");
    EXPECT_EQ(calendar.events[0].getStart().tm_year + 1900, 2023);
    EXPECT_EQ(calendar.events[0].getStart().tm_mon + 1, 6);
    EXPECT_EQ(calendar.events[0].getStart().tm_mday, 7);
    EXPECT_EQ(calendar.events[0].getStart().tm_hour, 13);
    EXPECT_EQ(calendar.events[0].getStart().tm_min, 30);
    EXPECT_EQ(calendar.events[0].getEnd().tm_hour, 14);
    EXPECT_EQ(calendar.events[0].getEnd().tm_min, 0);
    EXPECT_EQ(calendar.events[0].getLocation(), "New Location");
    EXPECT_EQ(calendar.events[0].getAttendees().size(), 1);
    EXPECT_EQ(calendar.events[0].getAttendees()[0], "Attendee3");

    // Restore original std::cin
    std::cin.rdbuf(oldCin);
}

TEST(InterfaceTest, EditRemider)
{
    Calendar calendar;
    Interface interface;
    Reminder rm("Test Reminder", make_tm(2024, 4, 4), "Old Details", Reminder::EVERYDAY);
    calendar.addReminder(rm);
    std::stringstream input("Test Reminder\nTest New Reminder\n2023\n6\n10\nDetails\n0\n");
    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf()); // Redirect std::cin
    // sets the buffer to input

    interface.editReminder(calendar, "testRemiders.txt");

    ASSERT_EQ(calendar.reminders.size(), 1);
    EXPECT_EQ(calendar.reminders[0].getName(), "Test New Reminder");
    EXPECT_EQ(calendar.reminders[0].getDate().tm_year, 123);
    EXPECT_EQ(calendar.reminders[0].getDate().tm_mon, 5);
    EXPECT_EQ(calendar.reminders[0].getDate().tm_mday, 10);
    EXPECT_EQ(calendar.reminders[0].getDetails(), "Details");
    EXPECT_EQ(calendar.reminders[0].getRepetitions(), "No repetition.");

    std::cin.rdbuf(oldCin); // Restore original std::cin
}

TEST(InterfaceTest, AddTask)
{
    Calendar calendar;
    Interface interface;

    std::stringstream input("Test Task\n2023\n6\n6\n1\nThis is a test task.\n0\ndone\n");
    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf()); // Redirect std::cin

    interface.addTask(calendar, "testTask.txt", "testCompleted.txt");

    ASSERT_EQ(calendar.tasks.size(), 1);
    EXPECT_EQ(calendar.tasks[0].getName(), "Test Task");
    EXPECT_EQ(calendar.tasks[0].getDate().tm_year + 1900, 2023);
    EXPECT_EQ(calendar.tasks[0].getDate().tm_mon + 1, 6);
    EXPECT_EQ(calendar.tasks[0].getDate().tm_mday, 6);
    EXPECT_EQ(calendar.tasks[0].getImportant(), true);
    EXPECT_EQ(calendar.tasks[0].getProgressNote(), "This is a test task.");
    EXPECT_EQ(calendar.tasks[0].getProgressStatus(), Task::PENDING);

    std::cin.rdbuf(oldCin); // Restore original std::cin
}

TEST(InterfaceTest, AddEvent)
{
    Calendar calendar;
    Interface interface;

    std::stringstream input("Test Event\n2023\n6\n6\n10\n30\n12\n0\nLocation1\nAttendee1\nAttendee2\ndone\n");
    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf()); // Redirect std::cin
    // sets the buffer to input

    interface.addEvent(calendar, "testEvents.txt");

    ASSERT_EQ(calendar.events.size(), 1);
    EXPECT_EQ(calendar.events[0].getName(), "Test Event");
    EXPECT_EQ(calendar.events[0].getStart().tm_year + 1900, 2023);
    EXPECT_EQ(calendar.events[0].getStart().tm_mon + 1, 6);
    EXPECT_EQ(calendar.events[0].getStart().tm_mday, 6);
    EXPECT_EQ(calendar.events[0].getStart().tm_hour, 10);
    EXPECT_EQ(calendar.events[0].getStart().tm_min, 30);
    EXPECT_EQ(calendar.events[0].getEnd().tm_hour, 12);
    EXPECT_EQ(calendar.events[0].getEnd().tm_min, 0);
    EXPECT_EQ(calendar.events[0].getLocation(), "Location1");
    EXPECT_EQ(calendar.events[0].getAttendees().size(), 2);
    EXPECT_EQ(calendar.events[0].getAttendees()[0], "Attendee1");
    EXPECT_EQ(calendar.events[0].getAttendees()[1], "Attendee2");

    std::cin.rdbuf(oldCin); // Restore original std::cin
}

TEST(InterfaceTest, AddRemider)
{
    Calendar calendar;
    Interface interface;

    std::stringstream input("Test Reminder\n2023\n6\n10\nDetails\n0\n");
    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf()); // Redirect std::cin
    // sets the buffer to input

    interface.addReminder(calendar, "testRemiders.txt");

    ASSERT_EQ(calendar.reminders.size(), 1);
    EXPECT_EQ(calendar.reminders[0].getName(), "Test Reminder");
    EXPECT_EQ(calendar.reminders[0].getDate().tm_year, 123);
    EXPECT_EQ(calendar.reminders[0].getDate().tm_mon, 5);
    EXPECT_EQ(calendar.reminders[0].getDate().tm_mday, 10);
    EXPECT_EQ(calendar.reminders[0].getDetails(), "Details");
    EXPECT_EQ(calendar.reminders[0].getRepetitions(), "No repetition.");

    std::cin.rdbuf(oldCin); // Restore original std::cin
}

TEST(help_funct, make_tm_)
{
    std::tm d1 = make_tm(2024, 6, 5, 12, 10);
    ASSERT_EQ(d1.tm_year, 2024 - 1900);
    ASSERT_EQ(d1.tm_mon, 5);
    ASSERT_EQ(d1.tm_mday, 5);
    ASSERT_EQ(d1.tm_hour, 12);
    ASSERT_EQ(d1.tm_min, 10);
    ASSERT_EQ(d1.tm_sec, 0);
}

TEST(plan, constr1)
{
    std::tm d1 = make_tm(2024, 6, 5, 12, 10);
    std::tm d2 = make_tm(2024, 6, 5, 12, 15);
    Plan p("plan1", d1);
    ASSERT_EQ(p.getName(), "plan1");
    p.setName("plan2");
    ASSERT_EQ(p.getName(), "plan2");
    p.setName("");
    ASSERT_EQ(p.getName(), "plan2");
}
