#include <gtest/gtest.h>
#include <sstream>
#include "calendar.h"


TEST(EventTest, EventPrintsCorrectly) {
    std::tm startEvent = make_tm(2024, 6, 5, 10, 0);
    std::tm endEvent = make_tm(2024, 6, 5, 12, 0);
    Event event("Meeting", startEvent, endEvent, "Conference Room", {"Alice", "Bob"});

    std::ostringstream output;
    event.print();
    std::string expectedOutput = "Meeting             2024-06-05 10:00    2024-06-05 12:00    Conference Room     Attendees: Alice Bob \n";
    testing::internal::CaptureStdout();
    event.print();
    std::string outputStr = testing::internal::GetCapturedStdout();
    ASSERT_EQ(outputStr, expectedOutput);
}

TEST(EventTest, get)
{
    std::tm startEvent = make_tm(2024, 6, 5, 10, 0);
    std::tm endEvent = make_tm(2024, 6, 5, 12, 0);
    std::vector<std::string> r({"Alice", "Bob"});
    Event event("Meeting", startEvent, endEvent, "Conference Room", {"Alice", "Bob"});
    ASSERT_EQ(event.getName(), "Meeting");
    ASSERT_EQ(event.getLocation(), "Conference Room");
    ASSERT_EQ(event.getAttendees(), r);
}

TEST(EventTest, set)
{
    std::tm startEvent = make_tm(2024, 6, 5, 10, 0);
    std::tm endEvent = make_tm(2024, 6, 5, 12, 0);
    std::vector<std::string> r({"Alice", "Bob"});
    std::vector<std::string> r2({"Alice", "Bob", "Dylan"});
    Event event("Meeting", startEvent, endEvent, "Conference Room", {"Alice", "Bob"});
    ASSERT_EQ(event.getName(), "Meeting");
    ASSERT_EQ(event.getLocation(), "Conference Room");
    ASSERT_EQ(event.getAttendees(), r);
    event.setAttendees(r2);
    ASSERT_EQ(event.getAttendees(), r2);
    event.setLocation("Office");
    ASSERT_EQ(event.getLocation(), "Office");
    event.setName("Task");
    ASSERT_EQ(event.getName(), "Task");
}

TEST(EventTest, ConstructorAndAccessors) {
    std::tm start = {};
    start.tm_year = 2023 - 1900;
    start.tm_mon = 5 - 1;
    start.tm_mday = 10;
    start.tm_hour = 10;
    start.tm_min = 30;

    std::tm end = start;
    end.tm_hour = 12;

    std::vector<std::string> attendees = {"John Doe", "Jane Smith"};

    Event event("Meeting", start, end, "Conference Room", attendees);

    EXPECT_EQ(event.getName(), "Meeting");
    EXPECT_EQ(event.getStart().tm_year, 2023 - 1900);
    EXPECT_EQ(event.getStart().tm_mon, 5 - 1);
    EXPECT_EQ(event.getStart().tm_mday, 10);
    EXPECT_EQ(event.getStart().tm_hour, 10);
    EXPECT_EQ(event.getStart().tm_min, 30);
    EXPECT_EQ(event.getEnd().tm_hour, 12);
    EXPECT_EQ(event.getLocation(), "Conference Room");
    EXPECT_EQ(event.getAttendees(), attendees);
}

TEST(EventTest, SetAndGetStart) {
    std::tm start = {};
    std::tm newStart = {};
    start.tm_year = 2023 - 1900;
    std::vector<std::string> attendees = {};

    Event event("Meeting", start, start, "Conference Room", attendees);

    newStart.tm_year = 2024 - 1900;
    event.setStart(newStart);
    EXPECT_EQ(event.getStart().tm_year, 2024 - 1900);
}

TEST(EventTest, SetAndGetEnd) {
    std::tm end = {};
    std::tm newEnd = {};
    end.tm_year = 2023 - 1900;
    std::vector<std::string> attendees = {};

    Event event("Meeting", end, end, "Conference Room", attendees);

    newEnd.tm_year = 2024 - 1900;
    event.setEnd(newEnd);
    EXPECT_EQ(event.getEnd().tm_year, 2024 - 1900);
}

TEST(EventTest, SetAndGetLocation) {
    std::tm start = {};
    std::tm end = {};
    std::vector<std::string> attendees = {};

    Event event("Meeting", start, end, "Old Location", attendees);

    event.setLocation("New Location");
    EXPECT_EQ(event.getLocation(), "New Location");
}


