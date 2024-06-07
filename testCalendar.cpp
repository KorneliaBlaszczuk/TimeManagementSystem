#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include "calendar.h"

TEST(CalendarTest, AddingAndFilteringEvents)
{
    Calendar calendar;

    std::tm startEvent1 = make_tm(2024, 6, 5, 10, 0);
    std::tm endEvent1 = make_tm(2024, 6, 5, 12, 0);
    Event event1("Meeting", startEvent1, endEvent1, "Conference Room", {"Alice", "Bob"});

    std::tm startEvent2 = make_tm(2024, 6, 7, 14, 0);
    std::tm endEvent2 = make_tm(2024, 6, 7, 16, 0);
    Event event2("Presentation", startEvent2, endEvent2, "Auditorium", {"Charlie", "David"});

    calendar.addEvent(event1);
    calendar.addEvent(event2);

    std::ostringstream output;
    for (const auto &event : calendar.filterEvents(make_tm(2024, 6, 5), make_tm(2024, 6, 6)))
    {
        event.print();
    }
    std::string expectedOutput = "Meeting             2024-06-05 10:00    2024-06-05 12:00    Conference Room     Alice, Bob, \n";
    testing::internal::CaptureStdout();
    std::string outputStr = "";
    for (const auto &event : calendar.filterEvents(make_tm(2024, 6, 5), make_tm(2024, 6, 6)))
    {
        event.print();
        outputStr += testing::internal::GetCapturedStdout();
    }

    ASSERT_EQ(outputStr, expectedOutput);
}

TEST(CalendarTest, AddingAndFilteringEventsChecksOrder)
{
    Calendar calendar;

    std::tm startEvent1 = make_tm(2024, 6, 5, 10, 0);
    std::tm endEvent1 = make_tm(2024, 6, 5, 12, 0);
    Event event1("Meeting", startEvent1, endEvent1, "Conference Room", {"Alice", "Bob"});

    std::tm startEvent2 = make_tm(2024, 6, 7, 14, 0);
    std::tm endEvent2 = make_tm(2024, 6, 7, 16, 0);
    Event event2("Presentation", startEvent2, endEvent2, "Auditorium", {"Charlie", "David"});

    calendar.addEvent(event2);
    calendar.addEvent(event1);

    std::ostringstream output;
    for (const auto &event : calendar.filterEvents(make_tm(2024, 6, 5), make_tm(2024, 6, 6)))
    {
        event.print();
    }
    std::string expectedOutput = "Meeting             2024-06-05 10:00    2024-06-05 12:00    Conference Room     Alice, Bob, \n";
    testing::internal::CaptureStdout();
    std::string outputStr = "";
    for (const auto &event : calendar.filterEvents(make_tm(2024, 6, 5), make_tm(2024, 6, 6)))
    {
        event.print();
        outputStr += testing::internal::GetCapturedStdout();
    }

    ASSERT_EQ(outputStr, expectedOutput);
}

TEST(CalendarTest, AddingAndFilteringTasks)
{
    Calendar calendar;

    std::tm taskDate1 = make_tm(2024, 6, 5);
    Task task1("Finish Report", taskDate1, true, "Work in progress", Task::PENDING);

    std::tm taskDate2 = make_tm(2024, 6, 7);
    Task task2("Prepare Presentation", taskDate2, false, "Not started yet", Task::PENDING);

    calendar.addTask(task1);
    calendar.addTask(task2);

    std::ostringstream output;
    for (const auto &task : calendar.filterTasks(make_tm(2024, 6, 5), make_tm(2024, 6, 6)))
    {
        task.print();
    }
    std::string expectedOutput = "2024-06-05          Finish Report       Important           Pending             Work in progress\n";
    testing::internal::CaptureStdout();
    for (const auto &task : calendar.filterTasks(make_tm(2024, 6, 5), make_tm(2024, 6, 6)))
    {
        task.print();
    }
    std::string outputStr = testing::internal::GetCapturedStdout();
    ASSERT_EQ(outputStr, expectedOutput);
}

TEST(CalendarTest, AddingAndFilteringTasksChecksOrder)
{
    Calendar calendar;

    std::tm taskDate1 = make_tm(2024, 6, 5);
    Task task1("Finish Report", taskDate1, true, "Work in progress", Task::PENDING);

    std::tm taskDate2 = make_tm(2024, 6, 7);
    Task task2("Prepare Presentation", taskDate2, false, "Not started yet", Task::PENDING);

    calendar.addTask(task2);
    calendar.addTask(task1);

    std::ostringstream output;
    for (const auto &task : calendar.filterTasks(make_tm(2024, 6, 5), make_tm(2024, 6, 6)))
    {
        task.print();
    }
    std::string expectedOutput = "2024-06-05          Finish Report       Important           Pending             Work in progress\n";
    testing::internal::CaptureStdout();
    for (const auto &task : calendar.filterTasks(make_tm(2024, 6, 5), make_tm(2024, 6, 6)))
    {
        task.print();
    }
    std::string outputStr = testing::internal::GetCapturedStdout();
    ASSERT_EQ(outputStr, expectedOutput);
}

TEST(CalendarTest, AddingAndFilteringReminders)
{
    Calendar calendar;

    std::tm reminderDate1 = make_tm(2024, 6, 5);
    Reminder rm1("Finish Report", reminderDate1, "Work in progress", Reminder::NO);

    std::tm reminderDate2 = make_tm(2024, 6, 7);
    Reminder rm2("Prepare Presentation", reminderDate2, "Not started yet", Reminder::NO);

    calendar.addReminder(rm1);
    calendar.addReminder(rm2);

    std::ostringstream output;
    for (const auto &reminder : calendar.filterReminders(make_tm(2024, 6, 4), make_tm(2024, 6, 6)))
    {
        reminder.print();
    }
    std::string expectedOutput = "Tu ma byc wynik\n";
    testing::internal::CaptureStdout();
    for (const auto &reminder : calendar.filterReminders(make_tm(2024, 6, 5), make_tm(2024, 6, 6)))
    {
        reminder.print();
    }
    std::string outputStr = testing::internal::GetCapturedStdout();
    ASSERT_EQ(outputStr, expectedOutput);
}

TEST(CalendarTest, AddingAndFilteringRemindersCheckOrder)
{
    Calendar calendar;

    std::tm reminderDate1 = make_tm(2024, 6, 5);
    Reminder rm1("Finish Report", reminderDate1, "Work in progress", Reminder::NO);

    std::tm reminderDate2 = make_tm(2024, 6, 7);
    Reminder rm2("Prepare Presentation", reminderDate2, "Not started yet", Reminder::NO);

    calendar.addReminder(rm2);
    calendar.addReminder(rm1);

    std::ostringstream output;
    for (const auto &reminder : calendar.filterReminders(make_tm(2024, 6, 4), make_tm(2024, 6, 6)))
    {
        reminder.print();
    }
    std::string expectedOutput = "Tu ma byc wynik\n";
    testing::internal::CaptureStdout();
    for (const auto &reminder : calendar.filterReminders(make_tm(2024, 6, 5), make_tm(2024, 6, 6)))
    {
        reminder.print();
    }
    std::string outputStr = testing::internal::GetCapturedStdout();
    ASSERT_EQ(outputStr, expectedOutput);
}

TEST(CalendarTest, AddEvent)
{
    Calendar calendar;
    std::tm start = make_tm(2023, 6, 10, 10, 30);
    std::tm end = make_tm(2023, 6, 10, 12, 0);
    Event event("Meeting", start, end, "Conference Room", {"John Doe"});

    calendar.addEvent(event);
    ASSERT_EQ(calendar.events.size(), 1);
    EXPECT_EQ(calendar.events[0].getName(), "Meeting");
}

// Test dodawania zadań do kalendarza
TEST(CalendarTest, AddTask)
{
    Calendar calendar;
    std::tm date = make_tm(2023, 6, 10);
    Task task("Finish Report", date, true, "In Progress", Task::PENDING);

    calendar.addTask(task);
    ASSERT_EQ(calendar.tasks.size(), 1);
    EXPECT_EQ(calendar.tasks[0].getName(), "Finish Report");
}