TEST(EventTest, SetAndGetAttendees) {
    std::tm start = {};
    std::tm end = {};
    std::vector<std::string> attendees = {"John Doe", "Jane Smith"};

    Event event("Meeting", start, end, "Conference Room", attendees);

    std::vector<std::string> newAttendees = {"Alice", "Bob"};
    event.setAttendees(newAttendees);
    EXPECT_EQ(event.getAttendees(), newAttendees);
}

TEST(TaskTest, TaskPrintsCorrectly) {
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

TEST(TaskTest, ConstructorAndAccessors) {
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

TEST(TaskTest, SetAndGetImportant) {
    std::tm date = {};
    Task task("Test Task", date, false, "In Progress", Task::PENDING);

    task.setImportant(true);
    EXPECT_TRUE(task.getImportant());

    task.setImportant(false);
    EXPECT_FALSE(task.getImportant());
}

TEST(TaskTest, SetAndGetProgressNote) {
    std::tm date = {};
    Task task("Test Task", date, false, "Initial Note", Task::PENDING);

    task.setProgressNote("Updated Note");
    EXPECT_EQ(task.getProgressNote(), "Updated Note");
}

TEST(TaskTest, AddAndGetSubtasks) {
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

TEST(TaskTest, SetAndGetStatus) {
    std::tm date = {};
    Task task("Test Task", date, false, "In Progress", Task::PENDING);

    task.setStatus(Task::COMPLETED);
    EXPECT_EQ(task.getProgressStatus(), Task::COMPLETED);

    task.setStatus(Task::PENDING);
    EXPECT_EQ(task.getProgressStatus(), Task::PENDING);
}

TEST(CalendarTest, AddingAndFilteringEvents) {
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
    for(const auto& event : calendar.filterEvents(make_tm(2024, 6, 5), make_tm(2024, 6, 6))) {
        event.print();
    }
    std::string expectedOutput = "Meeting             2024-06-05 10:00    2024-06-05 12:00    Conference Room     Attendees: Alice Bob \n";
    testing::internal::CaptureStdout();
    std::string outputStr = "";
    for(const auto& event : calendar.filterEvents(make_tm(2024, 6, 5), make_tm(2024, 6, 6))) {
        event.print();
        outputStr += testing::internal::GetCapturedStdout();
    }

    ASSERT_EQ(outputStr, expectedOutput);
}

TEST(CalendarTest, AddingAndFilteringTasks) {
    Calendar calendar;

    std::tm taskDate1 = make_tm(2024, 6, 5);
    Task task1("Finish Report", taskDate1, true, "Work in progress", Task::PENDING);

    std::tm taskDate2 = make_tm(2024, 6, 7);
    Task task2("Prepare Presentation", taskDate2, false, "Not started yet", Task::PENDING);

    calendar.addTask(task1);
    calendar.addTask(task2);

    std::ostringstream output;
    for(const auto& task : calendar.filterTasks(make_tm(2024, 6, 5), make_tm(2024, 6, 6))) {
        task.print();
    }
    std::string expectedOutput = "2024-06-05          Finish Report       Important           Pending             Work in progress\n";
    testing::internal::CaptureStdout();
    for(const auto& task : calendar.filterTasks(make_tm(2024, 6, 5), make_tm(2024, 6, 6))) {
        task.print();
    }
    std::string outputStr = testing::internal::GetCapturedStdout();
    ASSERT_EQ(outputStr, expectedOutput);
}

TEST(CalendarTest, AddEvent) {
    Calendar calendar;
    std::tm start = make_tm(2023, 6, 10, 10, 30);
    std::tm end = make_tm(2023, 6, 10, 12, 0);
    Event event("Meeting", start, end, "Conference Room", {"John Doe"});

    calendar.addEvent(event);
    ASSERT_EQ(calendar.events.size(), 1);
    EXPECT_EQ(calendar.events[0].getName(), "Meeting");
}

// Test dodawania zadań do kalendarza
TEST(CalendarTest, AddTask) {
    Calendar calendar;
    std::tm date = make_tm(2023, 6, 10);
    Task task("Finish Report", date, true, "In Progress", Task::PENDING);

    calendar.addTask(task);
    ASSERT_EQ(calendar.tasks.size(), 1);
    EXPECT_EQ(calendar.tasks[0].getName(), "Finish Report");
}

// Test filtrowania wydarzeń w danym zakresie
TEST(CalendarTest, FilterEvents) {
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


TEST(CalendarTest, FilterTasks) {
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

TEST(CalendarTest, FilterEventsBoundary) {
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

TEST(CalendarTest, FilterTasksBoundary) {
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


TEST(help_funct, make_tm_)
{
    std::tm d1 = make_tm(2024, 6, 5, 12, 10);
    ASSERT_EQ(d1.tm_year, 2024-1900);
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