TEST(CalendarTest, AddReminder)
{
    Calendar calendar;

    std::tm reminderDate1 = make_tm(2024, 6, 5);
    Reminder rm1("Finish Report", reminderDate1, "Work in progress", Reminder::NO);

    calendar.addReminder(rm1);
    ASSERT_EQ(calendar.reminders.size(), 1);
    EXPECT_EQ(calendar.reminders[0].getName(), "Finish Report");
}

// Test filtrowania wydarzeń w danym zakresie
TEST(CalendarTest, FilterEvents)
{
    Calendar calendar;
    std::tm start1 = make_tm(2023, 6, 10, 10, 30);
    std::tm end1 = make_tm(2023, 6, 10, 12, 0);
    Event event1("Meeting", start1, end1, "Conference Room", {"John Doe"});
    calendar.addEvent(event1);

    std::tm start2 = make_tm(2023, 6, 11, 14, 0);
    std::tm end2 = make_tm(2023, 6, 11, 15, 0);
    Event event2("Workshop", start2, end2, "Room 101", {"Jane Smith"});
    calendar.addEvent(event2);

    std::tm filterStart = make_tm(2023, 6, 10);
    std::tm filterEnd = make_tm(2023, 6, 10, 23, 59);
    std::vector<Event> filteredEvents = calendar.filterEvents(filterStart, filterEnd);

    ASSERT_EQ(filteredEvents.size(), 1);
    EXPECT_EQ(filteredEvents[0].getName(), "Meeting");
}

TEST(CalendarTest, FilterReminders)
{
    Calendar calendar;
    std::tm reminderDate1 = make_tm(2024, 6, 5);
    Reminder rm1("Finish Report", reminderDate1, "Work in progress", Reminder::NO);

    std::tm reminderDate2 = make_tm(2024, 6, 7);
    Reminder rm2("Prepare Presentation", reminderDate2, "Not started yet", Reminder::NO);

    calendar.addReminder(rm1);
    calendar.addReminder(rm2);

    std::tm filterStart = make_tm(2024, 6, 4); // Adjusted start date
    std::tm filterEnd = make_tm(2024, 6, 10, 23, 59); // Adjusted end date
    std::vector<Reminder> filteredReminders = calendar.filterReminders(filterStart, filterEnd);
    ASSERT_EQ(filteredReminders.size(), 2);
}

TEST(CalendarTest, FilterTasks)
{
    Calendar calendar;
    std::tm date1 = make_tm(2023, 6, 10);
    Task task1("Finish Report", date1, true, "In Progress", Task::PENDING);
    calendar.addTask(task1);

    std::tm date2 = make_tm(2023, 6, 11);
    Task task2("Prepare Presentation", date2, true, "Not Started", Task::PENDING);
    calendar.addTask(task2);

    std::tm filterStart = make_tm(2023, 6, 9);
    std::tm filterEnd = make_tm(2023, 6, 10);
    std::vector<Task> filteredTasks = calendar.filterTasks(filterStart, filterEnd);

    ASSERT_EQ(filteredTasks.size(), 1);
    EXPECT_EQ(filteredTasks[0].getName(), "Finish Report");
}

TEST(CalendarTest, FilterEventsBoundary)
{
    Calendar calendar;
    std::tm start = make_tm(2023, 6, 10, 10, 0);
    std::tm end = make_tm(2023, 6, 10, 11, 0);
    Event event("Meeting", start, end, "Conference Room", {"John Doe"});
    calendar.addEvent(event);

    std::tm filterStart = make_tm(2023, 6, 10, 11, 1);
    std::tm filterEnd = make_tm(2023, 6, 10, 12, 0);
    std::vector<Event> filteredEvents = calendar.filterEvents(filterStart, filterEnd);

    ASSERT_EQ(filteredEvents.size(), 0);
}

TEST(CalendarTest, FilterTasksBoundary)
{
    Calendar calendar;
    std::tm date = make_tm(2023, 6, 10);
    Task task("Finish Report", date, true, "In Progress", Task::PENDING);
    calendar.addTask(task);

    std::tm filterStart = make_tm(2023, 6, 10);
    std::tm filterEnd = make_tm(2023, 6, 10);
    std::vector<Task> filteredTasks = calendar.filterTasks(filterStart, filterEnd);

    ASSERT_EQ(filteredTasks.size(), 1);
    EXPECT_EQ(filteredTasks[0].getName(), "Finish Report");
}